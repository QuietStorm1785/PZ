#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class EngineRPMData {
public:
    float gearChange;
    float afterGearChange;

    public EngineRPMData() {
   }

    public EngineRPMData(float var1, float var2) {
      this.gearChange = var1;
      this.afterGearChange = var2;
   }

    void reset() {
      this.gearChange = 0.0F;
      this.afterGearChange = 0.0F;
   }
}
} // namespace vehicles
} // namespace zombie
