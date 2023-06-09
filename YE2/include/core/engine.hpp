#ifndef YE_ENGINE_HPP
#define YE_ENGINE_HPP

#include "engine_config.hpp"
#include "logger.hpp"

#include "rendering/window.hpp"
#include "rendering/GUI.hpp"
#include "rendering/frame_buffer.hpp"
#include "rendering/shader.hpp"

#include "scripting/script_engine.hpp"

namespace YE {

    class YApp {

        protected:

            core::Logger* logger = nullptr;
            core::EngineConfiguration engine_config{};

        public:

            YApp() {}
            virtual ~YApp() {  }

            inline core::EngineConfiguration GetEngineConfig() const { return engine_config; }

            virtual bool Init()      = 0;
            virtual void Update()    = 0;
            virtual void Render()    = 0;
            virtual void RenderGUI() = 0;

    };

    YApp* CreateApp();

    /** EngineY Class
     *    -> Central engine class
    */
   /** !!!!!!!!!!!
    *   =!> Might get rid og singleton pattern, makes testing with gtest hard.
    *       That being said I shouldn't let a testing lib dictate my design choices
    *       But it is something to consider
    *   =!> Also a unique ptr might avhieve the same thing but do I wrap an engine unq ptr in another *exterior class* or do I recreate a unq ptr class for the engine?????
   */
    class Engine {
        
        static Engine* engine_instance;

        YApp* running_app    = nullptr;
        core::Logger* logger = nullptr;

        std::unique_ptr<rendering::Window> window              = nullptr;
        std::unique_ptr<rendering::YEGUI> gui                  = nullptr;
        std::unique_ptr<scripting::ScriptEngine> script_engine = nullptr;

        bool is_initialized = false;
        bool running = false;

        // private constructor to prevent instantiation
        // Only hiding it , it doesnt od anything
        Engine();
        
        // Delete copy constructors and assign operators
        Engine(Engine&&) = delete;
        Engine(const Engine&) = delete;
        Engine& operator=(Engine&&) = delete;
        Engine& operator=(const Engine&) = delete;

        // Internal initialization functions
        bool InitSystems(const core::EngineConfiguration& config);
        void Update();
        void Render();

        inline void Quit() { running = false; }
        
        friend class YApp;
        friend class rendering::Window;
        friend class rendering::YEGUI;

        public:

            ~Engine();

            // Get the Engine instance
            static Engine& Get();

            // Public Initialization function
            bool Init(YApp* app);

            void Run();

            // Public Shutdown function
            void Shutdown();

    };    

}

#endif