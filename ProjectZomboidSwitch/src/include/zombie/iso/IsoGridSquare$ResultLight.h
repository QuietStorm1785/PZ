#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoGridSquare {
public:
    int id;
    int x;
    int y;
    int z;
    int radius;
    float r;
    float g;
    float b;
    static const int RLF_NONE = 0;
    static const int RLF_ROOMLIGHT = 1;
    static const int RLF_TORCH = 2;
    int flags;

   public IsoGridSquare$ResultLight copyFrom(IsoGridSquare$ResultLight var1) {
      this.id = var1.id;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.radius = var1.radius;
      this.r = var1.r;
      this.g = var1.g;
      this.b = var1.b;
      this.flags = var1.flags;
    return this;
   }
}
} // namespace iso
} // namespace zombie
