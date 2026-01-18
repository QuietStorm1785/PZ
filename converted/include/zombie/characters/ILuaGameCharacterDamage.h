#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ILuaGameCharacterDamage {
public:
 virtual ~ILuaGameCharacterDamage() = default;
 BodyDamage getBodyDamage();

 BodyDamage getBodyDamageRemote();

 float getHealth();

 void setHealth(float var1);

 float Hit(BaseVehicle var1, float var2, bool var3, float var4, float var5);

 float Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5);

 float Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5, bool var6);

 bool isOnFire();

 void StopBurning();

 void sendStopBurning();

 int getLastHitCount();

 void setLastHitCount(int var1);

 bool addHole(BloodBodyPartType var1);

 void addBlood(BloodBodyPartType var1, bool var2, bool var3, bool var4);

 bool isBumped();

 std::string getBumpType();

 bool isOnDeathDone();

 void setOnDeathDone(bool var1);

 bool isOnKillDone();

 void setOnKillDone(bool var1);

 bool isDeathDragDown();

 void setDeathDragDown(bool var1);

 bool isPlayingDeathSound();

 void setPlayingDeathSound(bool var1);
}
} // namespace characters
} // namespace zombie
