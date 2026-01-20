#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace iso {


class IsoHeatSource {
public:
    int x;
    int y;
    int z;
    int radius;
    int temperature;

    public IsoHeatSource(int var1, int var2, int var3, int var4, int var5) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.radius = var4;
      this.temperature = var5;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    int getZ() {
      return this.z;
   }

    int getRadius() {
      return this.radius;
   }

    void setRadius(int var1) {
      this.radius = var1;
   }

    int getTemperature() {
      return this.temperature;
   }

    void setTemperature(int var1) {
      this.temperature = var1;
   }

    bool isInBounds(int var1, int var2, int var3, int var4) {
      return this.x >= var1 && this.x < var3 && this.y >= var2 && this.y < var4;
   }

    bool isInBounds() {
      IsoChunkMap[] var1 = IsoWorld.instance.CurrentCell.ChunkMap;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (!var1[var2].ignore) {
    int var3 = var1[var2].getWorldXMinTiles();
    int var4 = var1[var2].getWorldXMaxTiles();
    int var5 = var1[var2].getWorldYMinTiles();
    int var6 = var1[var2].getWorldYMaxTiles();
            if (this.isInBounds(var3, var5, var4, var6)) {
    return true;
            }
         }
      }

    return false;
   }
}
} // namespace iso
} // namespace zombie
