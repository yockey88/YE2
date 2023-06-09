#include "scripting/script_internals.hpp"

#include "log.hpp"

namespace YE {
namespace scripting {


    /// Logging 
    void LogInfo(MonoString* mono_msg) {

        char* c_msg = mono_string_to_utf8(mono_msg);
        std::string cpp_msg(c_msg);
        mono_free(c_msg);

        YE_INFO(cpp_msg);

    }

    void LogTrace(MonoString* mono_msg) {

        char* c_msg = mono_string_to_utf8(mono_msg);
        std::string cpp_msg(c_msg);
        mono_free(c_msg);

        YE_TRACE(cpp_msg);

    }

    void LogDebug(MonoString* mono_msg) {

        char* c_msg = mono_string_to_utf8(mono_msg);
        std::string cpp_msg(c_msg);
        mono_free(c_msg);

        YE_DEBUG_LOG(cpp_msg);

    }

    void LogWarn(MonoString* mono_msg) {
        
        char* c_msg = mono_string_to_utf8(mono_msg);
        std::string cpp_msg(c_msg);
        mono_free(c_msg);

        YE_WARN(cpp_msg);

    }

    void LogError(MonoString* mono_msg) {

        char* c_msg = mono_string_to_utf8(mono_msg);
        std::string cpp_msg(c_msg);
        mono_free(c_msg);

        YE_ERROR(cpp_msg);

    }

    /// ID Component
    MonoString* IDComponent_GetTag(uint64_t entity_id) {

        // auto entity = GetEntity(entity_id);

        // if (!entity) {

            // YE_ERROR("IDComponent_GetTag::[ Retrieved Invalid Entity ]");
            // return nullptr;

        // }

        // auto& id = entity.GetComponent<TagComponent>();
        // id.Tag = ScriptUtils::UTF8toMonoString(id.Tag);
        return nullptr;

    }

    void IDComponent_SetTag(uint64_t entity_id , MonoString* in_tag) {

        // auto entity = GetEntity(entity_id);

        // if (!entity) {

        //     YE_ERROR("IDComponent_SetTag::[ Retrieved Invalid Entity ]");
        //     return;

        // }

        // auto& id = entity.GetComponent<TagComponent>();
        // id.Tag = ScriptUtils::MonoStringtoUTF8(id.Tag);

    }

}
}