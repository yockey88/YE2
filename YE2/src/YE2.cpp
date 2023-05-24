#include "YE2.hpp"

namespace YE {


    // Static singleton instance
    Engine* Engine::engine_instance = nullptr; 

    bool Engine::InitSystems() {

        if (script_engine != nullptr) {
            
            YE_FATAL("Scripting engine already initialized | Should not be calling Engine::InitSystems() more than once");
            return false;

        }

        script_engine = std::make_unique<scripting::ScriptEngine>();

        if (!script_engine->Init()) {
            
            YE_FATAL("Failed to initialize scripting engine");
            return false;

        }
        
        return true;

    }

    Engine::~Engine() {

        if (engine_instance != nullptr) {
            
            delete engine_instance;
            engine_instance = nullptr;

        } else {

            std::cerr << "Engine instance was null when destructor was called\n";
            std::cerr << "Engine corrupted" << std::endl;

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

        YE_TRACE("Initializing Engine");

        YE_TRACE("Initializing Core Systems");

        if (!InitSystems()) {
            
            YE_FATAL("Engine::InitSystems() failed");
            return false;

        }

        YE_TRACE("Engine Initialized");
        return true;

    }

    void Engine::Shutdown() {

        YE_TRACE("Shutting down Engine");

        YE_TRACE("Engine Shut Down Successful");

        logger.Shutdown();

    }
    
}