/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief core.texture object
 */

#pragma once

#include "contain_gl.h"

#include <string>

namespace PBRV {
    struct TextureInfo {
        GLint src_format = GL_RGB;
        GLint dst_format = GL_RGB;
        GLint wrap_s = GL_REPEAT;
        GLint wrap_t = GL_REPEAT;
        GLint min_filter = GL_LINEAR;
        GLint mag_filter = GL_LINEAR;
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