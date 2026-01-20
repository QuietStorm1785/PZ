#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class WeaponHit : public Hit {
public:
    float range;
    bool hitHead;

    void set(bool var1, float var2, float var3, float var4, float var5, float var6, bool var7) {
      super.set(var1, var2, var4, var5, var6);
      this.range = var3;
      this.hitHead = var7;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.range = var1.getFloat();
      this.hitHead = var1.get() != 0;
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      var1.putFloat(this.range);
      var1.putBoolean(this.hitHead);
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tWeapon [ range=" + this.range + " | hitHead=" + this.hitHead + " ]";
   }

    void process(IsoGameCharacter var1, IsoGameCharacter var2, HandWeapon var3) {
      var2.Hit(var3, var1, this.damage, this.ignore, this.range, true);
      super.process(var1, var2);
      LuaEventManager.triggerEvent("OnWeaponHitXp", var1, var3, var2, this.damage);
      if (var1.isAimAtFloor() && !var3.isRanged() && var1.isNPC()) {
         SwipeStatePlayer.splash(var2, var3, var1);
      }

      if (this.hitHead) {
         SwipeStatePlayer.splash(var2, var3, var1);
         SwipeStatePlayer.splash(var2, var3, var1);
         var2.addBlood(BloodBodyPartType.Head, true, true, true);
         var2.addBlood(BloodBodyPartType.Torso_Upper, true, false, false);
         var2.addBlood(BloodBodyPartType.UpperArm_L, true, false, false);
         var2.addBlood(BloodBodyPartType.UpperArm_R, true, false, false);
      }

      if ((!((IsoLivingCharacter)var1).bDoShove || var1.isAimAtFloor()) && var1.DistToSquared(var2) < 2.0F && Math.abs(var1.z - var2.z) < 0.5F) {
         var1.addBlood(nullptr, false, false, false);
      }

      if (!var2.isDead() && !(dynamic_cast<IsoPlayer*>(var2) != nullptr) && (!((IsoLivingCharacter)var1).bDoShove || var1.isAimAtFloor())) {
         SwipeStatePlayer.splash(var2, var3, var1);
      }
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
