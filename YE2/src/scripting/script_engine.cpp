#include "scripting/script_engine.hpp"

#include "scripting/script_internals.hpp"
#include "log.hpp"

#include <iostream>
#include <fstream>
#include <vector>

static void LogInfo(MonoString* mono_msg) {

    char* c_msg = mono_string_to_utf8(mono_msg);
    std::string cpp_msg(c_msg);
    mono_free(c_msg);

    YE_INFO(cpp_msg);

}

static void LogTrace(MonoString* mono_msg) {

    char* c_msg = mono_string_to_utf8(mono_msg);
    std::string cpp_msg(c_msg);
    mono_free(c_msg);

    YE_TRACE(cpp_msg);

}

static void LogDebug(MonoString* mono_msg) {

    char* c_msg = mono_string_to_utf8(mono_msg);
    std::string cpp_msg(c_msg);
    mono_free(c_msg);

    YE_DEBUG_LOG(cpp_msg);

}

static void LogWarn(MonoString* mono_msg) {

    char* c_msg = mono_string_to_utf8(mono_msg);
    std::string cpp_msg(c_msg);
    mono_free(c_msg);

    YE_WARN(cpp_msg);

}

static void LogError(MonoString* mono_msg) {

    char* c_msg = mono_string_to_utf8(mono_msg);
    std::string cpp_msg(c_msg);
    mono_free(c_msg);

    YE_ERROR(cpp_msg);

}

namespace YE {
namespace scripting {

    ScriptEngine::ScriptEngine() {

        mono_set_assemblies_path("../../../external/mono/lib");

    }
    
    ScriptEngine::~ScriptEngine() {

        mono_jit_cleanup(state.root_domain);
        state.root_domain = nullptr;

    }

    MonoObject* ScriptEngine::InstantiateObject(MonoClass* klass) {

        YE_ASSERT(klass != nullptr , "Failed to instantiate Mono Object | Mono Class is null");
        if (klass == nullptr) return nullptr;

        MonoObject* obj = mono_object_new(state.app_domain , klass);
        YE_ASSERT(obj != nullptr , "Failed to instantiate object");
        if (obj == nullptr) return nullptr;

        mono_runtime_object_init(obj);
        return obj;

    }

    bool ScriptEngine::Init() {

        state.root_domain = mono_jit_init(state.root_domain_name.c_str());

        if (state.root_domain == nullptr) {

            YE_ERROR("Failed to initialize Mono domain");
            return false;
            
        }

        YE_ADD_INTERNAL_CALL(LogInfo);
        YE_ADD_INTERNAL_CALL(LogTrace);
        YE_ADD_INTERNAL_CALL(LogDebug);
        YE_ADD_INTERNAL_CALL(LogWarn);
        YE_ADD_INTERNAL_CALL(LogError);

        YE_ADD_INTERNAL_CALL(IDComponent_GetTag);
        YE_ADD_INTERNAL_CALL(IDComponent_SetTag);

        LoadAssembly("runtime_scripts/YE_CoreScripts.dll");

        YE_ASSERT(state.script_engine_valid , "Script engine failed to initialize");
        
        return state.script_engine_valid;
        
    }

    void ScriptEngine::Shutdown() {

        YE_ASSERT(state.script_engine_valid , "Script engine is invalid | Should not be calling ScriptEngine::Shutdown()");

        UnloadAssembly();

    }

    void ScriptEngine::PrintTypes() {

        MonoImage* image = mono_assembly_get_image(state.core_assembly);
        YE_ASSERT(image != nullptr , "Failed to get Mono image");
        if (image == nullptr) return;

        const MonoTableInfo* table = mono_image_get_table_info(image , MONO_TABLE_TYPEDEF);
        uint32_t rows = mono_table_info_get_rows(table);

        for (uint32_t i = 0; i < rows; i++) {

            uint32_t cols[MONO_TYPEDEF_SIZE];
            mono_metadata_decode_row(table , i , cols , MONO_TYPEDEF_SIZE);

            const char* namespace_name = mono_metadata_string_heap(image , cols[MONO_TYPEDEF_NAMESPACE]);
            const char* class_name = mono_metadata_string_heap(image , cols[MONO_TYPEDEF_NAME]);

            YE_INFO("[Script Type] | {}::{}" , namespace_name , class_name);

        }

    }

    void ScriptEngine::LoadAssembly(const std::filesystem::path& path) {
        
        char app_domain_name[] = "YEScriptAppDomain";
        state.app_domain = mono_domain_create_appdomain(app_domain_name , nullptr);

        if (state.app_domain == nullptr) {

            YE_ERROR("Failed to initialize Mono app domain");
            state.script_engine_valid = false;
            return;

        }

        std::ifstream script_dll(path , std::ios::binary | std::ios::ate);

        if (!script_dll.is_open()) {

            YE_ERROR("Failed to open script | {}" , path);
            state.script_engine_valid = false;
            return;

        }

        std::streampos end = script_dll.tellg();
        script_dll.seekg(0 , std::ios::beg);
        uint32_t size = static_cast<uint32_t>(end - script_dll.tellg());

        if (size == 0) {

            YE_ERROR("Script loaded from {} is empty" , path);
            state.script_engine_valid = false;
            return;

        }

        std::vector<char> buffer(size);
        script_dll.read(buffer.data() , size);
        script_dll.close();

        MonoImageOpenStatus status;
        MonoImage* script_image = mono_image_open_from_data_full(buffer.data() , size , true , &status , false);

        if (status != MONO_IMAGE_OK) {

            std::string err_msg = std::string(mono_image_strerror(status));
            YE_ERROR("Failed to open image from {} | {}" , path , err_msg);
            state.script_engine_valid = false;
            return;

        }

        state.core_assembly = mono_assembly_load_from_full(script_image , path.string().c_str() , &status , false);
        mono_image_close(script_image);

        if (state.core_assembly == nullptr) {

            std::string err_msg = std::string(mono_image_strerror(status));
            YE_ERROR("Failed to load assembly from {} | {}" , path , err_msg);
            state.script_engine_valid = false;
            return;

        }

        state.script_engine_valid = true;

    }

    void ScriptEngine::UnloadAssembly() {
        
        mono_domain_set(mono_get_root_domain() , false);

        mono_domain_unload(state.app_domain);
        state.app_domain = nullptr;

    }

}
}