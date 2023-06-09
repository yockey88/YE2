#include "log.hpp"
#include "core/engine.hpp"

#include "input/keyboard.hpp"

#include "rendering/window.hpp"

#include "rendering/shader.hpp"
#include "rendering/camera.hpp"
#include "rendering/frame_buffer.hpp"

#include "imgui_impl_sdl.h"

namespace YE {
namespace rendering {

    void Window::HandleResize(int w , int h) {

        int width , height;
        width = (int)(h * (16.0f / 9.0f));
        height = (int)(w * (1.f / (16.0f / 9.0f)));

        if (h >= height) {

            height = w;

        } else {

            height = h;

        }

        m_Framebuffer_size = glm::vec2(width , height);

    }

    void Window::FlushEvents() {

        if (input::Keyboard::IsKeyPressed(input::Key::YE_KEY_ESCAPE)) YE::Engine::Get().Quit();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {

            switch (e.type) {

                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {

                        // case SDLK_ESCAPE: YE::Engine::Get().Quit(); break;
                        // case SDLK_w: if (m_Camera != nullptr) [[fallthrough]]
                        // case SDLK_s: if (m_Camera != nullptr) [[fallthrough]]
                        // case SDLK_a: if (m_Camera != nullptr) [[fallthrough]]
                        // case SDLK_d: if (m_Camera != nullptr) m_Camera->KeyboardCallback(&e); break;
                        case SDLK_c:
                            SDL_SetRelativeMouseMode(SDL_FALSE);
                            m_Dragging_view = !m_Dragging_view;
                        break;
                        case SDLK_t: m_Rendering_to_scrn = !m_Rendering_to_scrn; break;
                        default: break;

                    }
                break;
                case SDL_WINDOWEVENT:
                    switch (e.window.event) {

                        case SDL_WINDOWEVENT_CLOSE: YE::Engine::Get().Quit(); break;
                        case SDL_WINDOWEVENT_RESIZED:
                            HandleResize(e.window.data1 , e.window.data2);
                            m_Window_size = { e.window.data1 , e.window.data2 };
                            m_Framebuffer_size = m_Window_size;
                        default: break;
                        
                    }
                break;
                default: break;

            }

            if (m_Camera != nullptr) m_Camera->DefaultKeyboardCallback();
            if (m_Camera != nullptr && m_Dragging_view) m_Camera->DefaultMouseCallback(&e);

            ImGui_ImplSDL2_ProcessEvent(&e);

        }
    }

    Window::~Window() {
        SDL_GL_DeleteContext(m_Context);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    bool Window::InitSDL2(SDL2_Config& config) {

        int sdl_init = SDL_Init(SDL_INIT_VIDEO);
        YE_ASSERT(sdl_init == 0 , "SDL2 failed to initialize");
        if (sdl_init != 0) return false;

        config.flags |= SDL_WINDOW_OPENGL;

        m_Window = SDL_CreateWindow(config.title.c_str() , config.x , config.y , config.w , config.h , config.flags);
        YE_ASSERT(m_Window != nullptr , "SDL2 failed to create window");
        if (m_Window == nullptr) return false;

        m_Window_size = { config.w , config.h };
        m_Window_pos = { config.x , config.y };
        m_Framebuffer_size = m_Window_size;

        m_Rendering_to_scrn = config.render_to_screen;
        m_Clear_color = { config.r , config.g , config.b , config.a };

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK , SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER , 1);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE , 8);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS , 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES , 24);

        SDL_SetWindowMinimumSize(m_Window , 200 , 200);

        m_Context = SDL_GL_CreateContext(m_Window);
        YE_ASSERT(m_Context != nullptr , "SDL2 failed to create OpenGL context");
        if (m_Context == nullptr) return false;
        
        if (config.vsync)
            SDL_GL_SetSwapInterval(1);

        return true;
    }
    
    bool Window::InitGL() {

        int glad_init = gladLoadGLLoader(SDL_GL_GetProcAddress);
        YE_ASSERT(glad_init != 0 , "GLAD failed to initialize");
        if (glad_init == 0) return false;

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);

        glClearColor(m_Clear_color.r , m_Clear_color.g , m_Clear_color.b , m_Clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (m_Rendering_to_scrn) {
            m_Framebuffer = std::make_unique<Framebuffer>(static_cast<uint32_t>(m_Framebuffer_size.x) , static_cast<uint32_t>(m_Framebuffer_size.y));
            m_Framebuffer->m_Clear_color = m_Clear_color;
            
            m_Shader = std::make_unique<Shader>("shaders/post_process.vert" , "shaders/post_process.frag");

            m_Shader->Bind();
            m_Shader->SetUniformInt("screen_texture" , 0);
            m_Shader->Unbind();
        }

        return true;

    }

    void Window::BeginRender() {

        FlushEvents();

        if (m_Rendering_to_scrn) {
            glViewport(0 , 0 , static_cast<uint32_t>(m_Framebuffer_size.x) , static_cast<uint32_t>(m_Framebuffer_size.y));
            glClearColor(m_Framebuffer->m_Clear_color.x , m_Framebuffer->m_Clear_color.y , m_Framebuffer->m_Clear_color.z , m_Framebuffer->m_Clear_color.w);
        } else {
            glViewport(0 , 0 , static_cast<uint32_t>(m_Window_size.x) , static_cast<uint32_t>(m_Window_size.y));
            glClearColor(m_Clear_color.r , m_Clear_color.g , m_Clear_color.b , m_Clear_color.a);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        m_Framebuffer->BindFrame();

    }

    void Window::Render() {

        m_Framebuffer->UnbindFrame();
        glViewport(0 , 0 , static_cast<uint32_t>(m_Window_size.x) , static_cast<uint32_t>(m_Window_size.y));

        glm::vec2 scale = m_Framebuffer_size / (glm::vec2)m_Window_size;
        glm::mat4 model = glm::mat4(1.0f);
        
        model = glm::scale(model , glm::vec3(scale.x , scale.y , 1.0f));

        if (m_Rendering_to_scrn) {
            m_Framebuffer->BindMesh();
            m_Framebuffer->BindTexture();
            m_Shader->Bind();
            m_Shader->SetUniformMat4("model" , model);
            m_Framebuffer->Draw();
            m_Shader->Unbind();
            m_Framebuffer->UnbindTexture();
            m_Framebuffer->UnbindMesh();
        }

    }

    void Window::EndRender() {

        SDL_GL_SwapWindow(m_Window);

    }

}
}