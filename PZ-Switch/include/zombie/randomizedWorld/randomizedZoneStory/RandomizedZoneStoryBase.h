#pragma once
#include "zombie/SandboxOptions.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/randomizedWorld/RandomizedWorldBase.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <iterator>
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

class RandomizedZoneStoryBase : public RandomizedWorldBase {
public:
 bool alwaysDo = false;
 static const int baseChance = 15;
 static int totalChance = 0;
 static const std::string zoneStory = "ZoneStory";
 int chance = 0;
 int minZoneWidth = 0;
 int minZoneHeight = 0;
public
 ArrayList<String> zoneType = std::make_unique<ArrayList<>>();
private
 static HashMap<RandomizedZoneStoryBase, Integer> rzsMap =
 std::make_unique<HashMap<>>();

 static bool isValidForStory(IsoMetaGrid.Zone zone, bool force) {
 if (zone.pickedXForZoneStory > 0 && zone.pickedYForZoneStory > 0 &&
 zone.pickedRZStory != nullptr && checkCanSpawnStory(zone, force) {
 zone.pickedRZStory.randomizeZoneStory(zone);
 zone.pickedRZStory = nullptr;
 zone.pickedXForZoneStory = 0;
 zone.pickedYForZoneStory = 0;
 }

 if (!force && zone.hourLastSeen != 0) {
 return false;
 } else if (!force && zone.haveConstruction) {
 return false;
 } else if ("ZoneStory" == zone.type) {
 doRandomStory(zone);
 return true;
 }
 else {
 return false;
 }
 }

 static void initAllRZSMapChance(IsoMetaGrid.Zone zone) {
 totalChance = 0;
 rzsMap.clear();

 for (int int0 = 0; int0 < IsoWorld.instance.getRandomizedZoneList().size();
 int0++) {
 RandomizedZoneStoryBase randomizedZoneStoryBase =
 IsoWorld.instance.getRandomizedZoneList().get(int0);
 if (randomizedZoneStoryBase.isValid(zone, false) &&
 randomizedZoneStoryBase.isTimeValid(false) {
 totalChance = totalChance + randomizedZoneStoryBase.chance;
 rzsMap.put(randomizedZoneStoryBase, randomizedZoneStoryBase.chance);
 }
 }
 }

 bool isValid(IsoMetaGrid.Zone zone, bool force) {
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->zoneType.size(); int0++) {
 if (this->zoneType.get(int0) == zone.name) {
 boolean0 = true;
 break;
 }
 }

 return boolean0 && zone.w >= this->minZoneWidth &&
 zone.h >= this->minZoneHeight;
 }

 static bool doRandomStory(IsoMetaGrid.Zone zone) {
 zone.hourLastSeen++;
 uint8_t byte0 = 6;
 switch (SandboxOptions.instance.ZoneStoryChance.getValue()) {
 case 1:
 return false;
 case 2:
 byte0 = 2;
 case 3:
 default:
 break;
 case 4:
 byte0 = 12;
 break;
 case 5:
 byte0 = 20;
 break;
 case 6:
 byte0 = 40;
 }

 RandomizedZoneStoryBase randomizedZoneStoryBase0 = nullptr;

 for (int int0 = 0; int0 < IsoWorld.instance.getRandomizedZoneList().size();
 int0++) {
 RandomizedZoneStoryBase randomizedZoneStoryBase1 =
 IsoWorld.instance.getRandomizedZoneList().get(int0);
 if (randomizedZoneStoryBase1.alwaysDo &&
 randomizedZoneStoryBase1.isValid(zone, false) &&
 randomizedZoneStoryBase1.isTimeValid(false) {
 randomizedZoneStoryBase0 = randomizedZoneStoryBase1;
 }
 }

 if (randomizedZoneStoryBase0 != nullptr) {
 int int1 = zone.x;
 int int2 = zone.y;
 int int3 = zone.x + zone.w - randomizedZoneStoryBase0.minZoneWidth / 2;
 int int4 = zone.y + zone.h - randomizedZoneStoryBase0.minZoneHeight / 2;
 zone.pickedXForZoneStory = Rand.Next(int1, int3 + 1);
 zone.pickedYForZoneStory = Rand.Next(int2, int4 + 1);
 zone.pickedRZStory = randomizedZoneStoryBase0;
 return true;
 } else if (Rand.Next(100) < byte0) {
 initAllRZSMapChance(zone);
 randomizedZoneStoryBase0 = getRandomStory();
 if (randomizedZoneStoryBase0.empty()) {
 return false;
 } else {
 int int5 = zone.x;
 int int6 = zone.y;
 int int7 = zone.x + zone.w - randomizedZoneStoryBase0.minZoneWidth / 2;
 int int8 = zone.y + zone.h - randomizedZoneStoryBase0.minZoneHeight / 2;
 zone.pickedXForZoneStory = Rand.Next(int5, int7 + 1);
 zone.pickedYForZoneStory = Rand.Next(int6, int8 + 1);
 zone.pickedRZStory = randomizedZoneStoryBase0;
 return true;
 }
 } else {
 return false;
 }
 }

 /**
 * Get a random free square in our story zone
 */
 IsoGridSquare getRandomFreeSquare(RandomizedZoneStoryBase rzs,
 IsoMetaGrid.Zone zone) {
 IsoGridSquare square = nullptr;

 for (int int0 = 0; int0 < 1000; int0++) {
 int int1 = Rand.Next(zone.pickedXForZoneStory - rzs.minZoneWidth / 2,
 zone.pickedXForZoneStory + rzs.minZoneWidth / 2);
 int int2 = Rand.Next(zone.pickedYForZoneStory - rzs.minZoneHeight / 2,
 zone.pickedYForZoneStory + rzs.minZoneHeight / 2);
 square = this->getSq(int1, int2, zone.z);
 if (square != nullptr && square.isFree(false) {
 return square;
 }
 }

 return nullptr;
 }

 IsoGridSquare getRandomFreeSquareFullZone(RandomizedZoneStoryBase rzs,
 IsoMetaGrid.Zone zone) {
 IsoGridSquare square = nullptr;

 for (int int0 = 0; int0 < 1000; int0++) {
 int int1 = Rand.Next(zone.x, zone.x + zone.w);
 int int2 = Rand.Next(zone.y, zone.y + zone.h);
 square = this->getSq(int1, int2, zone.z);
 if (square != nullptr && square.isFree(false) {
 return square;
 }
 }

 return nullptr;
 }

 static RandomizedZoneStoryBase getRandomStory() {
 int int0 = Rand.Next(totalChance);
 Iterator iterator = rzsMap.keySet().iterator();
 int int1 = 0;

 while (iterator.hasNext()) {
 RandomizedZoneStoryBase randomizedZoneStoryBase =
 (RandomizedZoneStoryBase)iterator.next();
 int1 += rzsMap.get(randomizedZoneStoryBase);
 if (int0 < int1) {
 return randomizedZoneStoryBase;
 }
 }

 return nullptr;
 }

 static bool checkCanSpawnStory(IsoMetaGrid.Zone zone, bool var1) {
 int int0 =
 zone.pickedXForZoneStory - zone.pickedRZStory.minZoneWidth / 2 - 2;
 int int1 =
 zone.pickedYForZoneStory - zone.pickedRZStory.minZoneHeight / 2 - 2;
 int int2 =
 zone.pickedXForZoneStory + zone.pickedRZStory.minZoneWidth / 2 + 2;
 int int3 =
 zone.pickedYForZoneStory + zone.pickedRZStory.minZoneHeight / 2 + 2;
 int int4 = int0 / 10;
 int int5 = int1 / 10;
 int int6 = int2 / 10;
 int int7 = int3 / 10;

 for (int int8 = int5; int8 <= int7; int8++) {
 for (int int9 = int4; int9 <= int6; int9++) {
 IsoChunk chunk =
 GameServer.bServer
 ? ServerMap.instance.getChunk(int9, int8)
 : IsoWorld.instance.CurrentCell.getChunk(int9, int8);
 if (chunk.empty() || !chunk.bLoaded) {
 return false;
 }
 }
 }

 return true;
 }

 void randomizeZoneStory(IsoMetaGrid.Zone zone) {}

 bool isValid() { return true; }

 void cleanAreaForStory(RandomizedZoneStoryBase rzs, IsoMetaGrid.Zone zone) {
 int int0 = zone.pickedXForZoneStory - rzs.minZoneWidth / 2 - 1;
 int int1 = zone.pickedYForZoneStory - rzs.minZoneHeight / 2 - 1;
 int int2 = zone.pickedXForZoneStory + rzs.minZoneWidth / 2 + 1;
 int int3 = zone.pickedYForZoneStory + rzs.minZoneHeight / 2 + 1;

 for (int int4 = int0; int4 < int2; int4++) {
 for (int int5 = int1; int5 < int3; int5++) {
 IsoGridSquare square =
 IsoWorld.instance.getCell().getGridSquare(int4, int5, zone.z);
 if (square != nullptr) {
 square.removeBlood(false, false);

 for (int int6 = square.getObjects().size() - 1; int6 >= 0; int6--) {
 IsoObject object0 = square.getObjects().get(int6);
 if (square.getFloor() != object0) {
 square.RemoveTileObject(object0);
 }
 }

 for (int int7 = square.getSpecialObjects().size() - 1; int7 >= 0;
 int7--) {
 IsoObject object1 = square.getSpecialObjects().get(int7);
 square.RemoveTileObject(object1);
 }

 for (int int8 = square.getStaticMovingObjects().size() - 1; int8 >= 0;
 int8--) {
 IsoDeadBody deadBody = Type.tryCastTo(
 square.getStaticMovingObjects().get(int8), IsoDeadBody.class);
 if (deadBody != nullptr) {
 square.removeCorpse(deadBody, false);
 }
 }

 square.RecalcProperties();
 square.RecalcAllWithNeighbours(true);
 }
 }
 }
 }

 int getMinimumWidth() { return this->minZoneWidth; }

 int getMinimumHeight() { return this->minZoneHeight; }

public
 static enum ZoneType {
 Forest, Beach, Lake, Baseball, MusicFestStage, MusicFest, NewsStory;
 }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
