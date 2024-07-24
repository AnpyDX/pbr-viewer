/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief core.indexbuffer object
 */

#pragma once

#include "contain_gl.h"

#include <cstdint>

namespace PBRV::Core {
    class IndexBuffer {
    public:
        IndexBuffer() = delete;
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(void* data_ptr, uint32_t size, uint32_t count);
        ~IndexBuffer();

        // get indexbuffer id
        [[nodiscard]]
        GLuint get_id() const;

        // get index count (used for glDrawElement)
        [[nodiscard]]
        uint32_t get_count() const;

        // bind indexbuffer
        void bind() const;

    private:
        bool has_destroyed = true;
        GLuint m_id = 0;
        uint32_t m_count = 0;
    };
}