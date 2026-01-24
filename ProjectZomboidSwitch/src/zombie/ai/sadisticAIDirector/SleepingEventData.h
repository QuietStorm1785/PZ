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
      /**
       * Constructs a SleepingEventData object with default values.
       */
      SleepingEventData();
      ~SleepingEventData();

      /**
       * Resets all event data to default values.
       */
      void reset();

      /**
       * Returns the number of hours since rain started.
       */
      double getHoursSinceRainStarted() const;

      // Data members
      int forceWakeUpTime;
      bool zombiesIntruders;
      int nightmareWakeUp;
      IsoWindow weakestWindow;
      IsoDoor openDoor;
      bool bRaining;
      bool bWasRainingAtStart;
      double rainTimeStartHours;
      float sleepingTime;
};
}
} // namespace sadisticAIDirector
} // namespace ai
} // namespace zombie
