#include "log.hpp"

#include "rendering/frame_buffer.hpp"

namespace YE {
namespace rendering {

    Framebuffer::Framebuffer(uint32_t width , uint32_t height) {

        m_Size = glm::vec2(width , height);

        glGenVertexArrays(1 , &m_VAO);
        glGenBuffers(1 , &m_VBO);
        glGenBuffers(1 , &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER , m_VBO);
        glBufferData(GL_ARRAY_BUFFER , sizeof(m_Verts) , m_Verts , GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(m_Elements) , m_Elements , GL_STATIC_DRAW);

        std::vector<uint32_t> layout{ 2 , 2 };
        uint32_t attrib_cnt = 0;
        uint32_t offset = 0;
        for (auto& i : layout) {
            glVertexAttribPointer(attrib_cnt , i , GL_SHORT , GL_FALSE , 4 * sizeof(short) , (void*)(offset * sizeof(short)));
            glEnableVertexAttribArray(attrib_cnt);

            offset += i;
            attrib_cnt++;
        }

        glBindVertexArray(0);

        // MSAA Framebuffer
        glGenFramebuffers(1 , &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER , m_FBO);

        glGenTextures(1 , &m_Texture);
        glBindTexture(GL_TEXTURE_2D , m_Texture);
        glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGB , (GLsizei)m_Size.x , (GLsizei)m_Size.y , 0 , GL_RGB , GL_UNSIGNED_BYTE , NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D , 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D , m_Texture , 0);

        glGenRenderbuffers(1 , &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER , m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER , GL_DEPTH24_STENCIL8 , (GLsizei)m_Size.x , (GLsizei)m_Size.y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER , GL_DEPTH_STENCIL_ATTACHMENT , GL_RENDERBUFFER , m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER , 0);

        uint32_t status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        YE_ASSERT(status == GL_FRAMEBUFFER_COMPLETE , "Framebuffer is not complete!");
        (status != GL_FRAMEBUFFER_COMPLETE) ? m_Valid = false : m_Valid = true;

        glBindFramebuffer(GL_FRAMEBUFFER , 0);

        // // Post-Processing Framebuffer
        // glGenFramebuffers(1 , &m_Anti_alias_FBO);
        // glBindFramebuffer(GL_FRAMEBUFFER , m_Anti_alias_FBO);

        // glGenTextures(1 , &m_Anti_alias_texture);
        // glBindTexture(GL_TEXTURE_2D , m_Anti_alias_texture);
        // glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGB , m_Size.x , m_Size.y , 0 , GL_RGB , GL_UNSIGNED_BYTE , NULL);
        // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
        // glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D , m_Anti_alias_texture , 0);

        // uint32_t status2 = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        // if (status2 != GL_FRAMEBUFFER_COMPLETE) {
        //     std::cout << "Framebuffer is not complete!" << std::endl;
        //     m_Valid = false;
        // } else {
        //     m_Valid = true;
        // }

        // glBindFramebuffer(GL_FRAMEBUFFER , 0);
    }
    
    Framebuffer::~Framebuffer() {
        if (m_Valid) {
            glDeleteBuffers(1 , &m_EBO); 
            glDeleteBuffers(1 , &m_VBO); 
            glDeleteVertexArrays(1 , &m_VAO);
            glDeleteRenderbuffers(1 , &m_RBO);
            glDeleteTextures(1 , &m_Texture);
            glDeleteFramebuffers(1 , &m_FBO);
            // glDeleteTextures(1 , &m_Anti_alias_texture);
            // glDeleteFramebuffers(1 , &m_Anti_alias_FBO);
        }
    }
    
    void Framebuffer::Draw() {
        glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);
        // glDrawArrays(GL_TRIANGLES , 0 , 6);
    }

    void Framebuffer::BindFrame() {
        glBindFramebuffer(GL_FRAMEBUFFER , m_FBO);
        glViewport(0 , 0 , (GLsizei)m_Size.x , (GLsizei)m_Size.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void Framebuffer::BindMesh() {
        glBindVertexArray(m_VAO);
    }

    void Framebuffer::BindTexture() {
        glBindTexture(GL_TEXTURE_2D , m_Texture);
    }

    void Framebuffer::UnbindFrame() {
        // glBindFramebuffer(GL_READ_FRAMEBUFFER , m_FBO);
        // glBindFramebuffer(GL_DRAW_FRAMEBUFFER , m_Anti_alias_FBO);
        // glBlitFramebuffer(0 , 0 , m_Size.x , m_Size.y , 0 , 0 , m_Size.x , m_Size.y , GL_COLOR_BUFFER_BIT , GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER , 0);
    }

    void Framebuffer::UnbindMesh() {
        glBindVertexArray(0);
    }

    void Framebuffer::UnbindTexture() {
        glBindTexture(GL_TEXTURE_2D , 0);
    }

}
}