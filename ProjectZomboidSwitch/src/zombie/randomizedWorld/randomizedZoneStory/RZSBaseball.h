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


class RZSBaseball : public RandomizedZoneStoryBase {
public:
    public RZSBaseball() {
      this.name = "Baseball";
      this.chance = 100;
      this.zoneType.push_back(ZoneType.Baseball);
      this.minZoneWidth = 20;
      this.minZoneHeight = 20;
      this.alwaysDo = true;
   }

    void randomizeZoneStory(Zone var1) {
    int var2 = Rand.Next(0, 3);
    int var3 = Rand.Next(0, 3);

      while (var2 == var3) {
         var3 = Rand.Next(0, 3);
      }

    std::string var4 = "BaseballPlayer_KY";
      if (var2 == 1) {
         var4 = "BaseballPlayer_Rangers";
      }

      if (var2 == 2) {
         var4 = "BaseballPlayer_Z";
      }

    std::string var5 = "BaseballPlayer_KY";
      if (var3 == 1) {
         var5 = "BaseballPlayer_Rangers";
      }

      if (var3 == 2) {
         var5 = "BaseballPlayer_Z";
      }

      for (int var6 = 0; var6 < 20; var6++) {
         if (Rand.NextBool(4)) {
            this.addItemOnGround(this.getRandomFreeSquare(this, var1), "Base.BaseballBat");
         }

         if (Rand.NextBool(6)) {
            this.addItemOnGround(this.getRandomFreeSquare(this, var1), "Base.Baseball");
         }
      }

      for (int var7 = 0; var7 <= 9; var7++) {
         this.addZombiesOnSquare(1, var4, 0, this.getRandomFreeSquare(this, var1));
         this.addZombiesOnSquare(1, var5, 0, this.getRandomFreeSquare(this, var1));
      }
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
