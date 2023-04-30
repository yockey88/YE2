#ifndef YE_TESTBED_TESTMESHES_HPP
#define YE_TESTBED_TESTMESHES_HPP

#include "stb_image.h"
#include "asmjit/asmjit.h"

#include "YE2.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <memory>
#include <chrono>

// GUI Functions
bool Decompose(const glm::mat4& transform , glm::vec3& translation , glm::vec3& rotation , glm::vec3& scale);
void LightGUI(glm::vec3& pos , glm::vec3& ambient , glm::vec3& diffuse , glm::vec3& specular);
void CameraGUI(YE::rendering::Camera& camera);
void BoxGUI(glm::vec3& box_pos , glm::vec3& box_scale);

// Testing Data
class TestVertData {
    glm::vec3  p1{  0.5f ,  0.5f ,  0.5f };
    glm::vec3  p2{  0.5f , -0.5f ,  0.5f };
    glm::vec3  p3{ -0.5f , -0.5f ,  0.5f };
    glm::vec3  p4{ -0.5f ,  0.5f ,  0.5f };

    glm::vec3  p5{  0.5f ,  0.5f , -0.5f };
    glm::vec3  p6{  0.5f , -0.5f , -0.5f };
    glm::vec3  p7{ -0.5f , -0.5f , -0.5f };
    glm::vec3  p8{ -0.5f ,  0.5f , -0.5f };

    glm::vec3  c1{ 0.5f , 0.2f , 0.7f };
    glm::vec3  c2{ 0.5f , 0.2f , 0.7f };
    glm::vec3  c3{ 0.5f , 0.2f , 0.7f };
    glm::vec3  c4{ 0.5f , 0.2f , 0.7f };

    glm::vec3  nPosY{  0.0f ,  1.0f ,  0.0f };
    glm::vec3  nNegY{  0.0f , -1.0f ,  0.0f };
    glm::vec3  nPosX{  1.0f ,  0.0f ,  0.0f };
    glm::vec3  nNegX{ -1.0f ,  0.0f ,  0.0f };
    glm::vec3  nPosZ{  0.0f ,  0.0f ,  1.0f };
    glm::vec3  nNegZ{  0.0f ,  0.0f , -1.0f };

    glm::vec3 tan1{ 1.f , 0.f , 0.f };
    glm::vec3 tan2{ 1.f , 0.f , 0.f };
    glm::vec3 tan3{ 1.f , 0.f , 0.f };
    glm::vec3 tan4{ 1.f , 0.f , 0.f };

    glm::vec3 bitan1{ 0.f , 1.f , 0.f };
    glm::vec3 bitan2{ 0.f , 1.f , 0.f };
    glm::vec3 bitan3{ 0.f , 1.f , 0.f };
    glm::vec3 bitan4{ 0.f , 1.f , 0.f };

    glm::vec2  t1{ 1.f , 1.f };
    glm::vec2  t2{ 1.f , 0.f };
    glm::vec2  t3{ 0.f , 0.f };
    glm::vec2  t4{ 0.f , 1.f };

    float opacity = 1.0f;

    public:
        YE::rendering::Vertex  v1 = YE::rendering::Vertex(p1 , c1  , nPosZ , tan1 , bitan1 , t1  , opacity);
        YE::rendering::Vertex  v2 = YE::rendering::Vertex(p2 , c2  , nPosZ , tan2 , bitan2 , t2  , opacity);
        YE::rendering::Vertex  v3 = YE::rendering::Vertex(p3 , c3  , nPosZ , tan3 , bitan3 , t3  , opacity);
        YE::rendering::Vertex  v4 = YE::rendering::Vertex(p4 , c4  , nPosZ , tan4 , bitan4 , t4  , opacity);

        YE::rendering::Vertex  v5 = YE::rendering::Vertex(p5 , c1  , nNegZ , tan1 , bitan1 , t1  , opacity);
        YE::rendering::Vertex  v6 = YE::rendering::Vertex(p6 , c2  , nNegZ , tan2 , bitan2 , t2  , opacity);
        YE::rendering::Vertex  v7 = YE::rendering::Vertex(p7 , c3  , nNegZ , tan3 , bitan3 , t3  , opacity);
        YE::rendering::Vertex  v8 = YE::rendering::Vertex(p8 , c4  , nNegZ , tan4 , bitan4 , t4  , opacity);

        YE::rendering::Vertex  v9 = YE::rendering::Vertex(p5 , c1  , nPosX , tan1 , bitan1 , t1  , opacity);
        YE::rendering::Vertex v10 = YE::rendering::Vertex(p6 , c2  , nPosX , tan2 , bitan2 , t2  , opacity);
        YE::rendering::Vertex v11 = YE::rendering::Vertex(p2 , c2  , nPosX , tan3 , bitan3 , t3  , opacity);
        YE::rendering::Vertex v12 = YE::rendering::Vertex(p1 , c1  , nPosX , tan4 , bitan4 , t4  , opacity);

        YE::rendering::Vertex v13 = YE::rendering::Vertex(p4 , c4  , nNegX , tan1 , bitan1 , t1  , opacity);
        YE::rendering::Vertex v14 = YE::rendering::Vertex(p3 , c3  , nNegX , tan2 , bitan2 , t2  , opacity);
        YE::rendering::Vertex v15 = YE::rendering::Vertex(p7 , c3  , nNegX , tan3 , bitan3 , t3  , opacity);
        YE::rendering::Vertex v16 = YE::rendering::Vertex(p8 , c4  , nNegX , tan4 , bitan4 , t4  , opacity);

        YE::rendering::Vertex v17 = YE::rendering::Vertex(p5 , c1  , nPosY , tan1 , bitan1 , t1  , opacity);
        YE::rendering::Vertex v18 = YE::rendering::Vertex(p1 , c1  , nPosY , tan2 , bitan2 , t2  , opacity);
        YE::rendering::Vertex v19 = YE::rendering::Vertex(p4 , c4  , nPosY , tan3 , bitan3 , t3  , opacity);
        YE::rendering::Vertex v20 = YE::rendering::Vertex(p8 , c4  , nPosY , tan4 , bitan4 , t4  , opacity);

        YE::rendering::Vertex v21 = YE::rendering::Vertex(p6 , c2  , nNegY , tan1 , bitan1 , t1  , opacity);
        YE::rendering::Vertex v22 = YE::rendering::Vertex(p2 , c2  , nNegY , tan2 , bitan2 , t2  , opacity);
        YE::rendering::Vertex v23 = YE::rendering::Vertex(p3 , c3  , nNegY , tan3 , bitan3 , t3  , opacity);
        YE::rendering::Vertex v24 = YE::rendering::Vertex(p7 , c3  , nNegY , tan4 , bitan4 , t4  , opacity);

        std::vector<uint32_t> elements{ 0 , 3 , 1 , 1 , 3 , 2 };
};
namespace YE {
namespace dev {
    
    // class Space {
    //     public:
    //         Scene() = default;
    //         virtual ~Scene() = default;

    //         virtual void OnUpdate() = 0;
    //         virtual void OnRender() = 0;
    //         virtual void OnImGuiRender() = 0;
    // };

    template <std::intmax_t FPS>
    class FrameRateEnforcer {
        std::chrono::duration<double , std::ratio<1 , FPS>> m_Frame_duration;
        std::chrono::time_point<std::chrono::high_resolution_clock , decltype(m_Frame_duration)> m_Time_point;

        public:
            FrameRateEnforcer() { m_Time_point = std::chrono::high_resolution_clock::now(); }

            inline float GetTimeStep() const { return (float)(1.f / FPS); }

            void Enforce() {
                m_Time_point += m_Frame_duration;

                std::this_thread::sleep_until(m_Time_point);
            }
    };

    class CubeMap {
        std::unique_ptr<rendering::Shader> m_Shader = nullptr;
        bool LoadCubeMap(const std::vector<std::string>& faces);

        CubeMap(CubeMap const&) = delete;
        CubeMap(CubeMap&&) = delete;
        CubeMap& operator=(CubeMap const&) = delete;
        public:
            uint32_t m_VAO = 0 , m_VBO = 0;
            uint32_t m_TextID;        
            bool m_Valid = false;
            std::vector<rendering::Texture> m_Textures[6];
            CubeMap(const std::vector<std::string>& faces);
            ~CubeMap();
            void Draw(const glm::mat4& view , const glm::mat4& proj);
    };

    class Quad {
        TestVertData tvd;
        std::unique_ptr<rendering::VertexArray> quad_va = nullptr;
        std::vector<rendering::Vertex> verts{ tvd.v17 , tvd.v18 , tvd.v19 , tvd.v20 };

        bool valid = false;
        public:
            Quad();
            void Draw();
    };

    class Cube {
        TestVertData tvd;
        std::unique_ptr<YE::rendering::VertexArray> f1 = nullptr;
        std::unique_ptr<YE::rendering::VertexArray> f2 = nullptr;
        std::unique_ptr<YE::rendering::VertexArray> f3 = nullptr;
        std::unique_ptr<YE::rendering::VertexArray> f4 = nullptr;
        std::unique_ptr<YE::rendering::VertexArray> f5 = nullptr;
        std::unique_ptr<YE::rendering::VertexArray> f6 = nullptr;
        std::vector<YE::rendering::Vertex> f1_verts{ tvd.v1  , tvd.v2  , tvd.v3  , tvd.v4 };
        std::vector<YE::rendering::Vertex> f2_verts{ tvd.v5  , tvd.v6  , tvd.v7  , tvd.v8 };
        std::vector<YE::rendering::Vertex> f3_verts{ tvd.v9  , tvd.v10 , tvd.v11 , tvd.v12 };
        std::vector<YE::rendering::Vertex> f4_verts{ tvd.v13 , tvd.v14 , tvd.v15 , tvd.v16 };
        std::vector<YE::rendering::Vertex> f5_verts{ tvd.v17 , tvd.v18 , tvd.v19 , tvd.v20 };
        std::vector<YE::rendering::Vertex> f6_verts{ tvd.v21 , tvd.v22 , tvd.v23 , tvd.v24 };

        bool valid = false;
        public:
            Cube();
            void Draw();
    };

}
}

/*

    YE::rendering::SDL2_Config config{};
    config.title = "YE2";
    config.cc = glm::vec4(0.3f , 0.3f , 0.333f , 1.0f);
    config.x = SDL_WINDOWPOS_CENTERED;
    config.y = SDL_WINDOWPOS_CENTERED;
    config.w = 1440; // 800;
    config.h = 1080; // 600;
    config.render_to_screen = true;
    config.flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

    YE::rendering::SDL2 sdl;

    if (!sdl.CreateWindow(&config)) {
        printf("Unable to create window: %s", SDL_GetError());
        return 1;
    }
    // End of Window Setup

    // ImGui Setup



    // Setup Dear ImGui context

    // Frame Rate Control 
    YE::dev::FrameRateEnforcer<60> frame_rate;
    // End of Frame Rate Control

    // // Camera Data 
    YE::rendering::Camera camera{};
    camera.m_Position = glm::vec3(0.0f , 3.f ,  3.0f);
    camera.m_Front = glm::vec3(0.0f , -3.f , -3.0f);
    camera.m_Up = glm::vec3(0.0f , 1.0f , -1.f);

    glm::vec3 camera_pos = camera.m_Position;
    glm::vec3 camera_front = camera.m_Front;
    glm::vec3 camera_up = camera.m_Up;
    
    glm::mat4 view(1.f);
    glm::mat4 proj(1.f);

    sdl.m_Camera = &camera;

    camera.GetViewMatrix(view);
    camera.GetProjectionMatrix(proj);
    // End of Camera Data

    // Light Properties
    YE::rendering::Shader light_shader("shaders/light_cube.vert" , "shaders/light_cube.frag");

    std::unique_ptr<YE::dev::Cube> light_cube = std::make_unique<YE::dev::Cube>();

    glm::vec3 light_pos = glm::vec3(0.f , 1.f , 0.f);
    glm::vec3 light_color = glm::vec3(1.f , 1.f , 1.f);
    glm::vec3 diffuse_color = light_color * glm::vec3(1.f);
    glm::vec3 ambient_color = diffuse_color * glm::vec3(0.2f);
    glm::vec3 specular_color = glm::vec3(1.f , 1.f , 1.f);

    glm::mat4 light_model = glm::mat4(1.0f);
    light_model = glm::translate(light_model , light_pos);
    light_model = glm::scale(light_model , glm::vec3(0.2f , 0.2f , 0.2f));

    light_shader.Bind();
    light_shader.SetUniformMat4("model" , light_model);
    light_shader.SetUniformMat4("view" , view);
    light_shader.SetUniformMat4("proj" , proj);
    light_shader.Unbind();
    // End of Light Properties

    // Cubemap
    std::vector<std::string> faces{
        "skybox/right.jpg" ,
        "skybox/left.jpg" ,
        "skybox/top.jpg" ,
        "skybox/bottom.jpg" ,
        "skybox/front.jpg" ,
        "skybox/back.jpg"
    };
    
    std::unique_ptr<YE::dev::CubeMap> skybox = std::make_unique<YE::dev::CubeMap>(faces);
    // End of Cubemap

    // Object Control
    YE::rendering::Shader shader("shaders/materials.vert" , "shaders/materials.frag");
    YE::rendering::Texture tex("images/container2.png");

    std::unique_ptr<YE::dev::Cube> box  = std::make_unique<YE::dev::Cube>();
    std::unique_ptr<YE::dev::Cube> box1 = std::make_unique<YE::dev::Cube>();
    std::unique_ptr<YE::dev::Cube> box2 = std::make_unique<YE::dev::Cube>();

    glm::vec3 box_pos{ 0.f , 0.f , 0.f };
    glm::vec3 box1_pos{ -1.f , 0.f , 0.f };
    glm::vec3 box2_pos{  1.f , 0.f , 0.f };

    glm::vec3 box_size{ 0.5f , 0.5f , 0.5f };
    glm::vec3 box1_2_size{ 0.2f  , 0.2f , 0.2f };

    glm::mat4 box_model = glm::mat4(1.0f);
    box_model = glm::translate(box_model , box_pos);
    box_model = glm::scale(box_model , box_size);

    glm::mat4 box1_model = glm::mat4(1.0f);
    box1_model = glm::translate(box1_model , box1_pos);
    box1_model = glm::scale(box1_model , box1_2_size);
    
    glm::mat4 box2_model = glm::mat4(1.0f);
    box2_model = glm::translate(box2_model , box2_pos);
    box2_model = glm::scale(box2_model , box1_2_size);

    shader.Bind();
    shader.SetUniformInt("tex" , 0);
    shader.SetUniformVec3("material.ambient" , ambient_color);
    shader.SetUniformVec3("material.diffuse" , diffuse_color);
    shader.SetUniformVec3("material.specular" , specular_color);
    shader.SetUniformFloat("material.shininess" , 99.0f);
    shader.SetUniformVec3("light.position" , light_pos);
    shader.SetUniformVec3("light.ambient" , ambient_color);
    shader.SetUniformVec3("light.diffuse" , diffuse_color);
    shader.SetUniformVec3("light.specular" , specular_color);
    shader.SetUniformMat4("view" , view);
    shader.SetUniformMat4("proj" , proj);
    shader.Unbind();
    // End of Object Control

    // Running
    while (sdl.m_Running) {

        camera.Recalculate();
        view = camera.GetViewMatrix();
        proj = camera.GetProjectionMatrix();

        light_model = glm::mat4(1.0f);
        light_model = glm::translate(light_model , light_pos);
        light_model = glm::scale(light_model , glm::vec3(0.2f , 0.2f , 0.2f));

        { // Rendering
            sdl.BeginRender();

            tex.Bind();
            shader.Bind();
            shader.SetUniformMat4("view" , view);
            shader.SetUniformMat4("model" , box_model);
            shader.SetUniformVec3("light.position" , light_pos);
            shader.SetUniformVec3("light.ambient" , ambient_color);
            shader.SetUniformVec3("light.diffuse" , diffuse_color);
            shader.SetUniformVec3("light.specular" , specular_color);
            box->Draw();
            shader.SetUniformMat4("model" , box1_model);
            box1->Draw();
            shader.SetUniformMat4("model" , box2_model);
            box2->Draw();
            shader.Unbind();
            tex.Unbind();

            light_shader.Bind();
            light_shader.SetUniformMat4("view" , view);
            light_shader.SetUniformMat4("model" , light_model);
            light_shader.SetUniformVec3("light.position" , light_pos);
            light_shader.SetUniformVec3("light.diffuse" , diffuse_color * glm::vec3(0.2f));
            light_cube->Draw();
            light_shader.Unbind();

            skybox->Draw(view , proj);

            LightGUI(light_pos , ambient_color , diffuse_color , specular_color);
            CameraGUI(camera);

            sdl.EndRender();
        }

        frame_rate.Enforce();
    }
    // End of Rendering

*/

/*



*/

#endif