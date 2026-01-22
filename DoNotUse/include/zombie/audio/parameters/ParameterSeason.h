#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateManager/DayInfo.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterSeason : public FMODGlobalParameter {
public:
    public ParameterSeason() {
      super("Season");
   }

    float calculateCurrentValue() {
    DayInfo var1 = ClimateManager.getInstance().getCurrentDay();
      if (var1 == nullptr) {
         return 0.0F;
      } else {
    return switch() {
            case 1 -> 0.0F;
            case 2, 3 -> 1.0F;
            case 4 -> 2.0F;
            case 5 -> 3.0F;
            default -> 1.0F;
         };
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
