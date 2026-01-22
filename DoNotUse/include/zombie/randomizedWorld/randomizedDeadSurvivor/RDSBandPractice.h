#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSBandPractice : public RandomizedDeadSurvivorBase {
public:
   private const std::vector<std::string> instrumentsList = std::make_unique<std::vector<>>();

    public RDSBandPractice() {
      this.name = "Band Practice";
      this.setChance(10);
      this.setMaximumDays(60);
      this.instrumentsList.push_back("GuitarAcoustic");
      this.instrumentsList.push_back("GuitarElectricBlack");
      this.instrumentsList.push_back("GuitarElectricBlue");
      this.instrumentsList.push_back("GuitarElectricRed");
      this.instrumentsList.push_back("GuitarElectricBassBlue");
      this.instrumentsList.push_back("GuitarElectricBassBlack");
      this.instrumentsList.push_back("GuitarElectricBassRed");
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
      this.spawnItemsInContainers(var1, "BandPractice", 90);
    RoomDef var2 = this.getRoom(var1, "garagestorage");
      if (var2 == nullptr) {
         var2 = this.getRoom(var1, "shed");
      }

      if (var2 == nullptr) {
         var2 = this.getRoom(var1, "garage");
      }

      this.addZombies(var1, Rand.Next(2, 4), "Rocker", 20, var2);
    IsoGridSquare var3 = getRandomSpawnSquare(var2);
      if (var3 != nullptr) {
         var3.AddWorldInventoryItem((std::string)PZArrayUtil.pickRandom(this.instrumentsList), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         if (Rand.Next(4) == 0) {
            var3.AddWorldInventoryItem((std::string)PZArrayUtil.pickRandom(this.instrumentsList), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (Rand.Next(4) == 0) {
            var3.AddWorldInventoryItem((std::string)PZArrayUtil.pickRandom(this.instrumentsList), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         var1.bAlarmed = false;
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      this.debugLine = "";
      if (GameClient.bClient) {
    return false;
      } else if (var1.isAllExplored() && !var2) {
    return false;
      } else {
         if (!var2) {
            for (int var3 = 0; var3 < GameServer.Players.size(); var3++) {
    IsoPlayer var4 = (IsoPlayer)GameServer.Players.get(var3);
               if (var4.getSquare() != nullptr && var4.getSquare().getBuilding() != nullptr && var4.getSquare().getBuilding().def == var1) {
    return false;
               }
            }
         }

    bool var6 = false;

         for (int var7 = 0; var7 < var1.rooms.size(); var7++) {
    RoomDef var5 = (RoomDef)var1.rooms.get(var7);
            if (("garagestorage" == var5.name) || "shed" == var5.name) || "garage" == var5.name)) && var5.area >= 9) {
               var6 = true;
               break;
            }
         }

         if (!var6) {
            this.debugLine = "No shed/garage or is too small";
         }

    return var6;
      }
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
