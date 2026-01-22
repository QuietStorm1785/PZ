#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase/ZoneType.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {


class RZSSexyTime : public RandomizedZoneStoryBase {
public:
   private const std::vector<std::string> pantsMaleItems = std::make_unique<std::vector<>>();
   private const std::vector<std::string> pantsFemaleItems = std::make_unique<std::vector<>>();
   private const std::vector<std::string> topItems = std::make_unique<std::vector<>>();
   private const std::vector<std::string> shoesItems = std::make_unique<std::vector<>>();

    public RZSSexyTime() {
      this.name = "Sexy Time";
      this.chance = 5;
      this.minZoneHeight = 5;
      this.minZoneWidth = 5;
      this.zoneType.push_back(ZoneType.Beach);
      this.zoneType.push_back(ZoneType.Forest);
      this.zoneType.push_back(ZoneType.Lake);
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

    void randomizeZoneStory(Zone var1) {
      this.cleanAreaForStory(this, var1);
      BaseVehicle var2 = this.addVehicle(
         var1, this.getSq(var1.pickedXForZoneStory, var1.pickedYForZoneStory, var1.z), nullptr, nullptr, "Base.VanAmbulance", nullptr, nullptr, nullptr
      );
      if (var2 != nullptr) {
         var2.setAlarmed(false);
      }

    bool var3 = Rand.Next(7) == 0;
    bool var4 = Rand.Next(7) == 0;
      if (var3) {
         this.addItemsOnGround(var1, true, var2);
         this.addItemsOnGround(var1, true, var2);
      } else if (var4) {
         this.addItemsOnGround(var1, false, var2);
         this.addItemsOnGround(var1, false, var2);
      } else {
         this.addItemsOnGround(var1, true, var2);
         this.addItemsOnGround(var1, false, var2);
      }
   }

    void addItemsOnGround(Zone var1, bool var2, BaseVehicle var3) {
    uint8_t var4 = 100;
      if (!var2) {
         var4 = 0;
      }

    std::vector var5 = this.addZombiesOnVehicle(1, "Naked", int.valueOf(var4), var3);
      if (!var5.empty()) {
    IsoZombie var6 = (IsoZombie)var5.get(0);
         this.addRandomItemOnGround(var6.getSquare(), this.shoesItems);
         this.addRandomItemOnGround(var6.getSquare(), this.topItems);
         this.addRandomItemOnGround(var6.getSquare(), var2 ? this.pantsMaleItems : this.pantsFemaleItems);
      }
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
