#pragma once

#include "render/Renderer.h"
#include "Config.h"

class Scene;

class Viewer
{
public:
    Viewer(Config& config) : config_(config) {}

    virtual bool create(int width, int height, int outTexId);
    virtual void destroy();

    virtual void drawFrame(Scene* scene);
    virtual int swapBuffer() = 0;

protected:
    virtual std::shared_ptr<Renderer> createRenderer() = 0;

private:
    void drawScene(bool shadowPass);

    void setupMainBuffers();
    void setupShadowMapBuffers();
    void setupMainColorBuffer(bool multiSample);
    void setupMainDepthBuffer(bool multiSample);

protected:
    Config& config_;

    int m_width = 0;
    int m_height = 0;
    int m_outTexId = 0;

    Scene* scene_ = nullptr;

    std::shared_ptr<Renderer> renderer_ = nullptr;

    // main fbo
    std::shared_ptr<FrameBuffer> m_fboMain = nullptr;
    std::shared_ptr<Texture> m_texColorMain = nullptr;
    std::shared_ptr<Texture> m_texDepthMain = nullptr;
};

