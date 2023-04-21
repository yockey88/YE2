#ifndef YE2_SDL2_HPP
#define YE2_SDL2_HPP

#include "SDL.h"
#undef main
#include "glad/glad.h"
#include "glm/glm.hpp"

#include "imgui.h"
#include "imgui_impl_sdl.h"
// #define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui_impl_opengl3.h"
#include "ImGuizmo.h"

#include <iostream>
#include <stdio.h>
#include <memory>

using sdl_gl_context = void*;

namespace YE {
namespace rendering {

    class Shader;
    class Camera;
    class Framebuffer;

    struct SDL2_Config {
        glm::vec4 cc{ 0.0f , 0.0f , 0.0f , 1.0f };
        int x = 0; int y = 0;
        int w = 0; int h = 0;
        bool valid     = false , vsync            = false;
        bool resizable = false , render_to_screen = true;
        Uint32 flags = 0;
        std::string title{ "[< blank >]" };
        std::string config_path{ "[< blank >]" };
    };
    
    class SDL2 {
        sdl_gl_context m_Context = nullptr;

        void HandleResize(int w , int h);
        void FlushEvents();

        SDL2(const SDL2&) = delete;
        SDL2(SDL2&&) = delete;
        SDL2& operator=(const SDL2&) = delete;
        public:
            std::unique_ptr<Shader> m_Shader = nullptr;
            std::unique_ptr<Framebuffer> m_Framebuffer = nullptr;
            SDL_Window* m_Window = nullptr;
            Camera* m_Camera = nullptr;
            glm::vec4 m_Clear_color{ 0.0f , 0.0f , 0.0f , 1.0f };
            glm::vec2 m_Window_size{ 0 , 0 };
            glm::vec2 m_Window_pos{ 0 , 0 };
            glm::vec2 m_Framebuffer_size{ 0 , 0 };
            bool m_Running = false;
            bool m_Dragging_view = false;
            bool m_Rendering_to_scrn = true;

            SDL2() {}
            ~SDL2();

            bool CreateWindow(SDL2_Config* config);
            void BeginRender();
            void EndRender();
    };

}
}

#endif