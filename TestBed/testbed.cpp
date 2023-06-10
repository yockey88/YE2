#include "ft2build.h"
#include FT_FREETYPE_H

#include "YE2.hpp"

#include "console.hpp"
#include "scripts/native_scripts/test_native_entity.hpp"

#include <iostream>
#include <fstream>

struct Character {

    unsigned int texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;

};

std::map<char , Character> characters;

class TestBed : public YE::YApp {

    DebugConsole console;

    ImFont* clacon_font = nullptr;
    ImFont* vera_font   = nullptr;

    std::shared_ptr<YE::game::Scene> scene;
    std::shared_ptr<YE::rendering::Camera> camera;

    std::shared_ptr<YE::rendering::Shader> text_shader;
    
    
    FT_Library ft_library = nullptr;
    FT_Face ft_face       = nullptr;

    bool show_demo_window = true;
    bool show_console     = true;

    uint32_t vao;
    uint32_t vbo;

    std::string ex_text = "This is some text I am rendering";

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

            text_shader = std::make_shared<YE::rendering::Shader>("shaders/text_shader.vert" , "shaders/text_shader.frag");

            glGenVertexArrays(1 , &vao);
            glGenBuffers(1 , &vbo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER , vbo);
            glBufferData(GL_ARRAY_BUFFER , sizeof(float) * 6 * 4 , NULL , GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0 , 4 , GL_FLOAT , GL_FALSE , 4 * sizeof(float) , 0);
            glBindBuffer(GL_ARRAY_BUFFER , 0);
            glBindVertexArray(0);

            camera = std::make_shared<YE::rendering::Camera>();

            glm::vec3 camera_pos = glm::vec3(0.f , 0.f , 2.f);
            glm::vec3 camera_front = glm::vec3(0.f , 0.f , -1.f);
            glm::vec3 camera_up = glm::vec3(0.f , 1.f , 0.f);

            camera->m_Position = camera_pos;
            camera->m_Front    = camera_front;
            camera->m_Up       = camera_up;

            // YE::game::Entity ent_handle = scene->CreateEntity(1 , "Test Ent");

            // clacon_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/clacon2.ttf" , 13.0f);
            // vera_font   = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/Vera.ttf" , 13.0f);

            if (FT_Init_FreeType(&ft_library)) {
            
                YE_FATAL("Failed to initialize FreeType");
                return false;

            }

            if (FT_New_Face(ft_library , "res/fonts/Arial.ttf" , 0 , &ft_face)) {
                
                YE_FATAL("Failed to load font");
                return false;

            }

            FT_Set_Pixel_Sizes(ft_face , 0 , 48);

            glPixelStorei(GL_UNPACK_ALIGNMENT , 1);

            for (unsigned char c = 0; c < 128; c++) {

                if (FT_Load_Char(ft_face , c , FT_LOAD_RENDER)) {

                    YE_WARN("Failed to load glyph");
                    continue;

                }

                unsigned int texture;
                glGenTextures(1 , &texture);
                glBindTexture(GL_TEXTURE_2D , texture);
                glTexImage2D(GL_TEXTURE_2D , 0 , GL_RED , ft_face->glyph->bitmap.width , ft_face->glyph->bitmap.rows , 
                             0 , GL_RED , GL_UNSIGNED_BYTE , ft_face->glyph->bitmap.buffer);

                glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

                Character character = {

                    texture,
                    glm::ivec2(ft_face->glyph->bitmap.width , ft_face->glyph->bitmap.rows),
                    glm::ivec2(ft_face->glyph->bitmap_left  , ft_face->glyph->bitmap_top),
                    ft_face->glyph->advance.x

                };

                characters[c] = character;

                glPixelStorei(GL_UNPACK_ALIGNMENT , 1);

            }

            glBindTexture(GL_TEXTURE_2D , 0);

            FT_Done_Face(ft_face);
            FT_Done_FreeType(ft_library);

            YE_INFO("TestBed Initialized");

            return true;

        }

        virtual void Update() override { 

            scene->Update();

            if (YE::input::Mouse::IsButtonPressed(YE::input::MouseButton::YE_MOUSE_LEFT)) {

                YE_INFO("Left mouse button pressed");

            }

        } 
        
        virtual void Render() override {
            
            glm::mat4 proj = glm::mat4(1.0f);

            camera->GetProjectionMatrix(proj);

            text_shader->Bind();
            text_shader->SetUniformVec3("tex_color" , { 1.f , 1.f , 1.f });
            text_shader->SetUniformMat4("proj" , proj);

            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(vao);

            float x     = 500.f;
            float y     = 500.f;
            float scale = 1.f;

            std::string::const_iterator c;
            for (c = ex_text.begin(); c != ex_text.end(); c++) {

                Character ch = characters[*c];

                float xpos = x + ch.bearing.x * scale;
                float ypos = y - (ch.size.y - ch.bearing.y) * scale;

                float w = ch.size.x * scale;
                float h = ch.size.y * scale;

                float vertices[6][4] = {

                    { xpos     , ypos + h , 0.f , 0.f } ,
                    { xpos     , ypos     , 0.f , 1.f } ,
                    { xpos + w , ypos     , 1.f , 1.f } ,

                    { xpos      , ypos + h , 0.f , 0.f } ,
                    { xpos  + w , ypos     , 1.f , 1.f } ,
                    { xpos  + w , ypos + h , 1.f , 0.f } 

                };

                glBindTexture(GL_TEXTURE_2D , ch.texture_id);
                glBindBuffer(GL_ARRAY_BUFFER , vbo);
                glBufferSubData(GL_ARRAY_BUFFER , 0 , sizeof(vertices) , vertices);
                glBindBuffer(GL_ARRAY_BUFFER , 0);

                glDrawArrays(GL_TRIANGLES , 0 , 6);

                x += (ch.advance >> 6) * scale;

            }
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D , 0);
            
            text_shader->Unbind();

        }
        
        virtual void RenderGUI() override {

            if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

            if (show_console) console.Render(&show_console);

        }
        
};

YE::YApp* YE::CreateApp() { return new TestBed; }