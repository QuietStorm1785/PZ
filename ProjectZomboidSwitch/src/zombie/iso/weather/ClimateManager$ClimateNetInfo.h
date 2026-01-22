#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace weather {

class ClimateManager {
public:
    bool IsStopWeather = false;
    bool IsTrigger = false;
    bool IsGenerate = false;
    float TriggerDuration = 0.0F;
    bool TriggerStorm = false;
    bool TriggerTropical = false;
    bool TriggerBlizzard = false;
    float GenerateStrength = 0.0F;
    int GenerateFront = 0;

   private ClimateManager$ClimateNetInfo() {
   }

    void reset() {
      this.IsStopWeather = false;
      this.IsTrigger = false;
      this.IsGenerate = false;
      this.TriggerDuration = 0.0F;
      this.TriggerStorm = false;
      this.TriggerTropical = false;
      this.TriggerBlizzard = false;
      this.GenerateStrength = 0.0F;
      this.GenerateFront = 0;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
