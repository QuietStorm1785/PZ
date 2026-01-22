#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSStudentNight : public RandomizedDeadSurvivorBase {
public:
   private const std::vector<std::string> items = std::make_unique<std::vector<>>();
   private const std::vector<std::string> otherItems = std::make_unique<std::vector<>>();
   private const std::vector<std::string> pantsMaleItems = std::make_unique<std::vector<>>();
   private const std::vector<std::string> pantsFemaleItems = std::make_unique<std::vector<>>();
   private const std::vector<std::string> topItems = std::make_unique<std::vector<>>();
   private const std::vector<std::string> shoesItems = std::make_unique<std::vector<>>();

    public RDSStudentNight() {
      this.name = "Student Night";
      this.setChance(4);
      this.setMaximumDays(60);
      this.otherItems.push_back("Base.Cigarettes");
      this.otherItems.push_back("Base.WhiskeyFull");
      this.otherItems.push_back("Base.Wine");
      this.otherItems.push_back("Base.Wine2");
      this.items.push_back("Base.Crisps");
      this.items.push_back("Base.Crisps2");
      this.items.push_back("Base.Crisps3");
      this.items.push_back("Base.Pop");
      this.items.push_back("Base.Pop2");
      this.items.push_back("Base.Pop3");
      this.shoesItems.push_back("Base.Shoes_Random");
      this.shoesItems.push_back("Base.Shoes_TrainerTINT");
      this.pantsMaleItems.push_back("Base.TrousersMesh_DenimLight");
      this.pantsMaleItems.push_back("Base.Trousers_DefaultTEXTURE_TINT");
      this.pantsMaleItems.push_back("Base.Trousers_Denim");
      this.pantsFemaleItems.push_back("Base.Skirt_Knees");
      this.pantsFemaleItems.push_back("Base.Skirt_Long");
      this.pantsFemaleItems.push_back("Base.Skirt_Short");
      this.pantsFemaleItems.push_back("Base.Skirt_Normal");
      this.topItems.push_back("Base.Shirt_FormalWhite");
      this.topItems.push_back("Base.Shirt_FormalWhite_ShortSleeve");
      this.topItems.push_back("Base.Tshirt_DefaultTEXTURE_TINT");
      this.topItems.push_back("Base.Tshirt_PoloTINT");
      this.topItems.push_back("Base.Tshirt_WhiteLongSleeveTINT");
      this.topItems.push_back("Base.Tshirt_WhiteTINT");
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
      this.addZombies(var1, Rand.Next(2, 5), nullptr, nullptr, var2);
    RoomDef var3 = this.getRoom(var1, "bedroom");
      this.addZombies(var1, 1, "Naked", 0, var3);
      this.addItemsOnGround(var3, true);
      this.addZombies(var1, 1, "Naked", 100, var3);
      this.addItemsOnGround(var3, false);
      this.addRandomItemsOnGround(var2, this.items, Rand.Next(3, 7));
      this.addRandomItemsOnGround(var2, this.otherItems, Rand.Next(2, 6));
      var1.bAlarmed = false;
   }

    void addItemsOnGround(RoomDef var1, bool var2) {
    IsoGridSquare var3 = getRandomSpawnSquare(var1);
      this.addRandomItemOnGround(var3, this.shoesItems);
      this.addRandomItemOnGround(var3, this.topItems);
      this.addRandomItemOnGround(var3, var2 ? this.pantsMaleItems : this.pantsFemaleItems);
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
