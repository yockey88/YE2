#ifndef YE_ENGINE_SETTINGS_HPP
#define YE_ENGINE_SETTINGS_HPP

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "imgui.h"

namespace YE {
namespace core {

    struct GUIConfiguration {

        ImGuiConfigFlags config_flags   = ImGuiConfigFlags_None;
        ImGuiWindowFlags window_flags   = ImGuiWindowFlags_None;
        ImGuiDockNodeFlags dock_flags   = ImGuiDockNodeFlags_None;
        ImGuiBackendFlags backend_flags = ImGuiBackendFlags_None;
        ImGuiInputTextFlags text_flags    = ImGuiInputTextFlags_None;
        
        ImVec4 font_color{ 1.f , 1.f , 1.f , 1.f };

        float font_size = 0.0f;

        std::string font_path = "";

    };

    struct RenderConfiguration {

        enum class RenderType { ORTHO = 0 , PERSPECTIVE = 1 } render_type = RenderType::PERSPECTIVE;
        
        glm::vec4 clear_color{ 0.f , 0.f , 0.f , 1.f }; 
        glm::ivec2 position{ 0 , 0 };
        glm::ivec2 size{ 800 , 600 };
        
        bool rendering = true;
        bool debug_mode = false;
        bool vsync = true;
        bool fullscreen = false;
        bool resizable = false;
        
        uint32_t flags = 0;
        std::string title{ "[< blank >]" };

        std::vector<std::string> window_icon_paths = {};

    };

    struct EngineConfiguration {

        RenderConfiguration render_config;
        GUIConfiguration gui_config;

        glm::ivec3 engine_version{ 0 , 0 , 0 };

        bool valid = false;
        bool rendering = true;
        
        std::string proj_name          = "<NO PROJECT NAME>";
        std::string proj_author        = "<NO AUTHOR NAME>"; 
        std::string proj_user_log_path = "logs/ye.log";
        std::string proj_res_path      = "<NO RESOURCE PATH>";
        std::string proj_script_path   = "<NO SCRIPT PATH>";

    };

}
}

#endif