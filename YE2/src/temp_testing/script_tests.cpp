#include "temp_testing/script_tests.hpp"
#include "log.hpp"

#include <fstream>
#include <sstream>

namespace YE {

    bool RunScriptingTests() {
            
        // mono_set_assemblies_path("../../../external/mono/lib");

        // MonoDomain* root_domain = mono_jit_init("YE_ScriptRuntime");
        
        // if (root_domain == nullptr) {

        //     YE_ERROR("Failed to initialize Mono domain");
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Mono domain initialized");

        // }

        // std::ifstream script_dll("runtime_scripts/cs_test.dll" , std::ios::binary | std::ios::ate);

        // if (!script_dll.is_open()) {

        //     YE_ERROR("Failed to open script assembly");
            
        //     delete root_domain;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Script assembly opened");

        // }

        // std::streampos end = script_dll.tellg();
        // script_dll.seekg(0 , std::ios::beg);
        // uint32_t size = end - script_dll.tellg();

        // if (size == 0) {

        //     YE_ERROR("Script assembly is empty");
            
        //     delete root_domain;
        //     return false;

        // }

        // std::vector<char> script_assembly(size);
        // script_dll.read(script_assembly.data() , size);
        // script_dll.close();

        // MonoImageOpenStatus status;
        // MonoImage* script_image = mono_image_open_from_data_full(script_assembly.data() , size , true , &status , false);

        // if (status != MONO_IMAGE_OK) {

        //     std::string err_msg = std::string(mono_image_strerror(status));
        //     YE_ERROR("Failed to open script assembly image | {}" , err_msg);
            
        //     delete root_domain;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Script assembly image opened");

        // }

        // MonoAssembly* mono_script_assembly = mono_assembly_load_from_full(script_image , "runtime_scripts/cs_test.dll" , &status , false);
        // mono_image_close(script_image);

        // if (mono_script_assembly == nullptr) {

        //     YE_ERROR("Failed to load script assembly");
            
        //     delete root_domain;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Script assembly loaded");

        // }

        // MonoImage* script_image2 = mono_assembly_get_image(mono_script_assembly);

        // if (script_image2 == nullptr) {

        //     YE_ERROR("Failed to get script assembly image");
            
        //     delete root_domain;
        //     delete mono_script_assembly;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Script assembly image retrieved");

        // }

        // const MonoTableInfo* type_def_table = mono_image_get_table_info(script_image2 , MONO_TABLE_TYPEDEF);

        // if (type_def_table == nullptr) {

        //     YE_ERROR("Failed to get type definition table");
            
        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Type definition table retrieved");

        // }

        // int32_t num_types = mono_table_info_get_rows(type_def_table);

        // for (int32_t i = 0; i < num_types; i++) {

        //     uint32_t cols[MONO_TYPEDEF_SIZE];
        //     mono_metadata_decode_row(type_def_table, i, cols, MONO_TYPEDEF_SIZE);

        //     const char* nameSpace = mono_metadata_string_heap(script_image2, cols[MONO_TYPEDEF_NAMESPACE]);
        //     const char* name = mono_metadata_string_heap(script_image2, cols[MONO_TYPEDEF_NAME]);

        //     printf("%s::%s\n", nameSpace, name);

        // }

        // MonoClass* script_class = mono_class_from_name(script_image2 , "YE_SCRIPT" , "ScriptTest");

        // if (script_class == nullptr) {

        //     YE_ERROR("Failed to get script class");
            
        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Script class retrieved");

        // }

        // MonoObject* script_class_instance = mono_object_new(root_domain , script_class);
        
        // if (script_class_instance == nullptr) {

        //     YE_ERROR("Failed to create script class instance");
            
        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Script class instance created");

        // }

        // mono_runtime_object_init(script_class_instance);

        // MonoMethod* script_method = mono_class_get_method_from_name(script_class , "PrintMyFloat" , 0);

        // if (script_method == nullptr) {

        //     YE_ERROR("Failed to get script method");
            
        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // } else {

        //     YE_DEBUG_LOG("Script method retrieved");

        // }

        // MonoObject* exception = nullptr;
        // mono_runtime_invoke(script_method , script_class_instance , nullptr , &exception);

        // if (exception != nullptr) {

        //     YE_ERROR("Failed to invoke script method");
            
        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // }

        // MonoMethod* script_method2 = mono_class_get_method_from_name(script_class , "IncrementFloatVar" , 1);

        // if (script_method2 == nullptr) {

        //     YE_ERROR("Failed to get script method");

        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // }

        // float val = 5.0f;
        // void* args[] = { &val };
        // mono_runtime_invoke(script_method2 , script_class_instance , args , &exception);

        // if (exception != nullptr) {

        //     YE_ERROR("Failed to invoke script method");

        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // }

        // mono_runtime_invoke(script_method , script_class_instance , nullptr , &exception);

        // if (exception != nullptr) {

        //     YE_ERROR("Failed to invoke script method");

        //     delete root_domain;
        //     delete mono_script_assembly;
        //     delete script_image2;
        //     return false;

        // }

        // delete root_domain;
        // delete mono_script_assembly;
        // delete script_image2;

        return true;
    }

}