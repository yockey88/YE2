#include "YE2.hpp"

#include "console.hpp"
#include "scripts/native_scripts/test_native_entity.hpp"

#include <iostream>
#include <fstream>

class TestBed : public YE::YApp {

    DebugConsole console;

    ImFont* clacon_font = nullptr;
    ImFont* vera_font   = nullptr;

    std::shared_ptr<YE::game::Scene> scene;

    bool show_demo_window = true;
    bool show_console     = true;

    public:
        
        TestBed() {
            
            engine_config.proj_name          = "Engine Testing";
            engine_config.proj_author        = "Y";
            engine_config.proj_script_path   = "../../../TestBed/scripts";
            engine_config.proj_res_path      = "res";
            engine_config.proj_user_log_path = "logs/testbed_console.log";
            engine_config.render_config.render_type = YE::core::RenderConfiguration::RenderType::PERSPECTIVE;
            engine_config.render_config.clear_color = glm::vec4(0.2f , 0.2f , 0.2f , 1.0f);
            engine_config.render_config.position = glm::ivec2(SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED);
            engine_config.render_config.size = glm::ivec2(1600 , 900);
            engine_config.render_config.flags = SDL_WINDOW_RESIZABLE;
            engine_config.render_config.title = "YE2";
            engine_config.render_config.vsync = true;

            engine_config.gui_config.config_flags = ImGuiConfigFlags_NavEnableKeyboard;
            engine_config.gui_config.window_flags = ImGuiWindowFlags_MenuBar;
            engine_config.gui_config.font_color   = ImVec4(1.0f , 1.0f , 1.0f , 1.0f);
            engine_config.gui_config.font_size    = 11.0f;
            engine_config.gui_config.font_path    = "res/fonts";

        }

        virtual ~TestBed() override {}

        virtual bool Init() override {

            scene = std::make_shared<YE::game::Scene>();

            YE::game::Entity ent_handle = scene->CreateEntity(1 , "Test Ent");

            // clacon_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/clacon2.ttf" , 13.0f);
            // vera_font   = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/Vera.ttf" , 13.0f);

            YE_INFO("TestBed Initialized");

            return true;

        }

        virtual void Update() override { 

            scene->Update();

            if (YE::input::Mouse::IsButtonPressed(YE::input::MouseButton::YE_MOUSE_LEFT)) {

                YE_INFO("Left mouse button pressed");

            }

        } 
        
        virtual void Render() override {  }
        
        virtual void RenderGUI() override {

            if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

            if (show_console) console.Render(&show_console);

        }
        
};

YE::YApp* YE::CreateApp() { return new TestBed; }