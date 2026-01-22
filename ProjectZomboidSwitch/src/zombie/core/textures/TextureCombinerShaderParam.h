#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {

class TextureCombinerShaderParam {
public:
    std::string name;
    float min;
    float max;

    public TextureCombinerShaderParam(const std::string& var1, float var2, float var3) {
      this.name = var1;
      this.min = var2;
      this.max = var3;
   }

    public TextureCombinerShaderParam(const std::string& var1, float var2) {
      this.name = var1;
      this.min = var2;
      this.max = var2;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
