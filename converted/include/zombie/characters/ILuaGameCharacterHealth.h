#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ILuaGameCharacterHealth {
public:
 virtual ~ILuaGameCharacterHealth() = default;
 void setSleepingTabletEffect(float var1);

 float getSleepingTabletEffect();

 float getFatigueMod();

 bool Eat(InventoryItem var1, float var2);

 bool Eat(InventoryItem var1);

 float getTemperature();

 void setTemperature(float var1);

 float getReduceInfectionPower();

 void setReduceInfectionPower(float var1);

 int getLastHourSleeped();

 void setLastHourSleeped(int var1);

 void setTimeOfSleep(float var1);
}
} // namespace characters
} // namespace zombie
