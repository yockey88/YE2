#ifndef YE_SCRIPT_ENGINE_HPP
#define YE_SCRIPT_ENGINE_HPP

#include <string>
#include <filesystem>

#include "scripting/script_internals.hpp"
#include "scripting/script.hpp"

namespace YE {
namespace scripting {

    /** Script Engine State struct
     *   -> Holds all state for the script engine, including root domain, current app domain, current assembly, etc...
    */
    struct ScriptEngineState {

        MonoDomain* root_domain = nullptr;
        MonoDomain* app_domain = nullptr;

        MonoAssembly* core_assembly = nullptr;
        MonoImage* core_image = nullptr;

        bool script_engine_valid = false;

        std::string root_domain_name = "YE_ScriptRootDomain";

    };

    /** Script Engine Class 
     *   -> Handles all script related stuff
     *   -> Uses Mono to load and run C# dll assemblies as scripts
     *   -> Scripts must be written in a 'script' folder in the users main application directory next to 
     *          resources and other folders. The build system will copy the script folder to the runtime directory. In the future (near future)
     *          the engine will have a load option within the editor.
     *   -> Eventually will be able to load and run scripts from other languages (YSCRIPT!!!!! , Lua , etc...) (I want lots of options)
     *          but this engine will only support C# for now
    */
    class ScriptEngine {
        
        ScriptEngineState state;

        /**
         * Things I want/might want
         *  -> literally just registering member functions in the C# runtime
         *      I know i need a function pointer to register as internal call but how do I give a functione pointer 
         *      to this specific instance of the script engine existing at runtime.
        */

        public:
            // constructor only sets the mono assemblies paths
            //      might do more later such as set up debug information (hopefully do this soon)
            ScriptEngine();
            ~ScriptEngine();

            inline ScriptEngineState* GetState() { return &state; }

            // Instantiate an object (call constructor) of a scripted object
            MonoObject* InstantiateObject(MonoClass* klass);
            
            // initializes domains and does other basic script loading 
            //      and sets up certain other basic engine features
            bool Init();
            void Shutdown();

            void PrintTypes();
            // loads a script assembly from a file path to a DLL
            void LoadAssembly(const std::filesystem::path& path);    
            void UnloadAssembly();
    };

}
}

#endif // YE2_SCRIPT_ENGINE_HPP