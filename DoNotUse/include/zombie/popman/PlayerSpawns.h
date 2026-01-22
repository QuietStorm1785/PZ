#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/popman/PlayerSpawns/PlayerSpawn.h"

namespace zombie {
namespace popman {


class PlayerSpawns {
public:
   private const std::vector<PlayerSpawn> playerSpawns = std::make_unique<std::vector<>>();

    void addSpawn(int var1, int var2, int var3) {
    PlayerSpawn var4 = std::make_shared<PlayerSpawn>(var1, var2, var3);
      if (var4.building != nullptr) {
         this.playerSpawns.push_back(var4);
      }
   }

    void update() {
    long var1 = System.currentTimeMillis();

      for (int var3 = 0; var3 < this.playerSpawns.size(); var3++) {
    PlayerSpawn var4 = this.playerSpawns.get(var3);
         if (var4.counter == -1L) {
            var4.counter = var1;
         }

         if (var4.counter + 10000L <= var1) {
            this.playerSpawns.remove(var3--);
         }
      }
   }

    bool allowZombie(IsoGridSquare var1) {
      for (int var2 = 0; var2 < this.playerSpawns.size(); var2++) {
    PlayerSpawn var3 = this.playerSpawns.get(var2);
         if (!var3.allowZombie(var1)) {
    return false;
         }
      }

    return true;
   }
}
} // namespace popman
} // namespace zombie
