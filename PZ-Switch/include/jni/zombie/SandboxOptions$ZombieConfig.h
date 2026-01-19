#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions/DoubleSandboxOption.h"
#include "zombie/SandboxOptions/IntegerSandboxOption.h"

namespace zombie {


class SandboxOptions {
:
    const DoubleSandboxOption PopulationMultiplier;
    const DoubleSandboxOption PopulationStartMultiplier;
    const DoubleSandboxOption PopulationPeakMultiplier;
    const IntegerSandboxOption PopulationPeakDay;
    const DoubleSandboxOption RespawnHours;
    const DoubleSandboxOption RespawnUnseenHours;
    const DoubleSandboxOption RespawnMultiplier;
    const DoubleSandboxOption RedistributeHours;
    const IntegerSandboxOption FollowSoundDistance;
    const IntegerSandboxOption RallyGroupSize;
    const IntegerSandboxOption RallyTravelDistance;
    const IntegerSandboxOption RallyGroupSeparation;
    const IntegerSandboxOption RallyGroupRadius;

   private SandboxOptions$ZombieConfig(SandboxOptions var1) {
      this.this$0 = var1;
      this.PopulationMultiplier = var1.newDoubleOption("ZombieConfig.PopulationMultiplier", 0.0, 4.0, 1.0);
      this.PopulationStartMultiplier = var1.newDoubleOption("ZombieConfig.PopulationStartMultiplier", 0.0, 4.0, 1.0);
      this.PopulationPeakMultiplier = var1.newDoubleOption("ZombieConfig.PopulationPeakMultiplier", 0.0, 4.0, 1.5);
      this.PopulationPeakDay = var1.newIntegerOption("ZombieConfig.PopulationPeakDay", 1, 365, 28);
      this.RespawnHours = var1.newDoubleOption("ZombieConfig.RespawnHours", 0.0, 8760.0, 72.0);
      this.RespawnUnseenHours = var1.newDoubleOption("ZombieConfig.RespawnUnseenHours", 0.0, 8760.0, 16.0);
      this.RespawnMultiplier = var1.newDoubleOption("ZombieConfig.RespawnMultiplier", 0.0, 1.0, 0.1);
      this.RedistributeHours = var1.newDoubleOption("ZombieConfig.RedistributeHours", 0.0, 8760.0, 12.0);
      this.FollowSoundDistance = var1.newIntegerOption("ZombieConfig.FollowSoundDistance", 10, 1000, 100);
      this.RallyGroupSize = var1.newIntegerOption("ZombieConfig.RallyGroupSize", 0, 1000, 20);
      this.RallyTravelDistance = var1.newIntegerOption("ZombieConfig.RallyTravelDistance", 5, 50, 20);
      this.RallyGroupSeparation = var1.newIntegerOption("ZombieConfig.RallyGroupSeparation", 5, 25, 15);
      this.RallyGroupRadius = var1.newIntegerOption("ZombieConfig.RallyGroupRadius", 1, 10, 3);
   }
}
} // namespace zombie
