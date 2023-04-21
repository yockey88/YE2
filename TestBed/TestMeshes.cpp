#include "TestMeshes.hpp"

#include "stb_image.h"

namespace YE {
namespace dev {



    bool CubeMap::LoadCubeMap(const std::vector<std::string>& faces) {
        std::vector<std::string> paths{};
        if (faces.size() != 6) {
            std::cout << "CubeMap::LoadCubeMap: faces.size() != 6" << std::endl;
            m_Valid = false;
            return false;
        } else {
            for (auto& f : faces) {
                paths.push_back("res/" + f);
            }
        }

        int width , height , nrChannels , i = 0;
        for (const auto& f : paths) {
            unsigned char* data = stbi_load(f.c_str() , &width , &height , &nrChannels , 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i , 0 , GL_RGB , width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , data);
                stbi_image_free(data);
            } else {
                std::cout << "Cubemap texture failed to load at path: " << f << std::endl;
                stbi_image_free(data);
                m_Valid = false;
                return false;
            }
            i++;
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_R , GL_CLAMP_TO_EDGE);

        m_Valid = true;

        return true;
    }   
    
    CubeMap::CubeMap(const std::vector<std::string>& faces) {
        glGenVertexArrays(1 , &m_VAO);
        glBindVertexArray(m_VAO);

        float skybox_verts[] = {
            -1.0f ,  1.0f , -1.0f , -1.0f, -1.0f, -1.0f,
             1.0f , -1.0f , -1.0f ,  1.0f, -1.0f, -1.0f,
             1.0f ,  1.0f , -1.0f , -1.0f ,  1.0f , -1.0f ,

            -1.0f , -1.0f ,  1.0f , -1.0f , -1.0f , -1.0f ,
            -1.0f ,  1.0f , -1.0f , -1.0f ,  1.0f , -1.0f ,
            -1.0f ,  1.0f ,  1.0f , -1.0f , -1.0f ,  1.0f ,

             1.0f , -1.0f , -1.0f , 1.0f , -1.0f ,  1.0f ,
             1.0f ,  1.0f ,  1.0f , 1.0f ,  1.0f ,  1.0f ,
             1.0f ,  1.0f , -1.0f , 1.0f , -1.0f , -1.0f ,

            -1.0f , -1.0f ,  1.0f , -1.0f ,  1.0f ,  1.0f ,
             1.0f ,  1.0f ,  1.0f ,  1.0f ,  1.0f ,  1.0f , 
             1.0f , -1.0f ,  1.0f , -1.0f , -1.0f ,  1.0f ,

            -1.0f ,  1.0f , -1.0f , 1.0f ,  1.0f , -1.0f ,
             1.0f ,  1.0f ,  1.0f , 1.0f ,  1.0f ,  1.0f ,
            -1.0f ,  1.0f ,  1.0f , -1.0f ,  1.0f , -1.0f ,

            -1.0f , -1.0f , -1.0f , -1.0f , -1.0f ,  1.0f ,
             1.0f , -1.0f , -1.0f ,  1.0f , -1.0f , -1.0f ,
            -1.0f , -1.0f ,  1.0f ,  1.0f , -1.0f ,  1.0f
        };

        glGenBuffers(1 , &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER , m_VBO);
        glBufferData(GL_ARRAY_BUFFER , sizeof(skybox_verts) , skybox_verts , GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);

        glBindVertexArray(0);

        m_Shader = std::make_unique<rendering::Shader>("shaders/skybox.vert" , "shaders/skybox.frag");

        glm::mat4 sky_box_model{ 1.f };
        sky_box_model = glm::scale(sky_box_model , glm::vec3(100.f , 100.f , 100.f));

        m_Shader->Bind();
        m_Shader->SetUniformInt("skybox" , 0);
        m_Shader->SetUniformMat4("model" , sky_box_model);
        m_Shader->Unbind();

        glGenTextures(1 , &m_TextID);
        glBindTexture(GL_TEXTURE_CUBE_MAP , m_TextID);

        if (!LoadCubeMap(faces)) {
            m_Valid = false;
            return;
        }
    }

    CubeMap::~CubeMap() {
        if (m_Valid) {
            glDeleteTextures(1 , &m_TextID);
            glDeleteBuffers(1 , &m_VBO);
            glDeleteVertexArrays(1 , &m_VAO);
        }
    }

    void CubeMap::Draw(const glm::mat4& view , const glm::mat4& proj) {
        if (m_Valid) {
            glDepthFunc(GL_LEQUAL);
            glBindTexture(GL_TEXTURE_CUBE_MAP , m_TextID);
            m_Shader->Bind();
            m_Shader->SetUniformMat4("view" , view);
            m_Shader->SetUniformMat4("proj" , proj);
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES , 0 , 36);
            glBindVertexArray(0);
            m_Shader->Unbind();
            glBindTexture(GL_TEXTURE_CUBE_MAP , 0);
            glDepthFunc(GL_LESS);
        }
    }

    Quad::Quad() {
        quad_va = std::make_unique<YE::rendering::VertexArray>(verts , tvd.elements);
        if (quad_va->Upload()) {
            printf("Uploaded quad VA\n");
            valid = true;
        }
    }

    void Quad::Draw() {
        if (valid) {
            quad_va->Bind();
            quad_va->Draw();
            quad_va->Unbind();
        }
    }
        
    Cube::Cube() {
        f1 = std::make_unique<YE::rendering::VertexArray>(f1_verts , tvd.elements);
        f2 = std::make_unique<YE::rendering::VertexArray>(f2_verts , tvd.elements);
        f3 = std::make_unique<YE::rendering::VertexArray>(f3_verts , tvd.elements);
        f4 = std::make_unique<YE::rendering::VertexArray>(f4_verts , tvd.elements);
        f5 = std::make_unique<YE::rendering::VertexArray>(f5_verts , tvd.elements);
        f6 = std::make_unique<YE::rendering::VertexArray>(f6_verts , tvd.elements);

        if (f1->Upload() && f2->Upload() && f3->Upload() &&
            f4->Upload() && f5->Upload() && f6->Upload()) {
            printf("Uploaded face VAs\n");
            valid = true;
        }
    }

    void Cube::Draw() {
        if (valid) {
            f1->Bind();
            f1->Draw();
            f1->Unbind();

            f2->Bind();
            f2->Draw();
            f2->Unbind();

            f3->Bind();
            f3->Draw();
            f3->Unbind();

            f4->Bind();
            f4->Draw();
            f4->Unbind();

            f5->Bind();
            f5->Draw();
            f5->Unbind();

            f6->Bind();
            f6->Draw();
            f6->Unbind();
        }
    }

}
}