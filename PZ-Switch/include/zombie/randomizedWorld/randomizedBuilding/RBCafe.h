#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Add some food on table
 */
class RBCafe : public RandomizedBuildingBase {
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
 if (Rand.NextBool(2) && this->isTableFor3DItems(object, square) {
 if (Rand.NextBool(2) {
 int int4 = Rand.Next(3);
 switch (int4) {
 case 0:
 this->addWorldItem("Mugl", square, object);
 break;
 case 1:
 this->addWorldItem("MugWhite", square, object);
 break;
 case 2:
 this->addWorldItem("MugRed", square, object);
 }
 }

 if (Rand.NextBool(4) {
 this->addWorldItem("Cupcake", square, object);
 }

 if (Rand.NextBool(4) {
 this->addWorldItem("CookieJelly", square, object);
 }

 if (Rand.NextBool(4) {
 this->addWorldItem("CookieChocolateChip", square, object);
 }

 if (Rand.NextBool(4) {
 this->addWorldItem("Kettle", square, object);
 }

 if (Rand.NextBool(3) {
 this->addWorldItem("Sugar", square, object);
 }

 if (Rand.NextBool(2) {
 this->addWorldItem("Teabag2", square, object);
 }
 }
 }
 }
 }
 }
 }
 }

 bool roomValid(IsoGridSquare sq) {
 return sq.getRoom() != nullptr && "cafe" == sq.getRoom().getName());
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 return def.getRoom("cafe") != nullptr || force;
 }

public
 RBCafe() {
 this->name = "Cafe (Seahorse..)";
 this->setAlwaysDo(true);
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
