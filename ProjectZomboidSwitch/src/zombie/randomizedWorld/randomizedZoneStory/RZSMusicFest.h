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


class RZSMusicFest : public RandomizedZoneStoryBase {
public:
    public RZSMusicFest() {
      this.name = "Music Festival";
      this.chance = 100;
      this.zoneType.push_back(ZoneType.MusicFest);
      this.alwaysDo = true;
   }

    void randomizeZoneStory(Zone var1) {
    int var2 = Rand.Next(20, 50);

      for (int var3 = 0; var3 < var2; var3++) {
    int var4 = Rand.Next(0, 4);
         switch (var4) {
            case 0:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.BeerCan");
               break;
            case 1:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.BeerBottle");
               break;
            case 2:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.BeerCanEmpty");
               break;
            case 3:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.BeerEmpty");
         }
      }
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
