#include "zombie/ai/sadisticAIDirector/SleepingEventData.h"

namespace zombie {
namespace ai {
namespace sadisticAIDirector {

void SleepingEventData::reset() {
    forceWakeUpTime = -1;
    zombiesIntruders = false;
    nightmareWakeUp = -1;
    openDoor = nullptr;
    weakestWindow = nullptr;
    bRaining = false;
    bWasRainingAtStart = false;
    rainTimeStartHours = -1.0;
    sleepingTime = 8.0F;
}

double SleepingEventData::getHoursSinceRainStarted() {
    // Returns hours since rain started, or 0 if not started
    if (rainTimeStartHours < 0.0)
        return 0.0;
    return GameTime::getInstance().getWorldAgeHours() - rainTimeStartHours;
}

} // namespace sadisticAIDirector
} // namespace ai
} // namespace zombie
