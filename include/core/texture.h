/**
 * PBR-Viewer
 * >> Texture Object
 */

#pragma once

#include "contain_gl.h"

#include <string>

namespace PBRV {
    struct TextureInfo {
        GLenum src_format = GL_RGB;
        GLenum dst_format = GL_RGB;
        GLenum wrap_s = GL_REPEAT;
        GLenum wrap_t = GL_REPEAT;
        GLenum min_filter = GL_LINEAR;
        GLenum mag_filter = GL_LINEAR;
        GLint mipmap_level = 0;
    };

    class Texture {
    public:
        Texture() = delete;
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        /* create texture without data */
        Texture(TextureInfo& create_info, int width, int height);

        /* create texture with texture data */
        Texture(const std::string& tex_path, TextureInfo& create_info);
        
        ~Texture();

        // get texture id
        [[nodiscard]]
        GLuint get_id() const;

        // bind texture to sampler
        void bind_sampler(GLenum sampler_id) const;

    private:
        bool has_destroyed = true;
        GLuint m_id;
    };
}