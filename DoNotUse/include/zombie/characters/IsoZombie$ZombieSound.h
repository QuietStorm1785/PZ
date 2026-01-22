#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

enum class IsoZombie {
   Burned(10),
   DeadCloseKilled(10),
   DeadNotCloseKilled(10),
   Hurt(10),
   Idle(15),
   Lunge(40),
   MAX(-1);

    int radius;
   private static const IsoZombie$ZombieSound[] values = values();

   private IsoZombie$ZombieSound(int var3) {
      this.radius = var3;
   }

    int radius() {
      return this.radius;
   }

   public static IsoZombie$ZombieSound fromIndex(int var0) {
      return var0 >= 0 && var0 < values.length ? values[var0] : MAX;
   }
}
} // namespace characters
} // namespace zombie
