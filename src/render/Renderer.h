
#pragma once

#include "Framebuffer.h"
#include "Texture.h"
#include "PipelineStates.h"
#include "Uniform.h"
#include "Vertex.h"

enum RendererType
{
    Renderer_SOFT,
    Renderer_OPENGL,
    Renderer_Vulkan,

    Renderer_Count,
};

class Renderer
{
public:
    virtual RendererType type() = 0;
    virtual bool create() { return true; };
    virtual void destroy() {};

    // framebuffer
    virtual std::shared_ptr<FrameBuffer> createFrameBuffer(bool offscreen) = 0;

    // texture
    virtual std::shared_ptr<Texture> createTexture(const TextureDesc& desc) = 0;

    // vertex
    virtual std::shared_ptr<VertexArrayObject> createVertexArrayObject(const VertexArray& vertexArray) = 0;

    // shader program
    virtual std::shared_ptr<ShaderProgram> createShaderProgram() = 0;

    // pipeline states
    virtual std::shared_ptr<PipelineStates> createPipelineStates(const RenderStates& renderStates) = 0;

    // uniform
    virtual std::shared_ptr<UniformBlock> createUniformBlock(const std::string& name, int size) = 0;
    virtual std::shared_ptr<UniformSampler> createUniformSampler(const std::string& name, const TextureDesc& desc) = 0;

    // pipeline
    virtual void beginRenderPass(std::shared_ptr<FrameBuffer>& frameBuffer, const ClearStates& states) = 0;
    virtual void setViewPort(int x, int y, int width, int height) = 0;
    virtual void setVertexArrayObject(std::shared_ptr<VertexArrayObject>& vao) = 0;
    virtual void setShaderProgram(std::shared_ptr<ShaderProgram>& program) = 0;
    virtual void setShaderResources(std::shared_ptr<ShaderResources>& uniforms) = 0;
    virtual void setPipelineStates(std::shared_ptr<PipelineStates>& states) = 0;
    virtual void draw() = 0;
    virtual void endRenderPass() = 0;
    virtual void waitIdle() = 0;
};