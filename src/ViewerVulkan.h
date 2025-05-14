#pragma once

#include "Viewer.h"

class ViewerVulkan : public Viewer
{
public:
    ViewerVulkan(Config& config) : Viewer(config)
    {
    }

    virtual int swapBuffer() override
    {
        return 0;
    }

    std::shared_ptr<Renderer> createRenderer() override
    {
        return nullptr;
    }
};