#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class AttackVars {
public:
    bool isBareHeadsWeapon;
    MovingObject targetOnGround = std::make_shared<MovingObject>();
    bool bAimAtFloor;
    bool bCloseKill;
    bool bDoShove;
    float useChargeDelta;
    int recoilDelay;
   public const std::vector<HitInfo> targetsStanding = std::make_unique<std::vector<>>();
   public const std::vector<HitInfo> targetsProne = std::make_unique<std::vector<>>();

    void setWeapon(HandWeapon var1) {
      this.isBareHeadsWeapon = "BareHands" == var1.getType());
   }

    HandWeapon getWeapon(IsoLivingCharacter var1) {
      return !this.isBareHeadsWeapon && var1.getUseHandWeapon() != nullptr ? var1.getUseHandWeapon() : var1.bareHands;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
    uint8_t var3 = var1.get();
      this.isBareHeadsWeapon = (var3 & 1) != 0;
      this.bAimAtFloor = (var3 & 2) != 0;
      this.bCloseKill = (var3 & 4) != 0;
      this.bDoShove = (var3 & 8) != 0;
      this.targetOnGround.parse(var1, var2);
      this.useChargeDelta = var1.getFloat();
      this.recoilDelay = var1.getInt();
    uint8_t var4 = var1.get();
      this.targetsStanding.clear();

      for (int var5 = 0; var5 < var4; var5++) {
    HitInfo var6 = std::make_shared<HitInfo>();
         var6.parse(var1, var2);
         this.targetsStanding.push_back(var6);
      }

      var4 = var1.get();
      this.targetsProne.clear();

      for (int var8 = 0; var8 < var4; var8++) {
    HitInfo var9 = std::make_shared<HitInfo>();
         var9.parse(var1, var2);
         this.targetsProne.push_back(var9);
      }
   }

    void write(ByteBufferWriter var1) {
    uint8_t var2 = 0;
      var2 = (byte)(var2 | (byte)(this.isBareHeadsWeapon ? 1 : 0));
      var2 = (byte)(var2 | (byte)(this.bAimAtFloor ? 2 : 0));
      var2 = (byte)(var2 | (byte)(this.bCloseKill ? 4 : 0));
      var2 = (byte)(var2 | (byte)(this.bDoShove ? 8 : 0));
      var1.putByte(var2);
      this.targetOnGround.write(var1);
      var1.putFloat(this.useChargeDelta);
      var1.putInt(this.recoilDelay);
    uint8_t var3 = (byte)Math.min(100, this.targetsStanding.size());
      var1.putByte(var3);

      for (int var4 = 0; var4 < var3; var4++) {
    HitInfo var5 = this.targetsStanding.get(var4);
         var5.write(var1);
      }

      var3 = (byte)Math.min(100, this.targetsProne.size());
      var1.putByte(var3);

      for (int var11 = 0; var11 < var3; var11++) {
    HitInfo var12 = this.targetsProne.get(var11);
         var12.write(var1);
      }
   }

    int getPacketSizeBytes() {
    int var1 = 11 + this.targetOnGround.getPacketSizeBytes();
    uint8_t var2 = (byte)Math.min(100, this.targetsStanding.size());

      for (int var3 = 0; var3 < var2; var3++) {
    HitInfo var4 = this.targetsStanding.get(var3);
         var1 += var4.getPacketSizeBytes();
      }

      var2 = (byte)Math.min(100, this.targetsProne.size());

      for (int var6 = 0; var6 < var2; var6++) {
    HitInfo var7 = this.targetsProne.get(var6);
         var1 += var7.getPacketSizeBytes();
      }

    return var1;
   }

    std::string getDescription() {
    std::string var1 = "";
    uint8_t var2 = (byte)Math.min(100, this.targetsStanding.size());

      for (int var3 = 0; var3 < var2; var3++) {
    HitInfo var4 = this.targetsStanding.get(var3);
         var1 = var1 + var4.getDescription();
      }

    std::string var7 = "";
      var2 = (byte)Math.min(100, this.targetsProne.size());

      for (int var8 = 0; var8 < var2; var8++) {
    HitInfo var5 = this.targetsProne.get(var8);
         var7 = var7 + var5.getDescription();
      }

      return "\n\tHitInfo [ isBareHeadsWeapon="
         + this.isBareHeadsWeapon
         + " bAimAtFloor="
         + this.bAimAtFloor
         + " bCloseKill="
         + this.bCloseKill
         + " bDoShove="
         + this.bDoShove
         + " useChargeDelta="
         + this.useChargeDelta
         + " recoilDelay="
         + this.recoilDelay
         + "\n\t  targetOnGround:"
         + this.targetOnGround.getDescription()
         + "\n\t  targetsStanding=["
         + var1
         + "](size="
         + this.targetsStanding.size()
         + ")\n\t  targetsProne=["
         + var7
         + "](size="
         + this.targetsProne.size()
         + ")]";
   }

    void copy(AttackVars var1) {
      this.isBareHeadsWeapon = var1.isBareHeadsWeapon;
      this.targetOnGround = var1.targetOnGround;
      this.bAimAtFloor = var1.bAimAtFloor;
      this.bCloseKill = var1.bCloseKill;
      this.bDoShove = var1.bDoShove;
      this.useChargeDelta = var1.useChargeDelta;
      this.recoilDelay = var1.recoilDelay;
      this.targetsStanding.clear();

      for (HitInfo var3 : var1.targetsStanding) {
         this.targetsStanding.push_back(var3);
      }

      this.targetsProne.clear();

      for (HitInfo var5 : var1.targetsProne) {
         this.targetsProne.push_back(var5);
      }
   }

    void clear() {
      this.targetOnGround.setMovingObject(nullptr);
      this.targetsStanding.clear();
      this.targetsProne.clear();
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
