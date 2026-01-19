#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions/BooleanSandboxOption.h"
#include "zombie/SandboxOptions/EnumSandboxOption.h"

namespace zombie {


class SandboxOptions {
public:
    const EnumSandboxOption Speed;
    const EnumSandboxOption Strength;
    const EnumSandboxOption Toughness;
    const EnumSandboxOption Transmission;
    const EnumSandboxOption Mortality;
    const EnumSandboxOption Reanimate;
    const EnumSandboxOption Cognition;
    const EnumSandboxOption CrawlUnderVehicle;
    const EnumSandboxOption Memory;
    const EnumSandboxOption Sight;
    const EnumSandboxOption Hearing;
    const BooleanSandboxOption ThumpNoChasing;
    const BooleanSandboxOption ThumpOnConstruction;
    const EnumSandboxOption ActiveOnly;
    const BooleanSandboxOption TriggerHouseAlarm;
    const BooleanSandboxOption ZombiesDragDown;
    const BooleanSandboxOption ZombiesFenceLunge;
    const EnumSandboxOption DisableFakeDead;

   private SandboxOptions$ZombieLore(SandboxOptions var1) {
      this.this$0 = var1;
      this.Speed = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Speed", 4, 2).setTranslation("ZSpeed");
      this.Strength = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Strength", 4, 2).setTranslation("ZStrength");
      this.Toughness = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Toughness", 4, 2).setTranslation("ZToughness");
      this.Transmission = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Transmission", 4, 1).setTranslation("ZTransmission");
      this.Mortality = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Mortality", 7, 5).setTranslation("ZInfectionMortality");
      this.Reanimate = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Reanimate", 6, 3).setTranslation("ZReanimateTime");
      this.Cognition = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Cognition", 4, 3).setTranslation("ZCognition");
      this.CrawlUnderVehicle = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.CrawlUnderVehicle", 7, 5).setTranslation("ZCrawlUnderVehicle");
      this.Memory = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Memory", 5, 2).setTranslation("ZMemory");
      this.Sight = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Sight", 4, 2).setTranslation("ZSight");
      this.Hearing = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.Hearing", 4, 2).setTranslation("ZHearing");
      this.ThumpNoChasing = var1.newBooleanOption("ZombieLore.ThumpNoChasing", false);
      this.ThumpOnConstruction = var1.newBooleanOption("ZombieLore.ThumpOnConstruction", true);
      this.ActiveOnly = static_cast<EnumSandboxOption>(var1).newEnumOption("ZombieLore.ActiveOnly", 3, 1).setTranslation("ActiveOnly");
      this.TriggerHouseAlarm = var1.newBooleanOption("ZombieLore.TriggerHouseAlarm", false);
      this.ZombiesDragDown = var1.newBooleanOption("ZombieLore.ZombiesDragDown", true);
      this.ZombiesFenceLunge = var1.newBooleanOption("ZombieLore.ZombiesFenceLunge", true);
      this.DisableFakeDead = var1.newEnumOption("ZombieLore.DisableFakeDead", 3, 1);
   }
}
} // namespace zombie
