#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RZSMusicFest : public RandomizedZoneStoryBase {
public:
 public RZSMusicFest() {
 this->name = "Music Festival";
 this->chance = 100;
 this->zoneType.add(RandomizedZoneStoryBase.ZoneType.MusicFest.toString());
 this->alwaysDo = true;
 }

 void randomizeZoneStory(IsoMetaGrid.Zone zone) {
 int int0 = Rand.Next(20, 50);

 for (int int1 = 0; int1 < int0; int1++) {
 int int2 = Rand.Next(0, 4);
 switch (int2) {
 case 0:
 this->addItemOnGround(this->getRandomFreeSquareFullZone(this, zone), "Base.BeerCan");
 break;
 case 1:
 this->addItemOnGround(this->getRandomFreeSquareFullZone(this, zone), "Base.BeerBottle");
 break;
 case 2:
 this->addItemOnGround(this->getRandomFreeSquareFullZone(this, zone), "Base.BeerCanEmpty");
 break;
 case 3:
 this->addItemOnGround(this->getRandomFreeSquareFullZone(this, zone), "Base.BeerEmpty");
 }
 }
 }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
