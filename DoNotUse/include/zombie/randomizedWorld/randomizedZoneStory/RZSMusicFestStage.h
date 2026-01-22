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


class RZSMusicFestStage : public RandomizedZoneStoryBase {
public:
    public RZSMusicFestStage() {
      this.name = "Music Festival Stage";
      this.chance = 100;
      this.zoneType.push_back(ZoneType.MusicFestStage);
      this.alwaysDo = true;
   }

    void randomizeZoneStory(Zone var1) {
      for (int var2 = 0; var2 < 2; var2++) {
    int var3 = Rand.Next(0, 4);
         switch (var3) {
            case 0:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.GuitarAcoustic");
               break;
            case 1:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.GuitarElectricBlack");
               break;
            case 2:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.GuitarElectricBlue");
               break;
            case 3:
               this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.GuitarElectricRed");
         }
      }

    int var4 = Rand.Next(0, 3);
      switch (var4) {
         case 0:
            this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.GuitarElectricBassBlack");
            break;
         case 1:
            this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.GuitarElectricBassBlue");
            break;
         case 2:
            this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.GuitarElectricBassRed");
      }

      if (Rand.NextBool(6)) {
         this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.Keytar");
      }

      this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.Speaker");
      this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.Speaker");
      this.addItemOnGround(this.getRandomFreeSquareFullZone(this, var1), "Base.Drumstick");
      this.addZombiesOnSquare(1, "Punk", 0, this.getRandomFreeSquareFullZone(this, var1));
      this.addZombiesOnSquare(1, "Punk", 0, this.getRandomFreeSquareFullZone(this, var1));
      this.addZombiesOnSquare(1, "Punk", 0, this.getRandomFreeSquareFullZone(this, var1));
      this.addZombiesOnSquare(1, "Punk", 0, this.getRandomFreeSquareFullZone(this, var1));
      this.addZombiesOnSquare(1, "Punk", 100, this.getRandomFreeSquareFullZone(this, var1));
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
