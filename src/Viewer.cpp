#include "Viewer.h"

bool Viewer::create(int width, int height, int outTexId)
{
    m_width = width;
    m_height = height;
    m_outTexId = outTexId;

    return true;
}

void Viewer::destroy()
{
}