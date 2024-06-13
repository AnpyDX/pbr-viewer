/**
 * PBR-Viewer
 * >> IndexBuffer Object
 */

#pragma once

#include "contain_gl.h"

#include <cstdint>

namespace PBRV {
    class IndexBuffer {
    public:
        IndexBuffer() = delete;
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(void* data_ptr, uint32_t size);
        ~IndexBuffer();

        // get indexbuffer id
        [[nodiscard]]
        GLuint get_id() const;

        // bind indexbuffer
        void bind();

    private:
        bool has_destroyed = true;
        GLuint m_id;
    };
}