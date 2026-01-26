   // --- Methods implemented in header for completeness ---
   // (See Java/C++ sources for logic)

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoMetaGrid/RoomTone.h"
#include "zombie/iso/IsoMetaGrid/Trigger.h"
#include "zombie/iso/IsoMetaGrid/VehicleZone.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/objects/IsoMannequin/MannequinZone.h"

namespace zombie {
namespace iso {


class IsoMetaCell {
public:
   std::vector<std::shared_ptr<VehicleZone>> vehicleZones;
   std::vector<std::shared_ptr<IsoMetaChunk>> ChunkMap;
   std::shared_ptr<LotHeader> info;
   std::vector<std::shared_ptr<Trigger>> triggers;
   int wx = 0;
   int wy = 0;
   std::vector<std::shared_ptr<MannequinZone>> mannequinZones;
   std::vector<std::shared_ptr<RoomTone>> roomTones;

   IsoMetaCell(int wx_, int wy_) : wx(wx_), wy(wy_), ChunkMap(900) {
      for (int i = 0; i < 900; ++i) {
         ChunkMap[i] = std::make_shared<IsoMetaChunk>();
      }
   }

};
} // namespace iso
} // namespace zombie


    void getZonesUnique(Set<Zone> var1) {
      for (int var2 = 0; var2 < this.ChunkMap.length; var2++) {
    IsoMetaChunk var3 = this.ChunkMap[var2];
         if (var3 != nullptr) {
            var3.getZonesUnique(var1);
         }
      }
   }

    void getZonesIntersecting(int var1, int var2, int var3, int var4, int var5, std::vector<Zone> var6) {
    int var7 = (var1 + var4) / 10;
      if ((var1 + var4) % 10 == 0) {
         var7--;
      }

    int var8 = (var2 + var5) / 10;
      if ((var2 + var5) % 10 == 0) {
         var8--;
      }

    int var9 = this.wx * 300;
    int var10 = this.wy * 300;

      for (int var11 = var2 / 10; var11 <= var8; var11++) {
         for (int var12 = var1 / 10; var12 <= var7; var12++) {
            if (var12 >= var9 / 10 && var12 < (var9 + 300) / 10 && var11 >= var10 / 10 && var11 < (var10 + 300) / 10) {
    int var13 = var12 - var9 / 10 + (var11 - var10 / 10) * 30;
               if (this.ChunkMap[var13] != nullptr) {
                  this.ChunkMap[var13].getZonesIntersecting(var1, var2, var3, var4, var5, var6);
               }
            }
         }
      }
   }

    void getRoomsIntersecting(int var1, int var2, int var3, int var4, std::vector<RoomDef> var5) {
    int var6 = (var1 + var3) / 10;
      if ((var1 + var3) % 10 == 0) {
         var6--;
      }

    int var7 = (var2 + var4) / 10;
      if ((var2 + var4) % 10 == 0) {
         var7--;
      }

    int var8 = this.wx * 300;
    int var9 = this.wy * 300;

      for (int var10 = var2 / 10; var10 <= var7; var10++) {
         for (int var11 = var1 / 10; var11 <= var6; var11++) {
            if (var11 >= var8 / 10 && var11 < (var8 + 300) / 10 && var10 >= var9 / 10 && var10 < (var9 + 300) / 10) {
    int var12 = var11 - var8 / 10 + (var10 - var9 / 10) * 30;
               if (this.ChunkMap[var12] != nullptr) {
                  this.ChunkMap[var12].getRoomsIntersecting(var1, var2, var3, var4, var5);
               }
            }
         }
      }
   }

    void Dispose() {
      for (int var1 = 0; var1 < this.ChunkMap.length; var1++) {
    IsoMetaChunk var2 = this.ChunkMap[var1];
         if (var2 != nullptr) {
            var2.Dispose();
            this.ChunkMap[var1] = nullptr;
         }
      }

      this.info = nullptr;
      this.mannequinZones.clear();
      this.roomTones.clear();
   }
}
} // namespace iso
} // namespace zombie
