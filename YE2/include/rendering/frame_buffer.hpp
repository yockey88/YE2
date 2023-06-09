#ifndef YE_FRAME_BUFFER_HPP
#define YE_FRAME_BUFFER_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <iostream>
#include <stdint.h>
#include <vector>

namespace YE {
namespace rendering {

    /** Framebuffer class
     *   -> wraps framebuffer functionality from OpenGL
     *   -> draws to a texture, but there is not much functionality yet
     *          eventually this should be able to draw to a texture to allow for post processing and
     *          other effects as well as using the render as any other texture.
    */
    class Framebuffer {
        const short m_Verts[16] = {  1 ,  1 , 1 , 1   ,    1 , -1 , 1 , 0 ,
                                    -1 , -1 , 0 , 0   ,   -1 ,  1 , 0 , 1 };
        const uint32_t m_Elements[6] = { 0 , 3 , 1 , 1 , 3 , 2 };

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer(Framebuffer&&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;
        public:
            uint32_t m_Anti_alias_FBO = 0 , m_Anti_alias_texture = 0;
            uint32_t m_FBO = 0 , m_RBO = 0 , m_Texture = 0;
            uint32_t m_VAO = 0 , m_VBO = 0 , m_EBO = 0;
            uint32_t m_DepthTexture = 0;
            glm::vec2 m_Size{ 0 , 0 };
            glm::vec4 m_Clear_color{ 0.0f , 0.0f , 0.0f , 1.0f };
            bool m_Valid = false;

            Framebuffer(uint32_t width , uint32_t height);
            ~Framebuffer();

            // OpenGl functionality
            void Draw();

            // Bind/Unbind functionality
            // Very important to call in correct order and
            //      remember to unbind when done
            void BindFrame();
            void BindMesh();
            void BindTexture();
            void UnbindFrame();
            void UnbindMesh();
            void UnbindTexture();
    };

}
}

#endif