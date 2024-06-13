#include "framebuffer.h"

namespace PBRV {
    Framebuffer::Framebuffer(GLuint color_attachment, bool has_depth_stencil, int width, int height): has_rbo(has_depth_stencil) {
        glGenFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        // bind color attachment
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment, 0);

        // bind renderbuffer
        if (has_depth_stencil) {
            glGenRenderbuffers(1, &m_rbo_id);
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_id);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        has_destroyed = false;
    }

    Framebuffer::~Framebuffer() {
        if (!has_destroyed) {
            glDeleteFramebuffers(1, &m_id);
            if (has_rbo) glDeleteRenderbuffers(1, &m_rbo_id);
            has_destroyed = true;
        }
    }

    GLuint Framebuffer::get_id() {
        return m_id;
    }

    void Framebuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }
}