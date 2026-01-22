#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace popman {

class MPDebugInfo {
public:
    int wx;
    int wy;
    float worldAge;

   private MPDebugInfo$MPRepopEvent() {
   }

   public MPDebugInfo$MPRepopEvent init(int var1, int var2, float var3) {
      this.wx = var1;
      this.wy = var2;
      this.worldAge = var3;
    return this;
   }
}
} // namespace popman
} // namespace zombie
