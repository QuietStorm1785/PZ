#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase/ZoneType.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {


class RZSTrapperCamp : public RandomizedZoneStoryBase {
public:
    public RZSTrapperCamp() {
      this.name = "Trappers Forest Camp";
      this.chance = 7;
      this.minZoneHeight = 6;
      this.minZoneWidth = 6;
      this.zoneType.push_back(ZoneType.Forest);
   }

   public static std::vector<std::string> getTrapList() {
    std::vector var0 = new std::vector();
      var0.push_back("constructedobjects_01_3");
      var0.push_back("constructedobjects_01_4");
      var0.push_back("constructedobjects_01_7");
      var0.push_back("constructedobjects_01_8");
      var0.push_back("constructedobjects_01_11");
      var0.push_back("constructedobjects_01_13");
      var0.push_back("constructedobjects_01_16");
    return var0;
   }

    void randomizeZoneStory(Zone var1) {
    int var2 = var1.pickedXForZoneStory;
    int var3 = var1.pickedYForZoneStory;
    std::vector var4 = getTrapList();
      this.cleanAreaForStory(this, var1);
      this.addTileObject(var2, var3, var1.z, "camping_01_6");
    int var5 = Rand.Next(-1, 2);
    int var6 = Rand.Next(-1, 2);
      this.addTentWestEast(var2 + var5 - 2, var3 + var6, var1.z);
      if (Rand.Next(100) < 70) {
         this.addTentNorthSouth(var2 + var5, var3 + var6 - 2, var1.z);
      }

    int var7 = Rand.Next(2, 5);

      for (int var8 = 0; var8 < var7; var8++) {
    IsoGridSquare var9 = this.getRandomFreeSquare(this, var1);
         this.addTileObject(var9, (std::string)var4.get(Rand.Next(var4.size())));
      }

      this.addZombiesOnSquare(Rand.Next(2, 5), "Hunter", 0, this.getRandomFreeSquare(this, var1));
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
