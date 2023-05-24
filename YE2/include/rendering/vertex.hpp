#ifndef YE_VERTEX_HPP
#define YE_VERTEX_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

void CheckGLError(const std::string& file , int line);

#ifdef YE_DEBUG
#define GL_CHECK CheckGLError(__FILE__ , __LINE__)
#else
#define GL_CHECK (void)0
#endif

namespace YE {
namespace rendering {
    struct Vertex {
        glm::vec3 position{ 0.f , 0.f , 0.f };
        glm::vec3 color{ 0.f , 0.f , 0.f };
        glm::vec3 normal{ 0.f , 0.f , 0.f };
        glm::vec3 tangent{ 0.f , 0.f , 0.f };
        glm::vec3 bitangent{ 0.f , 0.f , 0.f };
        glm::vec2 tex_coord{ 0.f , 0.f };
        float opacity = 0.f;

        static const size_t size() { return sizeof(Vertex); }
        static const std::vector<uint32_t> layout() { return { 3 , 3 , 3 , 3 , 3 , 2 , 1 }; }

        Vertex() {}
        Vertex(glm::vec3 pos) 
            : position(pos) {}
        Vertex(glm::vec3 pos , glm::vec3 col) 
            : position(pos) , color(col) {}
        Vertex(glm::vec3 pos , glm::vec3 col , glm::vec3 normal) 
            : position(pos) , color(col) , normal(normal) {}
        Vertex(glm::vec3 pos , glm::vec3 col , glm::vec3 normal , glm::vec2 tex) 
            : position(pos) , color(col) , normal(normal) , tex_coord(tex) {}
        Vertex(glm::vec3 pos , glm::vec3 col , glm::vec3 normal , glm::vec2 tex , float op) 
            : position(pos) , color(col) , normal(normal) , tex_coord(tex) , opacity(op) {}
        Vertex(glm::vec3 pos , glm::vec3 col , glm::vec3 normal , glm::vec3 tangent , glm::vec2 tex  , float op) 
            : position(pos) , color(col) , normal(normal) , tangent(tangent) , tex_coord(tex) , opacity(op) {}
        Vertex(glm::vec3 pos , glm::vec3 col , glm::vec3 normal  , glm::vec3 tangent , glm::vec3 bitangent , glm::vec2 tex , float op) 
            : position(pos) , color(col) , normal(normal) , tangent(tangent) , bitangent(bitangent) , tex_coord(tex) , opacity(op) {}
    };

    /** Vertex Array Class
     *   -> Wraps OpenGL's Vertex Array Object
     *   -> Supports both indexed and non-indexed rendering
    */
    class VertexArray {
        VertexArray(const VertexArray&) = delete;
        VertexArray(VertexArray&&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        public:
            std::vector<Vertex> m_Verts;
            std::vector<uint32_t> m_Elements;
            uint32_t VAO = -1 , VBO = -1 , EBO = -1;
            bool m_Valid = false;
            
            VertexArray(const std::vector<Vertex>& verts);
            VertexArray(const std::vector<Vertex>& verts , const std::vector<uint32_t>& elements);
            ~VertexArray();

            inline void Bind() const { glBindVertexArray(VAO); }
            void Draw(int draw_type = GL_TRIANGLES) const;
            inline void Unbind() const { glBindVertexArray(0); }
            bool Upload();
    };

}
}

#endif