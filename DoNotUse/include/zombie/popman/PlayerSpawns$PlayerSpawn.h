#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace popman {


class PlayerSpawns {
public:
    int x;
    int y;
    long counter;
    BuildingDef building;

   public PlayerSpawns$PlayerSpawn(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.counter = -1L;
    RoomDef var4 = IsoWorld.instance.getMetaGrid().getRoomAt(var1, var2, var3);
      if (var4 != nullptr) {
         this.building = var4.getBuilding();
      }
   }

    bool allowZombie(IsoGridSquare var1) {
      if (this.building == nullptr) {
    return true;
      } else {
         return var1.getBuilding() != nullptr && this.building == var1.getBuilding().getDef()
            ? false
            : var1.getX() < this.building.getX() - 15
               || var1.getX() >= this.building.getX2() + 15
               || var1.getY() < this.building.getY() - 15
               || var1.getY() >= this.building.getY2() + 15;
      }
   }
}
} // namespace popman
} // namespace zombie
