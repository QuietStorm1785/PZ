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
#include "zombie/iso/RoomDef.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSPokerNight : public RandomizedDeadSurvivorBase {
public:
   private const std::vector<std::string> items = std::make_unique<std::vector<>>();
    std::string money = nullptr;
    std::string card = nullptr;

    public RDSPokerNight() {
      this.name = "Poker Night";
      this.setChance(4);
      this.setMaximumDays(60);
      this.items.push_back("Base.Cigarettes");
      this.items.push_back("Base.WhiskeyFull");
      this.items.push_back("Base.Wine");
      this.items.push_back("Base.Wine2");
      this.items.push_back("Base.Crisps");
      this.items.push_back("Base.Crisps2");
      this.items.push_back("Base.Crisps3");
      this.items.push_back("Base.Pop");
      this.items.push_back("Base.Pop2");
      this.items.push_back("Base.Pop3");
      this.money = "Base.Money";
      this.card = "Base.CardDeck";
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

         if (this.getRoom(var1, "kitchen") != nullptr) {
    return true;
         } else {
            this.debugLine = "No kitchen";
    return false;
         }
      }
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getRoom(var1, "kitchen");
      this.addZombies(var1, Rand.Next(3, 5), nullptr, 10, var2);
      this.addZombies(var1, 1, "PokerDealer", 0, var2);
      this.addRandomItemsOnGround(var2, this.items, Rand.Next(3, 7));
      this.addRandomItemsOnGround(var2, this.money, Rand.Next(8, 13));
      this.addRandomItemsOnGround(var2, this.card, 1);
      var1.bAlarmed = false;
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
