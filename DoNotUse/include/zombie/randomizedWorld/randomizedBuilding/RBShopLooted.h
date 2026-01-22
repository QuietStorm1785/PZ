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

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBShopLooted : public RandomizedBuildingBase {
public:
   private const std::vector<std::string> buildingList = std::make_unique<std::vector<>>();

    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
      var1.setAllExplored(true);
    RoomDef var2 = nullptr;

      for (int var3 = 0; var3 < var1.rooms.size(); var3++) {
    RoomDef var4 = (RoomDef)var1.rooms.get(var3);
         if (this.buildingList.contains(var4.name)) {
            var2 = var4;
            break;
         }
      }

      if (var2 != nullptr) {
    int var7 = Rand.Next(3, 8);

         for (int var8 = 0; var8 < var7; var8++) {
            this.addZombiesOnSquare(1, "Bandit", nullptr, var2.getFreeSquare());
         }

         this.addZombiesOnSquare(2, "Police", nullptr, var2.getFreeSquare());
    int var9 = Rand.Next(3, 8);

         for (int var5 = 0; var5 < var9; var5++) {
    IsoGridSquare var6 = getRandomSquareForCorpse(var2);
            createRandomDeadBody(var6, nullptr, Rand.Next(5, 10), 5, nullptr);
         }
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      this.debugLine = "";
      if (GameClient.bClient) {
    return false;
      } else if (!this.isTimeValid(var2)) {
    return false;
      } else if (var1.isAllExplored() && !var2) {
    return false;
      } else {
         if (!var2) {
            if (Rand.Next(100) > this.getChance()) {
    return false;
            }

            for (int var3 = 0; var3 < GameServer.Players.size(); var3++) {
    IsoPlayer var4 = (IsoPlayer)GameServer.Players.get(var3);
               if (var4.getSquare() != nullptr && var4.getSquare().getBuilding() != nullptr && var4.getSquare().getBuilding().def == var1) {
    return false;
               }
            }
         }

         for (int var5 = 0; var5 < var1.rooms.size(); var5++) {
    RoomDef var6 = (RoomDef)var1.rooms.get(var5);
            if (this.buildingList.contains(var6.name)) {
    return true;
            }
         }

         this.debugLine = this.debugLine + "not a shop";
    return false;
      }
   }

    public RBShopLooted() {
      this.name = "Looted Shop";
      this.setChance(2);
      this.setAlwaysDo(true);
      this.setMaximumDays(30);
      this.buildingList.push_back("conveniencestore");
      this.buildingList.push_back("warehouse");
      this.buildingList.push_back("medclinic");
      this.buildingList.push_back("grocery");
      this.buildingList.push_back("zippeestore");
      this.buildingList.push_back("gigamart");
      this.buildingList.push_back("fossoil");
      this.buildingList.push_back("spiffo_dining");
      this.buildingList.push_back("pizzawhirled");
      this.buildingList.push_back("bookstore");
      this.buildingList.push_back("grocers");
      this.buildingList.push_back("library");
      this.buildingList.push_back("toolstore");
      this.buildingList.push_back("bar");
      this.buildingList.push_back("pharmacy");
      this.buildingList.push_back("gunstore");
      this.buildingList.push_back("mechanic");
      this.buildingList.push_back("bakery");
      this.buildingList.push_back("aesthetic");
      this.buildingList.push_back("clothesstore");
      this.buildingList.push_back("restaurant");
      this.buildingList.push_back("poststorage");
      this.buildingList.push_back("generalstore");
      this.buildingList.push_back("furniturestore");
      this.buildingList.push_back("fishingstorage");
      this.buildingList.push_back("cornerstore");
      this.buildingList.push_back("housewarestore");
      this.buildingList.push_back("shoestore");
      this.buildingList.push_back("sportstore");
      this.buildingList.push_back("giftstore");
      this.buildingList.push_back("candystore");
      this.buildingList.push_back("toystore");
      this.buildingList.push_back("electronicsstore");
      this.buildingList.push_back("sewingstore");
      this.buildingList.push_back("medical");
      this.buildingList.push_back("medicaloffice");
      this.buildingList.push_back("jewelrystore");
      this.buildingList.push_back("musicstore");
      this.buildingList.push_back("departmentstore");
      this.buildingList.push_back("gasstore");
      this.buildingList.push_back("gardenstore");
      this.buildingList.push_back("farmstorage");
      this.buildingList.push_back("hunting");
      this.buildingList.push_back("camping");
      this.buildingList.push_back("butcher");
      this.buildingList.push_back("optometrist");
      this.buildingList.push_back("knoxbutcher");
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
