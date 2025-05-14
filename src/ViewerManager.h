
#pragma once

#include <memory>
#include <vector>

#include "ViewerOpenGL.h"
#include "ViewerVulkan.h"

class ViewerManager
{
public:
    bool create(int width, int height, int outTexId)
    {
        m_width = width;
        m_height = height;
        m_outTexId = outTexId;

        // config
        config_ = std::make_shared<Config>();

        m_viewers.resize(Renderer_Count);

        // viewer opengl
        auto viewer_opengl = std::make_shared<ViewerOpenGL>(*config_);
        m_viewers[Renderer_OPENGL] = std::move(viewer_opengl);

        // viewer vulkan
        auto viewer_vulkan = std::make_shared<ViewerVulkan>(*config_);
        m_viewers[Renderer_Vulkan] = std::move(viewer_vulkan);

        return true;
    }

    void destroy()
    {
        for (auto& it : m_viewers)
        {
            it->destroy();
        }
    }

    int drawFrame()
    {
        auto &viewer = m_viewers[config_->rendererType];
        if (m_rendertype != config_->rendererType) {
            m_rendertype = (RendererType)config_->rendererType;
            viewer->create(m_width, m_height, m_outTexId);
        }

        viewer->drawFrame(nullptr);
        return viewer->swapBuffer();
    }

    inline void drawPanel()
    {
        if (m_showUI)
        {
        }
    }
private:
    int m_width = 0;
    int m_height = 0;
    int m_outTexId = 0;
    bool m_showUI = true;
    RendererType m_rendertype = (RendererType)-1;
    std::vector<std::shared_ptr<Viewer>> m_viewers;

    std::shared_ptr<Config> config_;
};