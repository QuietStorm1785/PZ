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
    short cx;
    short cy;
    short currentPopulation;
    short desiredPopulation;
    float lastRepopTime;

   private MPDebugInfo$MPCell() {
   }

   MPDebugInfo$MPCell init(int var1, int var2, int var3, int var4, float var5) {
      this.cx = (short)var1;
      this.cy = (short)var2;
      this.currentPopulation = (short)var3;
      this.desiredPopulation = (short)var4;
      this.lastRepopTime = var5;
    return this;
   }
}
} // namespace popman
} // namespace zombie
