#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateManager/DayInfo.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterTimeOfDay : public OpenALParameterStub {
public:
    public ParameterTimeOfDay() {
      super("TimeOfDay");
   }

    float calculateCurrentValue() {
    DayInfo var1 = ClimateManager.getInstance().getCurrentDay();
      if (var1 == nullptr) {
         return 1.0F;
      } else {
    float var2 = var1.season.getDawn();
    float var3 = var1.season.getDusk();
    float var4 = var1.season.getDayHighNoon();
    float var5 = GameTime.instance.getTimeOfDay();
         if (var5 >= var2 - 1.0F && var5 < var2 + 1.0F) {
            return 0.0F;
         } else if (var5 >= var2 + 1.0F && var5 < var2 + 2.0F) {
            return 1.0F;
         } else if (var5 >= var2 + 2.0F && var5 < var3 - 2.0F) {
            return 2.0F;
         } else if (var5 >= var3 - 2.0F && var5 < var3 - 1.0F) {
            return 3.0F;
         } else {
            return var5 >= var3 - 1.0F && var5 < var3 + 1.0F ? 4.0F : 5.0F;
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
