#ifndef YE2_SDL2_HPP
#define YE2_SDL2_HPP

#include "SDL.h"
#undef main
#include "glad/glad.h"
#include "glm/glm.hpp"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo.h"

#include <iostream>
#include <stdio.h>
#include <memory>

/** SDL2 Wrapper
 *  -> wraps core window functionality from SDL2 as well sd OpenGL context creation
 * 
 * Structs::
 *  -> SDL2_Config
 * Classes::
 *  -> SDL2
 *      -> Shader (for window mesh)
 *      -> Camera (active camera)
 *      -> Framebuffer (for rendering to screen and textures)
*/

using sdl_gl_context = void*;

namespace YE {
namespace rendering {

    // forward declarations
    class Shader;
    class Camera;
    class Framebuffer;

    // SDl2 Config struct, can be hard coded or parsed from a yobj file
    struct SDL2_Config {
        glm::vec4 cc{ 0.0f , 0.0f , 0.0f , 1.0f }; // color
        int x = SDL_WINDOWPOS_CENTERED; int y = SDL_WINDOWPOS_CENTERED; // size
        int w = 800; int h = 600; // dimensions
        bool valid     = false , vsync            = false; // 
        bool resizable = false , render_to_screen = true; // options
        Uint32 flags = 0;
        std::string title{ "[< blank >]" };
        std::string config_path{ "[< blank >]" };
    };
    
    // SDL2 Wrapper
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