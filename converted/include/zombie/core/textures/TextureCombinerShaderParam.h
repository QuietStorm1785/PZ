#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureCombinerShaderParam {
public:
  std::string name;
  float min;
  float max;

public
  TextureCombinerShaderParam(const std::string &string, float float0,
                             float float1) {
    this.name = string;
    this.min = float0;
    this.max = float1;
  }

public
  TextureCombinerShaderParam(const std::string &string, float float0) {
    this.name = string;
    this.min = float0;
    this.max = float0;
  }
}
} // namespace textures
} // namespace core
} // namespace zombie
