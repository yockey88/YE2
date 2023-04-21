#include "rendering/shader.hpp"

#include "glm/gtc/type_ptr.hpp"

std::string GetFile(const std::string& path , const std::string& file) {
    std::string result;
    std::ifstream in(path + file);
    if (in.is_open()) {
        std::stringstream sstr;
        sstr << in.rdbuf();
        result = sstr.str();
    }
    return result;
}

namespace YE {
namespace rendering {

    int Shader::GetUniformLocation(const std::string& name) {

        auto itr = m_Uniform_locations.find(name);
        if (itr == m_Uniform_locations.end()) {
            m_Uniform_locations[name] = glGetUniformLocation(m_Program , name.c_str());
        }
        return m_Uniform_locations[name];
    }
    
    Shader::Shader(const std::string& vert_name , const std::string& frag_name) : 
        m_VertPath("res/" + vert_name) , m_FragPath("res/" + frag_name) {
        
        m_VertSrc = GetFile("res/" , vert_name);
        m_FragSrc = GetFile("res/" , frag_name);

        m_Program = glCreateProgram();

        char vert_log[2056];
        char frag_log[2056];
        char error_log[2056];
        int success = 0;

        uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER); 
        const GLchar* vert_shader_src = m_VertSrc.c_str();
        glShaderSource(vert_shader , 1 , &vert_shader_src , nullptr); 
        glCompileShader(vert_shader);
        glGetShaderiv(vert_shader , GL_COMPILE_STATUS , &success);
        if (success != GL_TRUE) {
            glGetShaderInfoLog(vert_shader , sizeof(error_log) , nullptr , error_log);
            printf("Error compiling vertex shader: %s\n" , error_log);
            m_Valid = false;
        } else {
            glAttachShader(m_Program , vert_shader);
        }
        
        uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* frag_shader_src = m_FragSrc.c_str();
        glShaderSource(frag_shader , 1 , &frag_shader_src , nullptr);
        glCompileShader(frag_shader);
        glGetShaderiv(frag_shader , GL_COMPILE_STATUS , &success);
        if (success != GL_TRUE) {
            glGetShaderInfoLog(frag_shader , sizeof(frag_log) , nullptr , error_log);
            printf("Error compiling fragment shader: %s" , error_log);
            m_Valid = false;
        } else {
            glAttachShader(m_Program , frag_shader);
        }

        if (success == GL_TRUE) {
            glLinkProgram(m_Program);
            glValidateProgram(m_Program);
            glGetProgramiv(m_Program , GL_LINK_STATUS , &success);
            if (success != GL_TRUE) {
                glGetProgramInfoLog(m_Program , 2056 , nullptr , error_log);
                printf("Error linking shader program: ");
                std::cout << error_log << std::endl;
                m_Valid = false;
            }
        } else {
            printf("Error compiling shader program: %s\n" , error_log);
            m_Valid = false;
        }

        glDeleteShader(frag_shader);
        glDeleteShader(vert_shader);

        m_Valid = true;
    }

    Shader::~Shader() {
        glUseProgram(0);
        glDeleteProgram(m_Program);
    }

    void Shader::SetUniformInt(const std::string& name , int val) {
        glUniform1i(GetUniformLocation(name) , val);
    }

    void Shader::SetUniformFloat(const std::string& name , float val) {
        glUniform1f(GetUniformLocation(name) , val);
    }

    void Shader::SetUniformFloat2(const std::string& name , float val1 , float val2) {
        glUniform2f(GetUniformLocation(name) , val1 , val2);
    }

    void Shader::SetUniformVec2(const std::string& name , const glm::vec2& val) {
        glUniform2f(GetUniformLocation(name) , val.x , val.y);
    }

    void Shader::SetUniformFloat3(const std::string& name , float val1 , float val2 , float val3) {
        glUniform3f(GetUniformLocation(name) , val1 , val2 , val3);
    }

    void Shader::SetUniformVec3(const std::string& name , const glm::vec3& val) {
        glUniform3f(GetUniformLocation(name) , val.x , val.y , val.z);
    }

    void Shader::SetUniformFloat4(const std::string& name , float val1 , float val2 , float val3 , float val4) {
        glUniform4f(GetUniformLocation(name) , val1 , val2 , val3 , val4);
    }

    void Shader::SetUniformVec4(const std::string& name , const glm::vec4& val) {
        glUniform4f(GetUniformLocation(name) , val.x , val.y , val.z , val.w);
    }

    void Shader::SetUniformMat3(const std::string& name , const glm::mat3& mat) {
        glUniformMatrix3fv(GetUniformLocation(name) , 1 , GL_FALSE , glm::value_ptr(mat));
    }
    
    void Shader::SetUniformMat4(const std::string& name , const glm::mat4& mat) {
        glUniformMatrix4fv(GetUniformLocation(name) , 1 , GL_FALSE , glm::value_ptr(mat));
    }

}
}