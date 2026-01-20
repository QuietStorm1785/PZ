#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {


// $VF: synthetic class
class HitCharacterPacket {
public:
   static {
      try {
         $SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.PlayerHitSquare.ordinal()] = 1;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.PlayerHitVehicle.ordinal()] = 2;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.PlayerHitZombie.ordinal()] = 3;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.PlayerHitPlayer.ordinal()] = 4;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.ZombieHitPlayer.ordinal()] = 5;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.VehicleHitZombie.ordinal()] = 6;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.VehicleHitPlayer.ordinal()] = 7;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
