#ifndef YE_WINDOW_HPP
#define YE_WINDOW_HPP

#include <iostream>
#include <stdio.h>
#include <memory>

#include "SDL.h"
#undef main
#include "glad/glad.h"
#include "glm/glm.hpp"

using sdl_gl_context = void*;

namespace YE {
namespace rendering {

    // forward declarations
    class Shader;
    class Camera;
    class Framebuffer;

    // SDl2 Config struct, can be hard coded or parsed from a yobj file
    struct SDL2_Config {
        enum class RenderType { ORTHO = 0 , PERSPECTIVE = 1 } render_type = RenderType::PERSPECTIVE;
        
        float r = 0.0f , g = 0.0f , b = 0.0f , a = 1.0f; // clear color
        
        int v_major = 0 , v_minor = 0 , v_patch = 0; // version
        
        int x = SDL_WINDOWPOS_CENTERED; int y = SDL_WINDOWPOS_CENTERED; // size
        
        int w = 800; int h = 600; // dimensions
        
        bool valid     = false , vsync            = false; // 
        bool resizable = false , render_to_screen = true; // options
        
        Uint32 flags = 0;
        std::string title{ "[< blank >]" };
    };
    
    /** SDL2 Class
     *  -> wraps core window functionality from SDL2 as well sd OpenGL context creation
     *  -> also handles ImGui initialization and rendering??? (maybe idk yet, might want to allow user to override gui rendering and 
     *          other window related stuff)
    */
    class Window {

        void HandleResize(int w , int h);
        void FlushEvents();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;

        public:
            // shader and framebuffer are unique pointers because they are only used by the SDL2 class
            // these are only created and used if RenderToScreen is true, otherwise engine will only render to framebuffers
            // public because the engine might want to use them for something or change them
            std::unique_ptr<Shader> m_Shader = nullptr;
            std::unique_ptr<Framebuffer> m_Framebuffer = nullptr;
            
            sdl_gl_context m_Context = nullptr;
            SDL_Window* m_Window = nullptr;
            // Camera for event callbacks, but more robust event handling will be added later and this will go away
            Camera* m_Camera = nullptr;
            
            // IDK why public but it is cause it feels like it might need to be acesbile and getters/setters are inefficient.
            glm::vec4 m_Clear_color{ 0.0f , 0.0f , 0.0f , 1.0f };
            glm::vec2 m_Window_size{ 0 , 0 };
            glm::vec2 m_Window_pos{ 0 , 0 };
            glm::vec2 m_Framebuffer_size{ 0 , 0 };

            bool m_Running = false;
            bool m_Dragging_view = false;
            bool m_Rendering_to_scrn = true;

            Window() {}
            ~Window();

            bool InitSDL2(SDL2_Config& config);
            bool InitGL();
            void BeginRender();
            void Render();
            void EndRender();

    };

}
}

#endif