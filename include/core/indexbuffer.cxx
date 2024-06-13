#include "indexbuffer.h"

#include <stdexcept>

namespace PBRV {
    IndexBuffer::IndexBuffer(void* data_ptr, uint32_t size) {
        if (!data_ptr || size == 0) {
            throw std::runtime_error("indexbuffer get invalid buffer data! Failed to create indexbuffer.");
        }

        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data_ptr, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        has_destroyed = false;
    }

    IndexBuffer::~IndexBuffer() {
        if (!has_destroyed) {
            glDeleteBuffers(1, &m_id);
            has_destroyed = true;
        }
    }

    GLuint IndexBuffer::get_id() const {
        return m_id;
    }

    void IndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }
}