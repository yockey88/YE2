#ifndef YE_SCRIPT_INTERNALS_HPP
#define YE_SCRIPT_INTERNALS_HPP

#include <string>
#include <filesystem>

#include "mono/jit/jit.h"

#define YE_ADD_INTERNAL_CALL(name) mono_add_internal_call("YE.InternalCalls::" #name , name)

namespace YE {
namespace scripting {
    
    /** Functions that are called from C#
     *      All functions declared here are added into the C# scripting API as internal calls
     *      i.e. they are added to the C# class InternalCalls, which is then accesses through any
     *      other C# script.
     * To add a function to the scripting API, declare it here and add it to the C# class InternalCalls
     *     in the file YE_CoreScripts/Scripts/InternalCalls.cs <!> Must recompile entire engine for this </!>
    */


    /** Internal Logging Funtions
     *  -> Logging support in C# scripts
    */
    void LogInfo(MonoString* mono_msg);
    void LogTrace(MonoString* mono_msg);
    void LogDebug(MonoString* mono_msg);
    void LogWarn(MonoString* mono_msg);
    void LogError(MonoString* mono_msg);

    /** Internal Filesystem Functions
     *  -> Filesystem support in C# scripts
     * <!> UNIMPLEMENTED </!> */

}
}

#endif