#ifndef YE_SHADER_HPP
#define YE_SHADER_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

std::string GetFile(const std::string& path , const std::string& file);

namespace YE {
namespace rendering {

    class Shader {
        Shader(const Shader&) = delete;
        Shader(Shader&&) = delete;
        Shader& operator=(const Shader&) = delete;
        
        int GetUniformLocation(const std::string& name);
        public:
            uint32_t m_Program = -1;
            bool m_Valid = false;
            std::string m_VertPath , m_FragPath;
            std::string m_VertSrc , m_FragSrc;
            std::unordered_map<std::string , int> m_Uniform_locations;

            Shader(const std::string& vert_path , const std::string& frag_path);
            ~Shader();

            void SetUniformInt(const std::string& name , int val);
            void SetUniformFloat(const std::string& name , float val);
            void SetUniformFloat2(const std::string& name , float val1 , float val2);
            void SetUniformVec2(const std::string& name , const glm::vec2& val);
            void SetUniformFloat3(const std::string& name , float val1 , float val2 , float val3);
            void SetUniformVec3(const std::string& name , const glm::vec3& val);
            void SetUniformFloat4(const std::string& name , float val1 , float val2 , float val3 , float val4);
            void SetUniformVec4(const std::string& name , const glm::vec4& val);
            void SetUniformMat3(const std::string& name , const glm::mat3& mat);
            void SetUniformMat4(const std::string& name , const glm::mat4& mat);

            inline void Bind() const { glUseProgram(m_Program); }
            inline void Unbind() const { glUseProgram(0); }

    };

}
}

#endif