#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"

namespace zombie {
namespace iso {
namespace weather {


class ThunderStorm {
public:
    int eventX;
    int eventY;
    bool doLightning = false;
    bool doRumble = false;
    bool doStrike = false;
    zombie::GameTime::AnimTimer soundDelay;
    bool isRunning = false;

   private ThunderStorm$ThunderEvent() {
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
