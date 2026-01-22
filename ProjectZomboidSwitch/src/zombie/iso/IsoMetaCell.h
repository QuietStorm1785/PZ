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
   public const std::vector<VehicleZone> vehicleZones = std::make_unique<std::vector<>>();
   public const IsoMetaChunk[] ChunkMap = new IsoMetaChunk[900];
    LotHeader info = nullptr;
   public const std::vector<Trigger> triggers = std::make_unique<std::vector<>>();
    int wx = 0;
    int wy = 0;
   public const std::vector<MannequinZone> mannequinZones = std::make_unique<std::vector<>>();
   public const std::vector<RoomTone> roomTones = std::make_unique<std::vector<>>();

    public IsoMetaCell(int var1, int var2) {
      this.wx = var1;
      this.wy = var2;

      for (int var3 = 0; var3 < 900; var3++) {
         this.ChunkMap[var3] = std::make_unique<IsoMetaChunk>();
      }
   }

    void addTrigger(BuildingDef var1, int var2, int var3, const std::string& var4) {
      this.triggers.push_back(std::make_shared<Trigger>(var1, var2, var3, var4));
   }

    void checkTriggers() {
      if (IsoCamera.CamCharacter != nullptr) {
    int var1 = (int)IsoCamera.CamCharacter.getX();
    int var2 = (int)IsoCamera.CamCharacter.getY();

         for (int var3 = 0; var3 < this.triggers.size(); var3++) {
    Trigger var4 = this.triggers.get(var3);
            if (var1 >= var4.def.x - var4.triggerRange
               && var1 <= var4.def.x2 + var4.triggerRange
               && var2 >= var4.def.y - var4.triggerRange
               && var2 <= var4.def.y2 + var4.triggerRange) {
               if (!var4.triggered) {
                  LuaEventManager.triggerEvent("OnTriggerNPCEvent", var4.type, var4.data, var4.def);
               }

               LuaEventManager.triggerEvent("OnMultiTriggerNPCEvent", var4.type, var4.data, var4.def);
               var4.triggered = true;
            }
         }
      }
   }

    IsoMetaChunk getChunk(int var1, int var2) {
      return var2 < 30 && var1 < 30 && var1 >= 0 && var2 >= 0 ? this.ChunkMap[var2 * 30 + var1] : nullptr;
   }

    void addZone(Zone var1, int var2, int var3) {
    int var4 = var1.x / 10;
    int var5 = var1.y / 10;
    int var6 = (var1.x + var1.w) / 10;
      if ((var1.x + var1.w) % 10 == 0) {
         var6--;
      }

    int var7 = (var1.y + var1.h) / 10;
      if ((var1.y + var1.h) % 10 == 0) {
         var7--;
      }

      var4 = PZMath.clamp(var4, var2 / 10, (var2 + 300) / 10);
      var5 = PZMath.clamp(var5, var3 / 10, (var3 + 300) / 10);
      var6 = PZMath.clamp(var6, var2 / 10, (var2 + 300) / 10 - 1);
      var7 = PZMath.clamp(var7, var3 / 10, (var3 + 300) / 10 - 1);

      for (int var8 = var5; var8 <= var7; var8++) {
         for (int var9 = var4; var9 <= var6; var9++) {
            if (var1.intersects(var9 * 10, var8 * 10, var1.z, 10, 10)) {
    int var10 = var9 - var2 / 10 + (var8 - var3 / 10) * 30;
               if (this.ChunkMap[var10] != nullptr) {
                  this.ChunkMap[var10].addZone(var1);
               }
            }
         }
      }
   }

    void removeZone(Zone var1) {
    int var2 = (var1.x + var1.w) / 10;
      if ((var1.x + var1.w) % 10 == 0) {
         var2--;
      }

    int var3 = (var1.y + var1.h) / 10;
      if ((var1.y + var1.h) % 10 == 0) {
         var3--;
      }

    int var4 = this.wx * 300;
    int var5 = this.wy * 300;

      for (int var6 = var1.y / 10; var6 <= var3; var6++) {
         for (int var7 = var1.x / 10; var7 <= var2; var7++) {
            if (var7 >= var4 / 10 && var7 < (var4 + 300) / 10 && var6 >= var5 / 10 && var6 < (var5 + 300) / 10) {
    int var8 = var7 - var4 / 10 + (var6 - var5 / 10) * 30;
               if (this.ChunkMap[var8] != nullptr) {
                  this.ChunkMap[var8].removeZone(var1);
               }
            }
         }
      }
   }

    void addRoom(RoomDef var1, int var2, int var3) {
    int var4 = var1.x2 / 10;
      if (var1.x2 % 10 == 0) {
         var4--;
      }

    int var5 = var1.y2 / 10;
      if (var1.y2 % 10 == 0) {
         var5--;
      }

      for (int var6 = var1.y / 10; var6 <= var5; var6++) {
         for (int var7 = var1.x / 10; var7 <= var4; var7++) {
            if (var7 >= var2 / 10 && var7 < (var2 + 300) / 10 && var6 >= var3 / 10 && var6 < (var3 + 300) / 10) {
    int var8 = var7 - var2 / 10 + (var6 - var3 / 10) * 30;
               if (this.ChunkMap[var8] != nullptr) {
                  this.ChunkMap[var8].addRoom(var1);
               }
            }
         }
      }
   }

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
