#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/MPStatistics.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombieCountOptimiser {
public:
  static int zombieCountForDelete = 0;
  static const int maxZombieCount = 500;
  static const int minZombieDistance = 20;
public
  static final ArrayList<IsoZombie> zombiesForDelete =
      std::make_unique<ArrayList<>>();

  static void startCount() {
    zombieCountForDelete =
        (int)(1.0F *
              Math.max(0, GameClient.IDToZombieMap.values().length - 500));
  }

  static void incrementZombie(IsoZombie zombie0) {
    if (zombieCountForDelete > 0 && Rand.Next(10) == 0 &&
        zombie0.canBeDeletedUnnoticed(20.0F) && !zombie0.isReanimatedPlayer()) {
      synchronized(zombiesForDelete) { zombiesForDelete.add(zombie0); }

      zombieCountForDelete--;
      MPStatistics.clientZombieCulled();
    }
  }
}
} // namespace popman
} // namespace zombie
