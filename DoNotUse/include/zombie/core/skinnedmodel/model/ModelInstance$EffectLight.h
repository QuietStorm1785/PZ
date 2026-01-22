#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

class ModelInstance {
public:
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    int radius;

    void set(float var1, float var2, float var3, float var4, float var5, float var6, int var7) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.r = var4;
      this.g = var5;
      this.b = var6;
      this.radius = var7;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
