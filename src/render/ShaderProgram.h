
#pragma once

#include <unordered_map>
#include <set>
#include "Uniform.h"

class ShaderProgram {
 public:
  virtual int getId() const = 0;

  virtual void addDefine(const std::string &def) = 0;

  virtual void addDefines(const std::set<std::string> &defs) {
    for (auto &str : defs) {
      addDefine(str);
    }
  }

  virtual void bindResources(ShaderResources &resources) {
    for (auto &kv : resources.blocks) {
      bindUniform(*kv.second);
    }

    for (auto &kv : resources.samplers) {
      bindUniform(*kv.second);
    }
  }

 protected:
  virtual bool bindUniform(Uniform &uniform) {
    int hash = uniform.getHash();
    int location = -1;
    if (uniformLocations_.find(hash) == uniformLocations_.end()) {
      location = uniform.getLocation(*this);
      uniformLocations_[hash] = location;
    } else {
      location = uniformLocations_[hash];
    }

    if (location < 0) {
      return false;
    }

    uniform.bindProgram(*this, location);
    return true;
  };

 protected:
  std::unordered_map<int, int> uniformLocations_;
};

