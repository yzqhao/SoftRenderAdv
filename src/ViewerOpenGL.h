#pragma once

#include "Viewer.h"

#include "render/opengl/OpenGLUtils.h"
#include "render/opengl/RendererOpenGL.h"

class ViewerOpenGL : public Viewer
{
public:
    ViewerOpenGL(Config& config) : Viewer(config)
    {
        GL_CHECK(glGenFramebuffers(1, &fbo_in_));
        GL_CHECK(glGenFramebuffers(1, &fbo_out_));
    }

    virtual int swapBuffer() override
    {
        int width = m_texColorMain->width;
        int height = m_texColorMain->height;

        if (m_texColorMain->multiSample) {
            GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo_in_));
            GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D_MULTISAMPLE,
                m_texColorMain->getId(),
                0));

            GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_outTexId));
            GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo_out_));
            GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_outTexId, 0));

            GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_in_));
            GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_out_));

            GL_CHECK(glBlitFramebuffer(0, 0, width, height,
                0, 0, width, height,
                GL_COLOR_BUFFER_BIT,
                GL_NEAREST));
            return m_outTexId;
        }

        return m_texColorMain->getId();
    }

    std::shared_ptr<Renderer> createRenderer() override
    {
        auto renderer = std::make_shared<RendererOpenGL>();
        if (!renderer->create())
        {
            return nullptr;
        }
        return renderer;
    }

private:
    GLuint fbo_in_ = 0;
    GLuint fbo_out_ = 0;
};