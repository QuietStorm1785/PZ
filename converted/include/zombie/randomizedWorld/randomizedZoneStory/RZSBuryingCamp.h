#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Align some graves with possible flower, possible clutter One grave open with a zombie
 */
class RZSBuryingCamp : public RandomizedZoneStoryBase {
public:
 public RZSBuryingCamp() {
 this->name = "Burying Camp";
 this->chance = 7;
 this->minZoneHeight = 6;
 this->minZoneWidth = 6;
 this->minimumDays = 20;
 this->zoneType.add(RandomizedZoneStoryBase.ZoneType.Forest.toString());
 }

 void randomizeZoneStory(IsoMetaGrid.Zone zone) {
 this->cleanAreaForStory(this, zone);
 bool boolean0 = Rand.NextBool(2);
 int int0 = zone.x + 1;
 int int1 = zone.y + 1;
 int int2 = 0;
 int int3 = 0;
 int int4 = Rand.Next(3, 7);

 for (int int5 = 0; int5 < int4; int5++) {
 if (boolean0) {
 this->addTileObject(int0 + int5, zone.y + 2, zone.z, "location_community_cemetary_01_22");
 if (int5 == 2) {
 this->addTileObject(int0 + int5, zone.y + 3, zone.z, "location_community_cemetary_01_35");
 this->addTileObject(int0 + int5, zone.y + 4, zone.z, "location_community_cemetary_01_34");
 int2 = int0 + int5;
 int3 = zone.y + 5;
 } else {
 this->addTileObject(int0 + int5, zone.y + 3, zone.z, "location_community_cemetary_01_43");
 this->addTileObject(int0 + int5, zone.y + 4, zone.z, "location_community_cemetary_01_42");
 if (Rand.NextBool(2) {
 this->addTileObject(int0 + int5, zone.y + 6, zone.z, "vegetation_ornamental_01_" + Rand.Next(16, 19);
 }
 }
 } else {
 this->addTileObject(zone.x + 2, int1 + int5, zone.z, "location_community_cemetary_01_23");
 if (int5 == 2) {
 this->addTileObject(zone.x + 3, int1 + int5, zone.z, "location_community_cemetary_01_32");
 this->addTileObject(zone.x + 4, int1 + int5, zone.z, "location_community_cemetary_01_33");
 int2 = zone.x + 5;
 int3 = int1 + int5;
 } else {
 this->addTileObject(zone.x + 3, int1 + int5, zone.z, "location_community_cemetary_01_40");
 this->addTileObject(zone.x + 4, int1 + int5, zone.z, "location_community_cemetary_01_41");
 if (Rand.NextBool(2) {
 this->addTileObject(zone.x + 6, int1 + int5, zone.z, "vegetation_ornamental_01_" + Rand.Next(16, 19);
 }
 }
 }
 }

 this->addItemOnGround(this->getSq(int2 + 1, int3 + 1, zone.z), "Base.Shovel");
 std::vector arrayList = this->addZombiesOnSquare(1, nullptr, nullptr, this->getRandomFreeSquare(this, zone);
 if (arrayList != nullptr && !arrayList.empty()) {
 IsoZombie zombie0 = (IsoZombie)arrayList.get(0);
 IsoDeadBody deadBody = createRandomDeadBody(this->getSq(int2, int3, zone.z), nullptr, Rand.Next(7, 12), 0, nullptr);
 if (deadBody != nullptr) {
 this->addBloodSplat(deadBody.getSquare(), 10);
 zombie0.faceLocationF(deadBody.x, deadBody.y);
 zombie0.setX(deadBody.x + 1.0F);
 zombie0.setY(deadBody.y);
 zombie0.setEatBodyTarget(deadBody, true);
 }
 }

 this->addItemOnGround(this->getRandomFreeSquare(this, zone), "Base.WhiskeyEmpty");
 this->addItemOnGround(this->getRandomFreeSquare(this, zone), "Base.WineEmpty");
 }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
