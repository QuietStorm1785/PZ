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
class RBPizzaWhirled : public RandomizedBuildingBase {
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
 this->addWorldItem("Pizza", square, object);
 if (Rand.NextBool(3) {
 this->addWorldItem("Fork", square, object);
 }

 if (Rand.NextBool(3) {
 this->addWorldItem("ButterKnife", square, object);
 }
 }
 }
 }
 }
 }
 }
 }

 bool roomValid(IsoGridSquare sq) {
 return sq.getRoom() != nullptr && ("pizzawhirled" == sq.getRoom().getName()) || "italianrestaurant" == sq.getRoom().getName()));
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 return def.getRoom("pizzawhirled") != nullptr || def.getRoom("italianrestaurant") != nullptr || force;
 }

 public RBPizzaWhirled() {
 this->name = "Pizza Whirled Restaurant";
 this->setAlwaysDo(true);
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
