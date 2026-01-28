#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/iso/weather/ThunderStorm/LightningState.h"

namespace zombie {
namespace iso {
namespace weather {


class ThunderStorm {
public:
    LightningState lightningState;
   zombie::GameTime::AnimTimer timer;
    float lightningStrength;
    float lightningMod;
    ClimateColorInfo lightningColor;
    ClimateColorInfo outColor;
    int x;
    int y;
    int distance;

   private ThunderStorm$PlayerLightningInfo(ThunderStorm var1) {
      this.this$0 = var1;
      this.lightningState = LightningState.Idle;
      this.timer = std::make_unique<AnimTimer>();
      this.lightningStrength = 1.0F;
      this.lightningMod = 0.0F;
      this.lightningColor = std::make_shared<ClimateColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);
      this.outColor = std::make_shared<ClimateColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);
      this.x = 0;
      this.y = 0;
      this.distance = 0;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
