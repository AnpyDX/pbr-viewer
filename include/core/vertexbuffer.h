/**
 * PBR-Viewer
 * >> VertexBuffer Object
 */

#pragma once

#include "contain_gl.h"

#include <vector>

namespace PBRV {
    struct VertexAttribute {
        GLuint    location;
        GLint     element_count;
        GLenum    type;
        GLboolean is_normalize;
        GLsizei   stride;
        GLuint    offset;
    };

    struct VertexBufferInfo {
        /* Configure Functions */

        VertexBufferInfo& add_attribute(
            GLuint    location,
            GLint     element_count,
            GLenum    type,
            GLboolean is_normalize,
            GLsizei   stride,
            GLuint    offset
        ) {
            VertexAttribute attr {
                location,
                element_count,
                type,
                is_normalize,
                stride,
                offset
            };
            attributes.push_back(attr);

            return *this;
        }

        VertexBufferInfo& set_buffer(
            void* pointer,
            uint32_t size
        ) {
            buffer_ptr = pointer;
            buffer_size = size;

            return *this;
        }

        /* VertexBuffer Info Data */
        std::vector<VertexAttribute> attributes = {};

        uint32_t buffer_size = 0;
        void* buffer_ptr = nullptr;
    };

    class VertexBuffer {
    public:
        VertexBuffer() = delete;
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBufferInfo& create_info);
        ~VertexBuffer();

        // get VAO id
        [[nodiscard]]
        GLuint get_vao_id() const;

        // get VBO id
        [[nodiscard]]
        GLuint get_vbo_id() const;

        // bind vertexbuffer object
        void bind();
        
    private:
        bool has_destroyed = true;
        GLuint m_VAO;
        GLuint m_VBO;
    };
}