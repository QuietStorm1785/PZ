#pragma once
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
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WeaponHit : public Hit {
public:
  float range;
  bool hitHead;

  void set(bool boolean0, float float0, float float4, float float1,
           float float2, float float3, bool boolean1) {
    super.set(boolean0, float0, float1, float2, float3);
    this.range = float4;
    this.hitHead = boolean1;
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    super.parse(byteBuffer, udpConnection);
    this.range = byteBuffer.getFloat();
    this.hitHead = byteBuffer.get() != 0;
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    byteBufferWriter.putFloat(this.range);
    byteBufferWriter.putBoolean(this.hitHead);
  }

  std::string getDescription() {
    return super.getDescription() + "\n\tWeapon [ range=" + this.range +
           " | hitHead=" + this.hitHead + " ]";
  }

  void process(IsoGameCharacter character1, IsoGameCharacter character0,
               HandWeapon weapon) {
    character0.Hit(weapon, character1, this.damage, this.ignore, this.range,
                   true);
    super.process(character1, character0);
    LuaEventManager.triggerEvent("OnWeaponHitXp", character1, weapon,
                                 character0, this.damage);
    if (character1.isAimAtFloor() && !weapon.isRanged() && character1.isNPC()) {
      SwipeStatePlayer.splash(character0, weapon, character1);
    }

    if (this.hitHead) {
      SwipeStatePlayer.splash(character0, weapon, character1);
      SwipeStatePlayer.splash(character0, weapon, character1);
      character0.addBlood(BloodBodyPartType.Head, true, true, true);
      character0.addBlood(BloodBodyPartType.Torso_Upper, true, false, false);
      character0.addBlood(BloodBodyPartType.UpperArm_L, true, false, false);
      character0.addBlood(BloodBodyPartType.UpperArm_R, true, false, false);
    }

    if ((!((IsoLivingCharacter)character1).bDoShove ||
         character1.isAimAtFloor()) &&
        character1.DistToSquared(character0) < 2.0F &&
        Math.abs(character1.z - character0.z) < 0.5F) {
      character1.addBlood(nullptr, false, false, false);
    }

    if (!character0.isDead() && !(character0 instanceof IsoPlayer) &&
        (!((IsoLivingCharacter)character1).bDoShove ||
         character1.isAimAtFloor())) {
      SwipeStatePlayer.splash(character0, weapon, character1);
    }
  }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
