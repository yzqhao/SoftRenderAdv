
#pragma once

#include <string>
#include "Buffer.h"
#include "MathInc.h"

class ImageUtils {
public:
    static std::shared_ptr<Buffer<RGBA>> readImageRGBA(const std::string& path);
    static void writeImage(char const* filename, int w, int h, int comp, const void* data, int strideInBytes,
        bool flipY);

    static void convertFloatImage(RGBA* dst, float* src, uint32_t width, uint32_t height);
};

