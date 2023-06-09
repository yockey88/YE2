#ifndef YETB_CONSOLE_HPP
#define YETB_CONSOLE_HPP

#include <string>
#include <vector>

class DebugConsole {

    char console_input[256] = {};

    std::vector<std::string> console_display{};
    std::vector<std::string> console_history{};

    public:
        DebugConsole() {}
        ~DebugConsole() {}

        void Render(bool* show_console) {

            if (ImGui::Begin("Debug Console" , show_console , ImGuiWindowFlags_MenuBar)) {

                if (ImGui::BeginMenuBar()) {

                    if (ImGui::BeginMenu("File")) {

                        if (ImGui::MenuItem("Save" , "Ctrl+S")) {

                            console_history.reserve(console_history.size() + console_display.size());
                            console_history.insert(console_history.end() , console_display.begin() , console_display.end());    
                            console_display.clear();

                            for (auto& cmd : console_history) {

                                YE_USER_FILE_TRACE(cmd);

                            }

                        }

                        ImGui::EndMenu();
                        
                    }

                    if (ImGui::Button("Clear")) {

                        console_history.reserve(console_history.size() + console_display.size());
                        console_history.insert(console_history.end() , console_display.begin() , console_display.end());    
                        console_display.clear();
                        
                    }

                    ImGui::EndMenuBar();

                }

                const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

                if (ImGui::BeginChild("ConsoleRegion" , ImVec2(0 , -footer_height_to_reserve) , false , ImGuiWindowFlags_HorizontalScrollbar)) {

                    // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing , ImVec2(4 , 1));

                    for (auto& cmd : console_display) {

                        ImGui::TextWrapped(cmd.c_str());

                    }

                    // ImGui::PopStyleVar();

                    // if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.0f);

                }
                ImGui::EndChild();
                ImGui::Separator();

                // ImGui::PushFont(clacon_font);
                ImGui::TextColored(ImVec4(0.f , 1.f , 0.f , 1.f) , "|YE2 $>");
                ImGui::SameLine();
                ImGui::InputText("<$>" , console_input , IM_ARRAYSIZE(console_input));
                ImGui::SameLine();
                // ImGui::PopFont();

                if ((ImGui::Button("Submit") || YE::input::Keyboard::IsKeyPressed(YE::input::Key::YE_KEY_RETURN))
                    && IM_ARRAYSIZE(console_input) > 0 && console_input[0] != '\0' && console_input[0] != '\n') {
                    
                    console_display.push_back(std::string(console_input));
                    memset(console_input , 0 , IM_ARRAYSIZE(console_input));

                }

            }
            ImGui::End();

        }

};

#endif