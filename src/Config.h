
#pragma once

#include <string>
#include "base/MathInc.h"
#include "render/Renderer.h"


const std::string ASSETS_DIR = "../assets/";
const std::string SHADER_GLSL_DIR = "../shaders/GLSL/";

enum AAType
{
    AAType_NONE,
    AAType_MSAA,
    AAType_FXAA,
};

class Config
{
public:
    std::string modelName;
    std::string modelPath;
    std::string skyboxName;
    std::string skyboxPath;

    size_t triangleCount_ = 0;

    bool wireframe = false;
    bool worldAxis = true;
    bool showSkybox = false;
    bool showFloor = true;

    bool shadowMap = true;
    bool pbrIbl = false;
    bool mipmaps = false;

    bool cullFace = true;
    bool depthTest = true;
    bool reverseZ = false;

    math::float4 clearColor = { 0.f, 0.f, 0.f, 0.f };
    math::float3 ambientColor = { 0.5f, 0.5f, 0.5f };

    bool showLight = true;
    math::float3 pointLightPosition = { 0.f, 0.f, 0.f };
    math::float3 pointLightColor = { 0.5f, 0.5f, 0.5f };

    int aaType = AAType_NONE;
    int rendererType = Renderer_OPENGL;
};


