#include "vertexbuffer.h"

#include <stdexcept>

namespace PBRV {
    VertexBuffer::VertexBuffer(VertexBufferInfo& create_info) {
        if (create_info.attributes.empty()) {
            throw std::runtime_error("attribute_size is zero. Failed to create vertexbuffer!");
        }

        if (!create_info.buffer_ptr || create_info.buffer_size == 0) {
            throw std::runtime_error("vertexbuffer_info gets an invalid buffer. Failed to create vertexbuffer!");
        }

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, create_info.buffer_size, create_info.buffer_ptr, GL_STATIC_DRAW);

        for (auto &attr : create_info.attributes) {
            glVertexAttribPointer(attr.location, attr.element_count, attr.type, attr.is_normalize, attr.stride, reinterpret_cast<void*>(attr.offset));
            glEnableVertexAttribArray(attr.location);
        }

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        has_destroyed = false;
    }

    VertexBuffer::~VertexBuffer() {
        if (!has_destroyed) {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            has_destroyed = true;
        }
    }

    GLuint VertexBuffer::get_vao_id() const {
        return m_VAO;
    }

    GLuint VertexBuffer::get_vbo_id() const {
        return m_VBO;
    }

    void VertexBuffer::bind() {
        glBindVertexArray(m_VAO);
    }
}