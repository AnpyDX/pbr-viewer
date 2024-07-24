#include "indexbuffer.h"

#include <stdexcept>

namespace PBRV::Core {
    IndexBuffer::IndexBuffer(void* data_ptr, uint32_t size, uint32_t count): m_count(count) {
        if (!data_ptr || size == 0 || count == 0) {
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

    uint32_t IndexBuffer::get_count() const {
        return m_count;
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }
}