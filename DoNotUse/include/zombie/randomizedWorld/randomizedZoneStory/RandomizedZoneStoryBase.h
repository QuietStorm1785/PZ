#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/randomizedWorld/RandomizedWorldBase.h"
#include "zombie/util/Type.h"
#include <iterator>

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {


class RandomizedZoneStoryBase : public RandomizedWorldBase {
public:
    bool alwaysDo = false;
    static const int baseChance = 15;
    static int totalChance = 0;
    static const std::string zoneStory = "ZoneStory";
    int chance = 0;
    int minZoneWidth = 0;
    int minZoneHeight = 0;
   public const std::vector<std::string> zoneType = std::make_unique<std::vector<>>();
   private static const std::unordered_map<RandomizedZoneStoryBase, int> rzsMap = std::make_unique<std::unordered_map<>>();

    static bool isValidForStory(Zone var0, bool var1) {
      if (var0.pickedXForZoneStory > 0 && var0.pickedYForZoneStory > 0 && var0.pickedRZStory != nullptr && checkCanSpawnStory(var0, var1)) {
         var0.pickedRZStory.randomizeZoneStory(var0);
         var0.pickedRZStory = nullptr;
         var0.pickedXForZoneStory = 0;
         var0.pickedYForZoneStory = 0;
      }

      if (!var1 && var0.hourLastSeen != 0) {
    return false;
      } else if (!var1 && var0.haveConstruction) {
    return false;
      } else if ("ZoneStory" == var0.type)) {
         doRandomStory(var0);
    return true;
      } else {
    return false;
      }
   }

    static void initAllRZSMapChance(Zone var0) {
      totalChance = 0;
      rzsMap.clear();

      for (int var1 = 0; var1 < IsoWorld.instance.getRandomizedZoneList().size(); var1++) {
    RandomizedZoneStoryBase var2 = (RandomizedZoneStoryBase)IsoWorld.instance.getRandomizedZoneList().get(var1);
         if (var2.isValid(var0, false) && var2.isTimeValid(false)) {
            totalChance = totalChance + var2.chance;
            rzsMap.put(var2, var2.chance);
         }
      }
   }

    bool isValid(Zone var1, bool var2) {
    bool var3 = false;

      for (int var4 = 0; var4 < this.zoneType.size(); var4++) {
         if (this.zoneType.get(var4) == var1.name)) {
            var3 = true;
            break;
         }
      }

      return var3 && var1.w >= this.minZoneWidth && var1.h >= this.minZoneHeight;
   }

    static bool doRandomStory(Zone var0) {
      var0.hourLastSeen++;
    uint8_t var1 = 6;
      switch (SandboxOptions.instance.ZoneStoryChance.getValue()) {
         case 1:
    return false;
         case 2:
            var1 = 2;
         case 3:
         default:
            break;
         case 4:
            var1 = 12;
            break;
         case 5:
            var1 = 20;
            break;
         case 6:
            var1 = 40;
      }

    RandomizedZoneStoryBase var2 = nullptr;

      for (int var3 = 0; var3 < IsoWorld.instance.getRandomizedZoneList().size(); var3++) {
    RandomizedZoneStoryBase var4 = (RandomizedZoneStoryBase)IsoWorld.instance.getRandomizedZoneList().get(var3);
         if (var4.alwaysDo && var4.isValid(var0, false) && var4.isTimeValid(false)) {
            var2 = var4;
         }
      }

      if (var2 != nullptr) {
    int var9 = var0.x;
    int var11 = var0.y;
    int var12 = var0.x + var0.w - var2.minZoneWidth / 2;
    int var13 = var0.y + var0.h - var2.minZoneHeight / 2;
         var0.pickedXForZoneStory = Rand.Next(var9, var12 + 1);
         var0.pickedYForZoneStory = Rand.Next(var11, var13 + 1);
         var0.pickedRZStory = var2;
    return true;
      } else if (Rand.Next(100) < var1) {
         initAllRZSMapChance(var0);
         var2 = getRandomStory();
         if (var2 == nullptr) {
    return false;
         } else {
    int var8 = var0.x;
    int var10 = var0.y;
    int var5 = var0.x + var0.w - var2.minZoneWidth / 2;
    int var6 = var0.y + var0.h - var2.minZoneHeight / 2;
            var0.pickedXForZoneStory = Rand.Next(var8, var5 + 1);
            var0.pickedYForZoneStory = Rand.Next(var10, var6 + 1);
            var0.pickedRZStory = var2;
    return true;
         }
      } else {
    return false;
      }
   }

    IsoGridSquare getRandomFreeSquare(RandomizedZoneStoryBase var1, Zone var2) {
    IsoGridSquare var3 = nullptr;

      for (int var4 = 0; var4 < 1000; var4++) {
    int var5 = Rand.Next(var2.pickedXForZoneStory - var1.minZoneWidth / 2, var2.pickedXForZoneStory + var1.minZoneWidth / 2);
    int var6 = Rand.Next(var2.pickedYForZoneStory - var1.minZoneHeight / 2, var2.pickedYForZoneStory + var1.minZoneHeight / 2);
         var3 = this.getSq(var5, var6, var2.z);
         if (var3 != nullptr && var3.isFree(false)) {
    return var3;
         }
      }

    return nullptr;
   }

    IsoGridSquare getRandomFreeSquareFullZone(RandomizedZoneStoryBase var1, Zone var2) {
    IsoGridSquare var3 = nullptr;

      for (int var4 = 0; var4 < 1000; var4++) {
    int var5 = Rand.Next(var2.x, var2.x + var2.w);
    int var6 = Rand.Next(var2.y, var2.y + var2.h);
         var3 = this.getSq(var5, var6, var2.z);
         if (var3 != nullptr && var3.isFree(false)) {
    return var3;
         }
      }

    return nullptr;
   }

    static RandomizedZoneStoryBase getRandomStory() {
    int var0 = Rand.Next(totalChance);
    Iterator var1 = rzsMap.keySet().iterator();
    int var2 = 0;

      while (var1.hasNext()) {
    RandomizedZoneStoryBase var3 = (RandomizedZoneStoryBase)var1.next();
         var2 += rzsMap.get(var3);
         if (var0 < var2) {
    return var3;
         }
      }

    return nullptr;
   }

    static bool checkCanSpawnStory(Zone var0, bool var1) {
    int var2 = var0.pickedXForZoneStory - var0.pickedRZStory.minZoneWidth / 2 - 2;
    int var3 = var0.pickedYForZoneStory - var0.pickedRZStory.minZoneHeight / 2 - 2;
    int var4 = var0.pickedXForZoneStory + var0.pickedRZStory.minZoneWidth / 2 + 2;
    int var5 = var0.pickedYForZoneStory + var0.pickedRZStory.minZoneHeight / 2 + 2;
    int var6 = var2 / 10;
    int var7 = var3 / 10;
    int var8 = var4 / 10;
    int var9 = var5 / 10;

      for (int var10 = var7; var10 <= var9; var10++) {
         for (int var11 = var6; var11 <= var8; var11++) {
    IsoChunk var12 = GameServer.bServer ? ServerMap.instance.getChunk(var11, var10) : IsoWorld.instance.CurrentCell.getChunk(var11, var10);
            if (var12 == nullptr || !var12.bLoaded) {
    return false;
            }
         }
      }

    return true;
   }

    void randomizeZoneStory(Zone var1) {
   }

    bool isValid() {
    return true;
   }

    void cleanAreaForStory(RandomizedZoneStoryBase var1, Zone var2) {
    int var3 = var2.pickedXForZoneStory - var1.minZoneWidth / 2 - 1;
    int var4 = var2.pickedYForZoneStory - var1.minZoneHeight / 2 - 1;
    int var5 = var2.pickedXForZoneStory + var1.minZoneWidth / 2 + 1;
    int var6 = var2.pickedYForZoneStory + var1.minZoneHeight / 2 + 1;

      for (int var7 = var3; var7 < var5; var7++) {
         for (int var8 = var4; var8 < var6; var8++) {
    IsoGridSquare var9 = IsoWorld.instance.getCell().getGridSquare(var7, var8, var2.z);
            if (var9 != nullptr) {
               var9.removeBlood(false, false);

               for (int var10 = var9.getObjects().size() - 1; var10 >= 0; var10--) {
    IsoObject var11 = (IsoObject)var9.getObjects().get(var10);
                  if (var9.getFloor() != var11) {
                     var9.RemoveTileObject(var11);
                  }
               }

               for (int var12 = var9.getSpecialObjects().size() - 1; var12 >= 0; var12--) {
    IsoObject var14 = (IsoObject)var9.getSpecialObjects().get(var12);
                  var9.RemoveTileObject(var14);
               }

               for (int var13 = var9.getStaticMovingObjects().size() - 1; var13 >= 0; var13--) {
    IsoDeadBody var15 = (IsoDeadBody)Type.tryCastTo((IsoMovingObject)var9.getStaticMovingObjects().get(var13), IsoDeadBody.class);
                  if (var15 != nullptr) {
                     var9.removeCorpse(var15, false);
                  }
               }

               var9.RecalcProperties();
               var9.RecalcAllWithNeighbours(true);
            }
         }
      }
   }

    int getMinimumWidth() {
      return this.minZoneWidth;
   }

    int getMinimumHeight() {
      return this.minZoneHeight;
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
