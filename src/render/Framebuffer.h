

#pragma once

#include <memory>
#include "Texture.h"

struct FrameBufferAttachment {
  std::shared_ptr<Texture> tex = nullptr;
  uint32_t layer = 0; // for cube map
  uint32_t level = 0;
};

class FrameBuffer {
 public:
  explicit FrameBuffer(bool offscreen) : offscreen_(offscreen) {}

  virtual int getId() const = 0;
  virtual bool isValid() = 0;

  virtual void setColorAttachment(std::shared_ptr<Texture> &color, int level) {
    colorAttachment_.tex = color;
    colorAttachment_.layer = 0;
    colorAttachment_.level = level;
    colorReady_ = true;
  };

  virtual void setColorAttachment(std::shared_ptr<Texture> &color, CubeMapFace face, int level) {
    colorAttachment_.tex = color;
    colorAttachment_.layer = face;
    colorAttachment_.level = level;
    colorReady_ = true;
  };

  virtual void setDepthAttachment(std::shared_ptr<Texture> &depth) {
    depthAttachment_.tex = depth;
    depthAttachment_.layer = 0;
    depthAttachment_.level = 0;
    depthReady_ = true;
  };

  inline const FrameBufferAttachment &getColorAttachment() const {
    return colorAttachment_;
  }

  inline const FrameBufferAttachment &getDepthAttachment() const {
    return depthAttachment_;
  }

  inline bool isColorReady() const {
    return colorReady_;
  }

  inline bool isDepthReady() const {
    return depthReady_;
  }

  inline bool isMultiSample() const {
    if (colorReady_) {
      return getColorAttachment().tex->multiSample;
    }
    if (depthReady_) {
      return getDepthAttachment().tex->multiSample;
    }

    return false;
  }

  inline bool isOffscreen() const {
    return offscreen_;
  }

  inline void setOffscreen(bool offscreen) {
    offscreen_ = offscreen;
  }

 protected:
  bool offscreen_ = false;
  bool colorReady_ = false;
  bool depthReady_ = false;

  // TODO MTR
  FrameBufferAttachment colorAttachment_{};
  FrameBufferAttachment depthAttachment_{};
};

