#ifndef YE_GUI_HPP
#define YE_GUI_HPP

#include "imgui.h"
#include "SDL.h"

#include <string>

namespace YE {
namespace rendering {

    struct ImGui_Config {
    
        ImGuiConfigFlags config_flags   = ImGuiConfigFlags_None;
        ImGuiWindowFlags window_flags   = ImGuiWindowFlags_None;
        ImGuiDockNodeFlags dock_flags   = ImGuiDockNodeFlags_None;
        ImGuiBackendFlags backend_flags = ImGuiBackendFlags_None;
        ImGuiInputTextFlags text_flags    = ImGuiInputTextFlags_None;
        ImGuiTreeNodeFlags tree_flags     = ImGuiTreeNodeFlags_None;
        
        ImVec4 font_color{ 1.f , 1.f , 1.f , 1.f };

        float font_size = 0.0f;

        std::string font_path = "";

    };

    class YEGUI {

        public:
            YEGUI() {}
            ~YEGUI() {}

            void InitGUI(ImGui_Config& config , SDL_Window* m_Window , void* m_Context);

            void BeginRender(SDL_Window* win);
            void EndRender(SDL_Window* win , void* context);

    };

}
}

#endif