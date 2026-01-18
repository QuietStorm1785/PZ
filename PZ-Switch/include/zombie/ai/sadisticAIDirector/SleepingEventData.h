#pragma once
#include "zombie/GameTime.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace sadisticAIDirector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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
 this->forceWakeUpTime = -1;
 this->zombiesIntruders = false;
 this->nightmareWakeUp = -1;
 this->openDoor = nullptr;
 this->weakestWindow = nullptr;
 this->bRaining = false;
 this->bWasRainingAtStart = false;
 this->rainTimeStartHours = -1.0;
 this->sleepingTime = 8.0F;
 }

 double getHoursSinceRainStarted() {
 return GameTime.getInstance().getWorldAgeHours() - this->rainTimeStartHours;
 }
}
} // namespace sadisticAIDirector
} // namespace ai
} // namespace zombie
