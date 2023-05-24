#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"

#include <string>
#include <iostream>

namespace YE {
namespace rendering {

    class Texture {
        // Texture(const Texture&) = delete;
        // Texture(Texture&&) = delete;
        // Texture& operator=(const Texture&) = delete;
        public:
            enum class FilterType {
                nearest = GL_NEAREST ,
                linear = GL_LINEAR
            };

            enum class TextureType {
                diffuse = GL_TEXTURE0 ,
                specular = GL_TEXTURE1 ,
                normal = GL_TEXTURE2 ,
                height = GL_TEXTURE3
            };

            FilterType m_Type = FilterType::linear;
            TextureType m_Texture_type = TextureType::diffuse;
            uint32_t m_Program = -1;
            uint32_t m_Width = -1 , m_Height = -1 , m_Num_channels = -1;
            bool m_Valid = false;
            unsigned char* m_Pixels = nullptr;

            std::string m_VertPath = "" , m_FragPath = "" , m_TexturePath = "";
            std::string m_VertSrc = "" , m_FragSrc = "";
          
            Texture(const std::string& texture_path);
            ~Texture();

            std::string TextureTypeToString(TextureType type);

            inline void Bind(int pos = GL_TEXTURE0) const { glActiveTexture(pos); glBindTexture(GL_TEXTURE_2D , m_Program); }
            inline void Unbind(int pos = GL_TEXTURE0) const { glActiveTexture(pos); glBindTexture(GL_TEXTURE_2D , 0); }
    };

}
}

#endif