#include "log.hpp"

#include "rendering/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace YE {
namespace rendering {

    Texture::Texture(const std::string& texture_path) {
        stbi_set_flip_vertically_on_load(1);
        std::string real_path = "res/" + texture_path; 
        int w , h , n;
        m_Pixels = stbi_load(real_path.c_str() , &w , &h , &n , 0);

        m_Width = w;
        m_Height = h;
        m_Num_channels = n;

        if (m_Pixels == nullptr) {
            YE_ERROR("Failed to load texture : {}" , real_path);
            m_Valid = false;
            return;
        }

        glGenTextures(1 , &m_Program);
        glBindTexture(GL_TEXTURE_2D , m_Program);

        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT);

        GLenum format = 0;
        switch (m_Num_channels) {
            case 1: format = GL_RED; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
            default:
                YE_ERROR("Invalid number of channels : {}" , m_Num_channels);
                m_Valid = false;
            break;
        }

        if (m_Pixels == nullptr && format == 0) {
            YE_ERROR("Failed to load texture : {}" , real_path);
            m_Valid = false;
            return;
        } else if (m_Pixels != nullptr && format == 0) {
            YE_ERROR("Image format not supported!" , real_path);
            m_Valid = false;
            return;
        } if (m_Pixels != nullptr && format != 0) {
            glTexImage2D(GL_TEXTURE_2D , 0 , format , m_Width , m_Height , 0 , format , GL_UNSIGNED_BYTE , m_Pixels);
            switch (m_Type) {
                case FilterType::nearest:
                    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST);
                break;
                case FilterType::linear:
                    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
                break;
                default:
                    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST);
                break;
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            float pixels[] = 
            {   0.f , 0.f , 1.f ,    0.f , 1.f , 1.f ,   0.f , 0.f , 1.f ,   0.f , 1.f , 1.f ,
                0.f , 1.f , 1.f ,    0.f , 0.f , 1.f ,   0.f , 1.f , 1.f ,   0.f , 0.f , 1.f ,
                0.f , 0.f , 1.f ,    0.f , 1.f , 1.f ,   0.f , 0.f , 1.f ,   0.f , 1.f , 1.f , 
                0.f , 1.f , 1.f ,    0.f , 0.f , 1.f ,   0.f , 1.f , 1.f ,   0.f , 0.f , 1.f };
            m_Width = 4;
            m_Height = 4;
            m_Num_channels = 3;

            glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGB , m_Width , m_Height , 0 , GL_RGB , GL_FLOAT , pixels);
            glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST);
        }

    }

    Texture::~Texture() {
        stbi_image_free(m_Pixels);
        m_Pixels = nullptr;
    }

    std::string Texture::TextureTypeToString(TextureType type) {
        switch (type) {
            case TextureType::diffuse: return "diffuse";
            case TextureType::specular: return "specular";
            case TextureType::normal: return "normal";
            case TextureType::height: return "height";
            default: return "diffuse";
        }
    }

}
}