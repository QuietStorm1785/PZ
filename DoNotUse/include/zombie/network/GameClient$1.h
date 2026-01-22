#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie/ZombieSound.h"

namespace zombie {
namespace network {


// $VF: synthetic class
class GameClient {
public:
   static {
      try {
         $SwitchMap$zombie$characters$IsoZombie$ZombieSound[ZombieSound.Burned.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$characters$IsoZombie$ZombieSound[ZombieSound.DeadCloseKilled.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$characters$IsoZombie$ZombieSound[ZombieSound.DeadNotCloseKilled.ordinal()] = 3;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$characters$IsoZombie$ZombieSound[ZombieSound.Hurt.ordinal()] = 4;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$characters$IsoZombie$ZombieSound[ZombieSound.Idle.ordinal()] = 5;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$characters$IsoZombie$ZombieSound[ZombieSound.Lunge.ordinal()] = 6;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace network
} // namespace zombie
