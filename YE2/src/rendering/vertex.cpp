#include "log.hpp"

#include "rendering/vertex.hpp"

#include <cassert>

void CheckGLError(const std::string& file , int line) { 
    GLenum err = glGetError(); 
    bool assert = err != GL_NO_ERROR; 
    while (err != GL_NO_ERROR) { 
        YE_ERROR("OpenGL Error {} [{}:{}]" , err , file , line);
        std::string errstr; 
        switch (err) { 
            case GL_INVALID_OPERATION: errstr = "INVALID OPERATION"; break; 
            case GL_INVALID_ENUM: errstr = "INVALID ENUM"; break; 
            case GL_INVALID_VALUE: errstr = "INVALID VALUE"; break; 
            case GL_OUT_OF_MEMORY: errstr = "OUT OF MEMORY"; break; 
            case GL_INVALID_FRAMEBUFFER_OPERATION: errstr = "INVALID FRAMEBUFFER OPERATION"; break; 
            default: errstr = std::to_string(err); break; 
        } 

        YE_ERROR("OpenGl Error {} : [{}:{}]" , errstr , file , line); 
        err = glGetError(); 
    } 
    assert(assert); 
}

namespace YE {
namespace rendering {

    VertexArray::VertexArray(const std::vector<Vertex>& verts) {
        for (const auto& i : verts)
            m_Verts.push_back(i);
    }

    VertexArray::VertexArray(const std::vector<Vertex>& verts , const std::vector<uint32_t>& elements) {
        for (const auto& i : verts)
            m_Verts.push_back(i);
        for (const auto& i : elements)
            m_Elements.push_back(i);
    }

    VertexArray::~VertexArray() {
        if (m_Valid) {
            glDeleteBuffers(1 , &EBO); 
            glDeleteBuffers(1 , &VBO); 
            glDeleteVertexArrays(1 , &VAO); 
        }
    }

    void VertexArray::Draw(int draw_type) const {
        if (!m_Valid) {
            YE_ERROR("Error: Invalid vertex array");
            return;
        }

        if (m_Elements.size() > 0) {
            glDrawElements(draw_type , (uint32_t)m_Elements.size() , GL_UNSIGNED_INT , (void*)0);
        } else {
            glDrawArrays(draw_type , 0 , (uint32_t)m_Verts.size());
        }
    }

    bool VertexArray::Upload() {

        if (m_Verts.size() == 0) {
            YE_ERROR("No vertices to upload : Corrupt vertex array");
            m_Valid = false;
            return false;
        }

        std::vector<float> vertex_data{};
        for (auto& v : m_Verts) {
            vertex_data.push_back(v.position.x);
            vertex_data.push_back(v.position.y);
            vertex_data.push_back(v.position.z);

            vertex_data.push_back(v.color.x);
            vertex_data.push_back(v.color.y);
            vertex_data.push_back(v.color.z);

            vertex_data.push_back(v.normal.x);
            vertex_data.push_back(v.normal.y);
            vertex_data.push_back(v.normal.z);

            vertex_data.push_back(v.tangent.x);
            vertex_data.push_back(v.tangent.y);
            vertex_data.push_back(v.tangent.z);

            vertex_data.push_back(v.bitangent.x);
            vertex_data.push_back(v.bitangent.y);
            vertex_data.push_back(v.bitangent.z);

            vertex_data.push_back(v.tex_coord.x);
            vertex_data.push_back(v.tex_coord.y);

            vertex_data.push_back(v.opacity);
        }

        glGenVertexArrays(1 , &VAO);
        glGenBuffers(1 , &VBO);
        if (m_Elements.size() > 0) glGenBuffers(1 , &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER , VBO);
        glBufferData(GL_ARRAY_BUFFER , vertex_data.size() * sizeof(float) , vertex_data.data() , GL_STATIC_DRAW);

        if (m_Elements.size() > 0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER , m_Elements.size() * sizeof(uint32_t) , m_Elements.data() , GL_STATIC_DRAW);
        }

        uint32_t attrib_cnt = 0;
        uint32_t offset = 0;
        for (auto& i : YE::rendering::Vertex::layout()) {
            glVertexAttribPointer(attrib_cnt , i , GL_FLOAT , GL_FALSE , 18 * sizeof(float) , (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(attrib_cnt);

            offset += i;
            attrib_cnt++;
        }

        glBindVertexArray(0);

        m_Valid = true;

        return true;
    }

}
}