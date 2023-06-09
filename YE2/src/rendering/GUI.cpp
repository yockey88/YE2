#include "rendering/GUI.hpp"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace YE {
namespace rendering {

    void YEGUI::InitGUI(ImGui_Config& config , SDL_Window* win , void* context) {
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark((ImGuiStyle*)0);

        io.ConfigWindowsResizeFromEdges = true;
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.ConfigFlags = config.config_flags;

        ImGui_ImplSDL2_InitForOpenGL(win , context);
        ImGui_ImplOpenGL3_Init("#version 460");

    }
    
    void YEGUI::BeginRender(SDL_Window* win) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(win);
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    }

    void YEGUI::EndRender(SDL_Window* win , void* context) {

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(win , context);

        }

    }

}
}