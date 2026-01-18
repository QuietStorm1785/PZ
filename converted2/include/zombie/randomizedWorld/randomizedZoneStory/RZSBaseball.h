#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RZSBaseball : public RandomizedZoneStoryBase {
public:
public
  RZSBaseball() {
    this.name = "Baseball";
    this.chance = 100;
    this.zoneType.add(RandomizedZoneStoryBase.ZoneType.Baseball.toString());
    this.minZoneWidth = 20;
    this.minZoneHeight = 20;
    this.alwaysDo = true;
  }

  void randomizeZoneStory(IsoMetaGrid.Zone zone) {
    int int0 = Rand.Next(0, 3);
    int int1 = Rand.Next(0, 3);

    while (int0 == int1) {
      int1 = Rand.Next(0, 3);
    }

    std::string string0 = "BaseballPlayer_KY";
    if (int0 == 1) {
      string0 = "BaseballPlayer_Rangers";
    }

    if (int0 == 2) {
      string0 = "BaseballPlayer_Z";
    }

    std::string string1 = "BaseballPlayer_KY";
    if (int1 == 1) {
      string1 = "BaseballPlayer_Rangers";
    }

    if (int1 == 2) {
      string1 = "BaseballPlayer_Z";
    }

    for (int int2 = 0; int2 < 20; int2++) {
      if (Rand.NextBool(4)) {
        this.addItemOnGround(this.getRandomFreeSquare(this, zone),
                             "Base.BaseballBat");
      }

      if (Rand.NextBool(6)) {
        this.addItemOnGround(this.getRandomFreeSquare(this, zone),
                             "Base.Baseball");
      }
    }

    for (int int3 = 0; int3 <= 9; int3++) {
      this.addZombiesOnSquare(1, string0, 0,
                              this.getRandomFreeSquare(this, zone));
      this.addZombiesOnSquare(1, string1, 0,
                              this.getRandomFreeSquare(this, zone));
    }
  }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
