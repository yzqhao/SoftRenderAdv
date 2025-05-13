#pragma once

#include "render/Renderer.h"

class Viewer
{
public:
    virtual bool create(int width, int height, int outTexId);
    virtual void destroy();

private:
    int m_width = 0;
    int m_height = 0;
    int m_outTexId = 0;
};

