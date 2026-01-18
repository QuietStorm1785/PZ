#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Add some food on table
 */
class RBBar : public RandomizedBuildingBase {
public:
 void randomizeBuilding(BuildingDef def) {
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = def.x - 1; int0 < def.x2 + 1; int0++) {
 for (int int1 = def.y - 1; int1 < def.y2 + 1; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square = cell.getGridSquare(int0, int1, int2);
 if (square != nullptr && this->roomValid(square) {
 for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
 IsoObject object = square.getObjects().get(int3);
 if (object.getSprite() != nullptr
 && object.getSprite().getName() != nullptr
 && (object.getSprite().getName() == "recreational_01_6") || object.getSprite().getName() == "recreational_01_7"))) {
 if (Rand.NextBool(3) {
 this->addWorldItem("PoolBall", square, object);
 }

 if (Rand.NextBool(3) {
 this->addWorldItem("Poolcue", square, object);
 }
 } else if (object.isTableSurface() && Rand.NextBool(2) {
 if (Rand.NextBool(3) {
 this->addWorldItem("Cigarettes", square, object);
 if (Rand.NextBool(2) {
 this->addWorldItem("Lighter", square, object);
 }
 }

 int int4 = Rand.Next(7);
 switch (int4) {
 case 0:
 this->addWorldItem("WhiskeyFull", square, object);
 break;
 case 1:
 this->addWorldItem("Wine", square, object);
 break;
 case 2:
 this->addWorldItem("Wine2", square, object);
 break;
 case 3:
 this->addWorldItem("BeerCan", square, object);
 break;
 case 4:
 this->addWorldItem("BeerBottle", square, object);
 }

 if (Rand.NextBool(3) {
 int int5 = Rand.Next(7);
 switch (int5) {
 case 0:
 this->addWorldItem("Crisps", square, object);
 break;
 case 1:
 this->addWorldItem("Crisps2", square, object);
 break;
 case 2:
 this->addWorldItem("Crisps3", square, object);
 break;
 case 3:
 this->addWorldItem("Crisps4", square, object);
 break;
 case 4:
 this->addWorldItem("Peanuts", square, object);
 }
 }

 if (Rand.NextBool(4) {
 this->addWorldItem("CardDeck", square, object);
 }
 }
 }

 if (Rand.NextBool(20)
 && square.getRoom() != nullptr
 && square.getRoom().getName() == "bar")
 && square.getObjects().size() == 1
 && Rand.NextBool(8) {
 this->addWorldItem("Dart", square, nullptr);
 }
 }
 }
 }
 }
 }

 bool roomValid(IsoGridSquare sq) {
 return sq.getRoom() != nullptr && "bar" == sq.getRoom().getName());
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 return def.getRoom("bar") != nullptr && def.getRoom("stripclub") == nullptr || force;
 }

 public RBBar() {
 this->name = "Bar";
 this->setAlwaysDo(true);
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
