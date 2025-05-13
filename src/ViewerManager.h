
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

        m_viewers.resize(Renderer_Count);

        // viewer opengl
        auto viewer_opengl = std::make_shared<ViewerOpenGL>();
        m_viewers[Renderer_OPENGL] = std::move(viewer_opengl);

        // viewer vulkan
        auto viewer_vulkan = std::make_shared<ViewerVulkan>();
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
        return 0;
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
    RendererType m_rendertype = (RendererType)Renderer_OPENGL;
    std::vector<std::shared_ptr<Viewer>> m_viewers;
};