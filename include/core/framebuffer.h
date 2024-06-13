/**
 * PBR-Viewer
 * >> FrameBuffer Object
 */

#pragma once
#include "contain_gl.h"

namespace PBRV {

    class Framebuffer {
    public:
        Framebuffer() = delete;
        Framebuffer(const Framebuffer&) = delete;
        Framebuffer operator=(const Framebuffer&) = delete;

        // argu <width, height> only need to be set when has_depth_stencil = true
        Framebuffer(GLuint color_attachment, bool has_depth_stencil = false, int width = 0, int height = 0);
        ~Framebuffer();

        // bind GL_FRAMEBUFFER0
        static void bind_default() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        // get framebuffer id
        [[nodiscard]]
        GLuint get_id();

        // bind framebuffer
        void bind();

    private:
        bool has_destroyed = true;
        bool has_rbo = false;
        GLuint m_id;
        GLuint m_rbo_id;
    };
}