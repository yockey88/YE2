#include "scripting/script_internals.hpp"

#include "log.hpp"

namespace YE {
namespace scripting {

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

}
}