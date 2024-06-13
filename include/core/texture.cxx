#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"

#include <stdexcept>

#include <stb_image.h>

namespace PBRV {
    Texture::Texture(TextureInfo& create_info, int width, int height) {

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, create_info.wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, create_info.wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, create_info.min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, create_info.mag_filter);
        glTexImage2D(GL_TEXTURE_2D, create_info.mipmap_level, create_info.dst_format, width, height, 0, create_info.src_format, GL_UNSIGNED_BYTE, nullptr);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        has_destroyed = false;
    }

    Texture::Texture(const std::string& tex_path, TextureInfo& create_info) {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *tex_data = stbi_load(tex_path.c_str(), &width, &height, &channels, 0);
        if (!tex_data) {
            throw std::runtime_error("failed to open texture: " + tex_path + " !");
        }

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, create_info.wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, create_info.wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, create_info.min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, create_info.mag_filter);
        glTexImage2D(GL_TEXTURE_2D, create_info.mipmap_level, create_info.dst_format, width, height, 0, create_info.src_format, GL_UNSIGNED_BYTE, tex_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        has_destroyed = false;
    }

    Texture::~Texture() {
        if (!has_destroyed) {
            glDeleteTextures(1, &m_id);
            has_destroyed = true;
        }
    }

    GLuint Texture::get_id() const {
        return m_id;
    }

    void Texture::bind_sampler(GLenum sampler_id) {
        glActiveTexture(sampler_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
}