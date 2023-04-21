#include "rendering/SDL2.hpp"

#include "rendering/shader.hpp"
#include "rendering/camera.hpp"
#include "rendering/frame_buffer.hpp"

namespace YE {
namespace rendering {

    void SDL2::HandleResize(int w , int h) {

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

    void SDL2::FlushEvents() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE: m_Running = false; break;
                        case SDLK_w: if (m_Camera != nullptr) m_Camera->KeyboardCallback(&e); break;
                        case SDLK_s: if (m_Camera != nullptr) m_Camera->KeyboardCallback(&e); break;
                        case SDLK_a: if (m_Camera != nullptr) m_Camera->KeyboardCallback(&e); break;
                        case SDLK_d: if (m_Camera != nullptr) m_Camera->KeyboardCallback(&e); break;
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
                        case SDL_WINDOWEVENT_CLOSE: m_Running = false; break;
                        case SDL_WINDOWEVENT_RESIZED:
                            HandleResize(e.window.data1 , e.window.data2);
                            m_Window_size = { e.window.data1 , e.window.data2 };
                            m_Framebuffer_size = m_Window_size;
                        default: break;
                    }
                break;
                default: break;
            }
            if (m_Camera != nullptr) m_Camera->KeyboardCallback(&e);
            if (m_Camera != nullptr && m_Dragging_view) m_Camera->MouseCallback(&e);
            ImGui_ImplSDL2_ProcessEvent(&e);
        }
    }

    SDL2::~SDL2() {
        SDL_GL_DeleteContext(m_Context);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    bool SDL2::CreateWindow(SDL2_Config* config) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printf("Unable to initialize SDL: %s", SDL_GetError());
            return 1;
        }

        config->flags = SDL_WINDOW_OPENGL;

        if (config->resizable) config->flags |= SDL_WINDOW_RESIZABLE;
        // if (config->fullscreen) config->flags |= SDL_WINDOW_FULLSCREEN;
        // if (config->borderless) config->flags |= SDL_WINDOW_BORDERLESS;
        // if (config->hidden) config->flags |= SDL_WINDOW_HIDDEN;
        // if (config->maximized) config->flags |= SDL_WINDOW_MAXIMIZED;
        // if (config->minimized) config->flags |= SDL_WINDOW_MINIMIZED;

        m_Window = SDL_CreateWindow(config->title.c_str() , config->x , config->y , config->w , config->h , config->flags);
        if (m_Window == nullptr) {
            printf("Unable to create window: %s", SDL_GetError());
            return false;
        }

        m_Window_size = { config->w , config->h };
        m_Window_pos = { config->x , config->y };
        m_Framebuffer_size = m_Window_size;

        m_Rendering_to_scrn = config->render_to_screen;
        m_Clear_color = config->cc;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK , SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER , 1);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE , 8);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS , 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES , 24);

        SDL_SetWindowMinimumSize(m_Window , 200 , 200);

        m_Context = SDL_GL_CreateContext(m_Window);
        if (m_Context == nullptr) {
            printf("Unable to create OpenGL context: %s", SDL_GetError());
            return false;
        }
        if (config->vsync)
            SDL_GL_SetSwapInterval(1);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui_ImplSDL2_InitForOpenGL(m_Window , m_Context);
        ImGui_ImplOpenGL3_Init("#version 460");

        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            printf("Unable to initialize OpenGL context");
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);

        glClearColor(m_Clear_color.r , m_Clear_color.g , m_Clear_color.b , m_Clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (m_Rendering_to_scrn) {
            m_Framebuffer = std::make_unique<Framebuffer>(m_Framebuffer_size.x , m_Framebuffer_size.y);
            m_Framebuffer->m_Clear_color = m_Clear_color;
            
            m_Shader = std::make_unique<Shader>("shaders/post_process.vert" , "shaders/post_process.frag");

            m_Shader->Bind();
            m_Shader->SetUniformInt("screen_texture" , 0);
            m_Shader->Unbind();
        }

        m_Running = true;

        return true;
    }

    void SDL2::BeginRender() {
        FlushEvents();

        if (m_Rendering_to_scrn) {
            glViewport(0 , 0 , m_Framebuffer_size.x , m_Framebuffer_size.y);
            glClearColor(m_Framebuffer->m_Clear_color.x , m_Framebuffer->m_Clear_color.y , m_Framebuffer->m_Clear_color.z , m_Framebuffer->m_Clear_color.w);
        } else {
            glViewport(0 , 0 , m_Window_size.x , m_Window_size.y);
            glClearColor(m_Clear_color.r , m_Clear_color.g , m_Clear_color.b , m_Clear_color.a);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        m_Framebuffer->BindFrame();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_Window);
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
    }

    void SDL2::EndRender() {

        m_Framebuffer->UnbindFrame();
        glViewport(0 , 0 , m_Window_size.x , m_Window_size.y);

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

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window , backup_current_context);
        }

        SDL_GL_SwapWindow(m_Window);
    }

}
}