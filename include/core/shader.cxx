#include "shader.h"
#include "contain_gl.h"

#include <stdexcept>
#include <string>
#include <bmx/bmx.h>


namespace {
    void checkShaderStatus(unsigned int id, bool is_program = false) {
        GLint success = false;
        char info_log[1024];

        if (is_program) {
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(id, 1024, nullptr, info_log);
                throw std::runtime_error("failed to link shader program!\n" + std::string(info_log));
            }
        }
        else {
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(id, 1024, nullptr, info_log);
                throw std::runtime_error("failed to compile shader program!\n" + std::string(info_log));
            }
        }
    }
}

namespace PBRV {
    Shader::Shader(std::fstream& bmx_shader) {
        BMX::Data shader_raw {};
        shader_raw = BMX::loads(bmx_shader);
        if (shader_raw.texts.find("vertex") == shader_raw.texts.end()) {
            throw std::runtime_error("failed to find vertex block in shaders!");
        }
        if (shader_raw.texts.find("fragment") == shader_raw.texts.end()) {
            throw std::runtime_error("failed to find fragment block in shaders!");
        }

        const char* vertex_code = shader_raw.texts["vertex"].c_str();
        const char* fragment_code = shader_raw.texts["fragment"].c_str();

        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code, nullptr);
        glCompileShader(vertex);
        checkShaderStatus(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code, nullptr);
        glCompileShader(fragment);
        checkShaderStatus(fragment);

        m_id = glCreateProgram();
        glAttachShader(m_id, vertex);
        glAttachShader(m_id, fragment);
        glLinkProgram(m_id);
        try { checkShaderStatus(m_id, true); } 
        catch (const std::exception& e) {
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            throw std::runtime_error(e.what());
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        has_destroyed = false;
    }

    Shader::~Shader() {
        if (!has_destroyed) {
            glDeleteProgram(m_id);
            has_destroyed = true;
        }
    }

    unsigned int Shader::get_id() const {
        return m_id;
    }

    void Shader::use() {
        glUseProgram(m_id);
    }

    void Shader::set_bool(const std::string& name, bool value) const {
        this->set_int(name, static_cast<int>(value));
    }

    void Shader::set_int(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::set_float(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::set_vec2(const std::string& name, mas::vec2& value) const {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, mas::get_value_ptr(value));
    }

    void Shader::set_vec3(const std::string& name, mas::vec3& value) const {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, mas::get_value_ptr(value));
    }

    void Shader::set_vec4(const std::string& name, mas::vec4& value) const {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, mas::get_value_ptr(value));
    }

    void Shader::set_mat4(const std::string& name, mas::mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, mas::get_value_ptr(value));
    }
}