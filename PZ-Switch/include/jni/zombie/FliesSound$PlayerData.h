#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/FliesSound/ChunkData.h"
#include "zombie/FliesSound/ChunkLevelData.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/areas/IsoBuilding.h"

namespace zombie {


class FliesSound {
:
    int wx;
    int wy;
    int z;
    IsoBuilding building;
    bool forceUpdate;

   FliesSound$PlayerData(FliesSound var1) {
      this.this$0 = var1;
      this.wx = -1;
      this.wy = -1;
      this.z = -1;
      this.building = nullptr;
      this.forceUpdate = false;
   }

    bool isSameLocation(IsoPlayer var1) {
    IsoGridSquare var2 = var1.getCurrentSquare();
      return var2 != nullptr && var2.getBuilding() != this.building
         ? false
         : (int)var1.getX() / 10 == this.wx && (int)var1.getY() / 10 == this.wy && (int)var1.getZ() == this.z;
   }

    void update(IsoPlayer var1) {
      if (this.forceUpdate || !this.isSameLocation(var1)) {
         this.forceUpdate = false;
    int var2 = this.wx;
    int var3 = this.wy;
    int var4 = this.z;
    IsoGridSquare var5 = var1.getCurrentSquare();
         this.wx = var5.getX() / 10;
         this.wy = var5.getY() / 10;
         this.z = var5.getZ();
         this.building = var5.getBuilding();

         for (int var6 = -1; var6 <= 1; var6++) {
            for (int var7 = -1; var7 <= 1; var7++) {
    ChunkData var8 = this.this$0.getChunkData((this.wx + var7) * 10, (this.wy + var6) * 10);
               if (var8 != nullptr) {
    ChunkLevelData var9 = var8.levelData[this.z];
                  var9.update(this.wx + var7, this.wy + var6, this.z, var1);
               }
            }
         }

         if (var4 != -1) {
            for (int var10 = -1; var10 <= 1; var10++) {
               for (int var11 = -1; var11 <= 1; var11++) {
    ChunkData var12 = this.this$0.getChunkData((var2 + var11) * 10, (var3 + var10) * 10);
                  if (var12 != nullptr) {
    ChunkLevelData var13 = var12.levelData[var4];
                     var13.deref(var1);
                  }
               }
            }
         }
      }
   }

    void Reset() {
      this.wx = this.wy = this.z = -1;
      this.building = nullptr;
      this.forceUpdate = false;
   }
}
} // namespace zombie
