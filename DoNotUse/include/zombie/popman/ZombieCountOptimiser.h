#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/MPStatistics.h"

namespace zombie {
namespace popman {


class ZombieCountOptimiser {
public:
    static int zombieCountForDelete = 0;
    static const int maxZombieCount = 500;
    static const int minZombieDistance = 20;
   public static const std::vector<IsoZombie> zombiesForDelete = std::make_unique<std::vector<>>();

    static void startCount() {
      zombieCountForDelete = (int)(1.0F * Math.max(0, GameClient.IDToZombieMap.values().length - 500));
   }

    static void incrementZombie(IsoZombie var0) {
      if (zombieCountForDelete > 0 && Rand.Next(10) == 0 && var0.canBeDeletedUnnoticed(20.0F) && !var0.isReanimatedPlayer()) {
         /* synchronized - TODO: add std::mutex */ (zombiesForDelete) {
            zombiesForDelete.push_back(var0);
         }

         zombieCountForDelete--;
         MPStatistics.clientZombieCulled();
      }
   }
}
} // namespace popman
} // namespace zombie
