#include "core/engine.hpp"
#include "core/logger.hpp"

#include "input/keyboard.hpp"
#include "input/mouse.hpp"

#include "rendering/window.hpp"
#include "rendering/GUI.hpp"

#include "parsers/config_parser.hpp"

namespace YE {

    // Static singleton instance
    Engine* Engine::engine_instance = nullptr; 

    bool Engine::InitSystems(const core::EngineConfiguration& config) {

        input::Keyboard::Initialize();

        if (window != nullptr) {
            
            YE_FATAL("Window already created | Should not be calling Engine::InitSystems() more than once");
            return false;

        }

        window = std::make_unique<rendering::Window>();

        YE::rendering::SDL2_Config sdl2_config{};
        YE::rendering::ImGui_Config gui_config{};

        sdl2_config.title = config.render_config.title;
        sdl2_config.r = config.render_config.clear_color.r;
        sdl2_config.g = config.render_config.clear_color.g;
        sdl2_config.b = config.render_config.clear_color.b;
        sdl2_config.a = config.render_config.clear_color.a;
        sdl2_config.x = config.render_config.position.x;
        sdl2_config.y = config.render_config.position.y;
        sdl2_config.w = config.render_config.size.x;
        sdl2_config.h = config.render_config.size.y;
        sdl2_config.flags = config.render_config.flags;

        if (!window->InitSDL2(sdl2_config)) {

            YE_FATAL("Failed to create window");
            return false;

        }

        gui_config.config_flags  = config.gui_config.config_flags;
        gui_config.config_flags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
        gui_config.window_flags  = config.gui_config.window_flags;
        gui_config.dock_flags    = config.gui_config.dock_flags;
        gui_config.backend_flags = config.gui_config.backend_flags;
        gui_config.font_color    = config.gui_config.font_color;
        gui_config.font_size     = config.gui_config.font_size;
        gui_config.font_path     = config.gui_config.font_path;
        
        gui->InitGUI(gui_config , window->m_Window , window->m_Context);

        if (!window->InitGL()) {

            YE_FATAL("Failed to initialize OpenGL");
            return false;

        }

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
        
        return true;

    }

    void Engine::Update() {
        
        SDL_PumpEvents();

        input::Keyboard::Update();
        input::Mouse::Update();

        running_app->Update();

    }
    
    void Engine::Render() {

        window->BeginRender();
        gui->BeginRender(window->m_Window);

        running_app->Render();
        window->Render();

        running_app->RenderGUI();
        
        gui->EndRender(window->m_Window , window->m_Context);
        window->EndRender();

    }

    Engine::Engine() {
        
        logger = core::Logger::Get();

    }

    Engine::~Engine() {

        delete engine_instance;
        engine_instance = nullptr;

    }

    Engine& Engine::Get() {

        if (engine_instance == nullptr) {
            
            engine_instance = new Engine();
        
        }

        return *engine_instance;

    }

    bool Engine::Init(YApp* app) {
        
        /// \note temporary until parser for .yproj .yobj etc... is done
        core::EngineConfiguration en_config = app->GetEngineConfig();

        en_config.engine_version = glm::ivec3(0 , 0 , 1);

#ifdef YE_DEBUG
        en_config.render_config.debug_mode = true;
#else
        en_config.render_config.debug_mode = false;
#endif

        /// \todo(chris) actually parse the config file and set the values accordingly and check if valid
        en_config.valid = true; 

        logger->Init(en_config.proj_user_log_path);

        if (is_initialized) {
            
            YE_FATAL("Engine already initialized | Should not be calling YE::Engine::Init() more than once");
            
            YE_ASSERT(engine_instance != nullptr , "Engine instance is null | YE::Engine corrupted upon YE::Engine::Init()");
            delete engine_instance;
            engine_instance = nullptr;
            
            return false;

        } else if (engine_instance == nullptr) {
            
            YE_FATAL("Engine instance is null | YE::Engine corrupted upon YE::Engine::Init()");
            
            YE_ASSERT(engine_instance != nullptr , "Engine instance is null | YE::Engine corrupted upon YE::Engine::Init()");
            delete engine_instance;
            engine_instance = nullptr;
            
            return false;

        } else if (!en_config.valid) {

            YE_FATAL("Engine configuration is invalid | YE::Engine corrupted upon YE::Engine::Init()");
            
            YE_ASSERT(engine_instance != nullptr , "Engine instance is null | YE::Engine corrupted upon YE::Engine::Init()");            
            delete engine_instance;
            engine_instance = nullptr;
            
            return false;

        }

        if (!InitSystems(en_config)) {
            
            YE_FATAL("YE::Engine::InitSystems() failed");            

            YE_ASSERT(engine_instance != nullptr , "Engine instance is null | YE::Engine corrupted upon YE::Engine::Init()");
            delete engine_instance;
            engine_instance = nullptr;
            
            logger->Shutdown();
            return false;

        }

        if (!app->Init()) {

            YE_FATAL("Failed to intiialize application");
            Shutdown();

            return false;

        } else {

            running_app = std::move(app);

        }

        /** Setup Global State
         *   -> Define/Initialize global state variables
         *   -> Register global state variables and functions with scripting engine
        */

        is_initialized = true;

        running = true;

        return is_initialized;

    }

    void Engine::Run() {

        while (running) {

            Update();
            Render();

        }

        delete running_app;
        running_app = nullptr;

    }

    void Engine::Shutdown() {

        is_initialized = false;
        
        script_engine->Shutdown();

        logger->Shutdown();

    }

}