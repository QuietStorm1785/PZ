#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"

namespace zombie {
namespace ai {
namespace sadisticAIDirector {


class SleepingEventData {
public:
    int forceWakeUpTime = -1;
    bool zombiesIntruders = true;
    int nightmareWakeUp = -1;
    IsoWindow weakestWindow = nullptr;
    IsoDoor openDoor = nullptr;
    bool bRaining = false;
    bool bWasRainingAtStart = false;
    double rainTimeStartHours = -1.0;
    float sleepingTime = 8.0F;

    void reset() {
      this.forceWakeUpTime = -1;
      this.zombiesIntruders = false;
      this.nightmareWakeUp = -1;
      this.openDoor = nullptr;
      this.weakestWindow = nullptr;
      this.bRaining = false;
      this.bWasRainingAtStart = false;
      this.rainTimeStartHours = -1.0;
      this.sleepingTime = 8.0F;
   }

    double getHoursSinceRainStarted() {
      return GameTime.getInstance().getWorldAgeHours() - this.rainTimeStartHours;
   }
}
} // namespace sadisticAIDirector
} // namespace ai
} // namespace zombie
