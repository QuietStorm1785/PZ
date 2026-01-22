#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase/ZoneType.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {


class RZSHunterCamp : public RandomizedZoneStoryBase {
public:
    public RZSHunterCamp() {
      this.name = "Hunter Forest Camp";
      this.chance = 5;
      this.minZoneHeight = 6;
      this.minZoneWidth = 6;
      this.zoneType.push_back(ZoneType.Forest);
   }

   public static std::vector<std::string> getForestClutter() {
    std::vector var0 = new std::vector();
      var0.push_back("Base.VarmintRifle");
      var0.push_back("Base.223Box");
      var0.push_back("Base.HuntingRifle");
      var0.push_back("Base.308Box");
      var0.push_back("Base.Shotgun");
      var0.push_back("Base.ShotgunShellsBox");
      var0.push_back("Base.DoubleBarrelShotgun");
      var0.push_back("Base.AssaultRifle");
      var0.push_back("Base.556Box");
    return var0;
   }

    void randomizeZoneStory(Zone var1) {
    int var2 = var1.pickedXForZoneStory;
    int var3 = var1.pickedYForZoneStory;
    std::vector var4 = getForestClutter();
      this.cleanAreaForStory(this, var1);
      this.addVehicle(var1, this.getSq(var1.x, var1.y, var1.z), nullptr, nullptr, "Base.OffRoad", nullptr, nullptr, "Hunter");
      this.addTileObject(var2, var3, var1.z, "camping_01_6");
    int var5 = Rand.Next(-1, 2);
    int var6 = Rand.Next(-1, 2);
      this.addTentWestEast(var2 + var5 - 2, var3 + var6, var1.z);
      if (Rand.Next(100) < 70) {
         this.addTentNorthSouth(var2 + var5, var3 + var6 - 2, var1.z);
      }

      if (Rand.Next(100) < 30) {
         this.addTentNorthSouth(var2 + var5 + 1, var3 + var6 - 2, var1.z);
      }

    int var7 = Rand.Next(2, 5);

      for (int var8 = 0; var8 < var7; var8++) {
         this.addItemOnGround(this.getRandomFreeSquare(this, var1), (std::string)var4.get(Rand.Next(var4.size())));
      }

      this.addZombiesOnSquare(Rand.Next(2, 5), "Hunter", 0, this.getRandomFreeSquare(this, var1));
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
