/**
 * PBR-Viewer
 * >> Shader Object
 */

#pragma once
#define MAS_UTYPE_FLOAT

#include "contain_gl.h"

#include <fstream>
#include <string>
#include <mas/mas.hpp>

namespace PBRV {
    
    class Shader {
    public:
        Shader() = delete;
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        
        explicit Shader(std::fstream& bmx_shader);
        ~Shader();

        // get GLShader object id
        [[nodiscard]]
        GLuint get_id() const;

        // active shader object
        void use() const;

        /* set shader uniform variable */
        void set_bool(const std::string& name, bool value) const;
        void set_int(const std::string& name, int value) const;
        void set_float(const std::string& name, float value) const;
        void set_vec2(const std::string& name, mas::vec2 value) const;
        void set_vec3(const std::string& name, mas::vec3 value) const;
        void set_vec4(const std::string& name, mas::vec4 value) const;
        void set_mat4(const std::string& name, mas::mat4 value) const;

    private:
        bool has_destroyed = true;
        GLuint m_id;
    };
}