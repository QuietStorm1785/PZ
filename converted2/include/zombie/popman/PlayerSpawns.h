#pragma once
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
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

class PlayerSpawns {
public:
private
  final ArrayList<PlayerSpawns.PlayerSpawn> playerSpawns =
      std::make_unique<ArrayList<>>();

  void addSpawn(int int0, int int1, int int2) {
    PlayerSpawns.PlayerSpawn playerSpawn =
        new PlayerSpawns.PlayerSpawn(int0, int1, int2);
    if (playerSpawn.building != nullptr) {
      this.playerSpawns.add(playerSpawn);
    }
  }

  void update() {
    long long0 = System.currentTimeMillis();

    for (int int0 = 0; int0 < this.playerSpawns.size(); int0++) {
      PlayerSpawns.PlayerSpawn playerSpawn = this.playerSpawns.get(int0);
      if (playerSpawn.counter == -1L) {
        playerSpawn.counter = long0;
      }

      if (playerSpawn.counter + 10000L <= long0) {
        this.playerSpawns.remove(int0--);
      }
    }
  }

  bool allowZombie(IsoGridSquare square) {
    for (int int0 = 0; int0 < this.playerSpawns.size(); int0++) {
      PlayerSpawns.PlayerSpawn playerSpawn = this.playerSpawns.get(int0);
      if (!playerSpawn.allowZombie(square)) {
        return false;
      }
    }

    return true;
  }

private
  static class PlayerSpawn {
    int x;
    int y;
    long counter;
    BuildingDef building;

  public
    PlayerSpawn(int int0, int int1, int int2) {
      this.x = int0;
      this.y = int1;
      this.counter = -1L;
      RoomDef roomDef =
          IsoWorld.instance.getMetaGrid().getRoomAt(int0, int1, int2);
      if (roomDef != nullptr) {
        this.building = roomDef.getBuilding();
      }
    }

    bool allowZombie(IsoGridSquare square) {
      if (this.building == nullptr) {
        return true;
      } else {
        return square.getBuilding() != nullptr &&
                       this.building == square.getBuilding().getDef()
                   ? false
                   : square.getX() < this.building.getX() - 15 ||
                         square.getX() >= this.building.getX2() + 15 ||
                         square.getY() < this.building.getY() - 15 ||
                         square.getY() >= this.building.getY2() + 15;
      }
    }
  }
}
} // namespace popman
} // namespace zombie
