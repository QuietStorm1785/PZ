#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoGridSquare/GetSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/ServerMap/ServerCell.h"

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
    ServerCell cell;

   private ServerChunkLoader$GetSquare(ServerChunkLoader var1) {
      this.this$0 = var1;
   }

    IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      var1 -= this.cell.WX * 50;
      var2 -= this.cell.WY * 50;
      if (var1 < 0 || var1 >= 50) {
    return nullptr;
      } else if (var2 >= 0 && var2 < 50) {
    IsoChunk var4 = this.cell.chunks[var1 / 10][var2 / 10];
    return var4 = = nullptr ? nullptr : var4.getGridSquare(var1 % 10, var2 % 10, var3);
      } else {
    return nullptr;
      }
   }

    bool contains(int var1, int var2, int var3) {
      return var1 < 0 || var1 >= 50 ? false : var2 >= 0 && var2 < 50;
   }

    IsoChunk getChunkForSquare(int var1, int var2) {
      var1 -= this.cell.WX * 50;
      var2 -= this.cell.WY * 50;
      if (var1 < 0 || var1 >= 50) {
    return nullptr;
      } else {
         return var2 >= 0 && var2 < 50 ? this.cell.chunks[var1 / 10][var2 / 10] : nullptr;
      }
   }

    void EnsureSurroundNotNull(int var1, int var2, int var3) {
    int var4 = this.cell.WX * 50;
    int var5 = this.cell.WY * 50;

      for (int var6 = -1; var6 <= 1; var6++) {
         for (int var7 = -1; var7 <= 1; var7++) {
            if ((var6 != 0 || var7 != 0) && this.contains(var1 + var6, var2 + var7, var3)) {
    IsoGridSquare var8 = this.getGridSquare(var4 + var1 + var6, var5 + var2 + var7, var3);
               if (var8 == nullptr) {
                  var8 = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, nullptr, var4 + var1 + var6, var5 + var2 + var7, var3);
    int var9 = (var1 + var6) / 10;
    int var10 = (var2 + var7) / 10;
    int var11 = (var1 + var6) % 10;
    int var12 = (var2 + var7) % 10;
                  if (this.cell.chunks[var9][var10] != nullptr) {
                     this.cell.chunks[var9][var10].setSquare(var11, var12, var3, var8);
                  }
               }
            }
         }
      }
   }
}
} // namespace network
} // namespace zombie
