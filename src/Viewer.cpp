#include "Viewer.h"

bool Viewer::create(int width, int height, int outTexId)
{
    m_width = width;
    m_height = height;
    m_outTexId = outTexId;

    // create renderer
    if (!renderer_)
    {
        renderer_ = createRenderer();
        if (!renderer_)
        {
            LOGE("Viewer::create failed: createRenderer error");
            return false;
        }
    }
    

    return true;
}

void Viewer::destroy()
{
}

void Viewer::drawFrame(Scene* scene)
{
    if (!renderer_)
    {
        return;
    }

    scene_ = scene;

    // setup framebuffer
    setupMainBuffers();
    setupShadowMapBuffers();

    // setup model materials
    //setupScene();

    // draw shadow map
    //drawShadowMap();

    // main pass
    ClearStates clearStates{};
    clearStates.colorFlag = true;
    clearStates.depthFlag = config_.depthTest;
    clearStates.clearColor = config_.clearColor;
    clearStates.clearDepth = config_.reverseZ ? 0.f : 1.f;

    renderer_->beginRenderPass(m_fboMain, clearStates);
    renderer_->setViewPort(0, 0, m_width, m_height);

    // draw scene
    drawScene(false);

    // end main pass
    renderer_->endRenderPass();
}

void Viewer::drawScene(bool shadowPass)
{

}

void Viewer::setupMainBuffers()
{
    setupMainColorBuffer(false);
    setupMainDepthBuffer(false);

    if (!m_fboMain) {
        m_fboMain = renderer_->createFrameBuffer(false);
    }
    m_fboMain->setColorAttachment(m_texColorMain, 0);
    m_fboMain->setDepthAttachment(m_texDepthMain);
    m_fboMain->setOffscreen(false);

    if (!m_fboMain->isValid()) {
        LOGE("setupMainBuffers failed");
    }
}

void Viewer::setupShadowMapBuffers()
{
}

void Viewer::setupMainColorBuffer(bool multiSample)
{
    if (!m_texColorMain || m_texColorMain->multiSample != multiSample)
    {
        TextureDesc texDesc{};
        texDesc.width = m_width;
        texDesc.height = m_height;
        texDesc.type = TextureType_2D;
        texDesc.format = TextureFormat_RGBA8;
        texDesc.usage = TextureUsage_AttachmentColor | TextureUsage_RendererOutput;
        texDesc.useMipmaps = false;
        texDesc.multiSample = multiSample;
        m_texColorMain = renderer_->createTexture(texDesc);

        SamplerDesc sampler{};
        sampler.filterMin = Filter_LINEAR;
        sampler.filterMag = Filter_LINEAR;
        m_texColorMain->setSamplerDesc(sampler);

        m_texColorMain->initImageData();
    }
}

void Viewer::setupMainDepthBuffer(bool multiSample)
{
    if (!m_texDepthMain || m_texDepthMain->multiSample != multiSample)
    {
        TextureDesc texDesc{};
        texDesc.width = m_width;
        texDesc.height = m_height;
        texDesc.type = TextureType_2D;
        texDesc.format = TextureFormat_FLOAT32;
        texDesc.usage = TextureUsage_AttachmentDepth;
        texDesc.useMipmaps = false;
        texDesc.multiSample = multiSample;
        m_texDepthMain = renderer_->createTexture(texDesc);

        SamplerDesc sampler{};
        sampler.filterMin = Filter_NEAREST;
        sampler.filterMag = Filter_NEAREST;
        m_texDepthMain->setSamplerDesc(sampler);

        m_texDepthMain->initImageData();
    }
}
