#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/FliesSound/ChunkLevelData.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoBuilding.h"

namespace zombie {


class FliesSound {
:
    int wx;
    int wy;
   private ChunkLevelData[] levelData;

   private FliesSound$ChunkData(FliesSound var1, int var2, int var3) {
      this.this$0 = var1;
      this.levelData = new ChunkLevelData[8];
      this.wx = var2;
      this.wy = var3;

      for (int var4 = 0; var4 < this.levelData.length; var4++) {
         this.levelData[var4] = new ChunkLevelData(var1);
      }
   }

    void corpseAdded(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
    IsoBuilding var5 = var4 == nullptr ? nullptr : var4.getBuilding();
    int var6 = var1 - this.wx * 10;
    int var7 = var2 - this.wy * 10;
      this.levelData[var3].corpseAdded(var6, var7, var5);
   }

    void corpseRemoved(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
    IsoBuilding var5 = var4 == nullptr ? nullptr : var4.getBuilding();
    int var6 = var1 - this.wx * 10;
    int var7 = var2 - this.wy * 10;
      this.levelData[var3].corpseRemoved(var6, var7, var5);
   }

    void Reset() {
      for (int var1 = 0; var1 < this.levelData.length; var1++) {
         this.levelData[var1].Reset();
      }
   }
}
} // namespace zombie
