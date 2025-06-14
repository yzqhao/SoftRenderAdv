

#pragma once

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include "Base/UUID.h"
#include "Texture.h"

class ShaderProgram;

class Uniform {
 public:
  explicit Uniform(std::string name) : name(std::move(name)) {}

  inline int getHash() const {
    return uuid_.get();
  }

  virtual int getLocation(ShaderProgram &program) = 0;
  virtual void bindProgram(ShaderProgram &program, int location) = 0;

 public:
  std::string name;

 private:
  UUID<Uniform> uuid_;
};

class UniformBlock : public Uniform {
 public:
  UniformBlock(const std::string &name, int size) : Uniform(name), blockSize(size) {}

  virtual void setSubData(void *data, int len, int offset) = 0;
  virtual void setData(void *data, int len) = 0;

 protected:
  int blockSize;
};

class UniformSampler : public Uniform {
 public:
  UniformSampler(const std::string &name, TextureType type, TextureFormat format)
      : Uniform(name), type(type), format(format) {}
  virtual void setTexture(const std::shared_ptr<Texture> &tex) = 0;

 protected:
  TextureType type;
  TextureFormat format;
};

class ShaderResources {
 public:
  std::unordered_map<int, std::shared_ptr<UniformBlock>> blocks;
  std::unordered_map<int, std::shared_ptr<UniformSampler>> samplers;
};

