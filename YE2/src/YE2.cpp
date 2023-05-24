#include "YE2.hpp"

namespace YE {


    // Static singleton instance
    Engine* Engine::engine_instance = nullptr; 

    bool Engine::InitSystems() {

        // Start by loading scripts because there might be scripts in use by other systems
        if (script_engine != nullptr) {
            
            YE_FATAL("Scripting engine already initialized | Should not be calling Engine::InitSystems() more than once");
            return false;

        }

        script_engine = std::make_unique<scripting::ScriptEngine>();
        if (!script_engine->Init()) {
            
            YE_FATAL("Failed to initialize scripting engine");
            return false;

        }

        /* 

        if (Filesystem::IsInitialized()) {
            
            YE_FATAL("Filesystem already initialized | Should not be calling Engine::InitSystems() more than once");
            return false;

        }
        
        if (!FileSystem::Init()) {
            
            YE_FATAL("Failed to initialize FileSystem");
            return false;

        }

        */
        
        return true;

    }

    Engine::~Engine() {

        if (engine_instance != nullptr) {
            
            delete engine_instance;
            engine_instance = nullptr;

        } else {

            std::cerr << "<!> Engine corrupted </!>\n\t!!!> Engine instance was null when destructor was called" << std::endl;

        }

    }

    Engine& Engine::Get() {

        if (engine_instance == nullptr) {
            
            engine_instance = new Engine();
        
        }

        return *engine_instance;

    }

    bool Engine::Init() {
        
        logger.Init();

        YE_INFO("Initializing Engine");

        YE_TRACE("Initializing Core Systems");

        if (!InitSystems()) {
            
            YE_FATAL("Engine::InitSystems() failed");
            logger.Shutdown();
            return false;

        }

        /** Setup Global State
         *   -> Define/Initialize global state variables
         *   -> Register global state variables and functions with scripting engine
        */

        // std::string cfg file path = Filesystem::YcfgPath();
        // std::string res path      = Filesystem::ResPath();
        // std::string log file path = Filesystem::LogPath();
        // std::string script path   = Filesystem::ScriptPath();
        // parsing::ConfigParser config_parser(/* path to .ycfg file */);
        // engine_config

        YE_INFO("Engine Initialized");
        return true;

    }

    void Engine::Shutdown() {

        YE_INFO("Shutting down Engine");

        YE_TRACE("Shutting down Core Systems");

        script_engine->Shutdown();

        YE_INFO("Engine Shut Down Successful");

        logger.Shutdown();

    }
    
}