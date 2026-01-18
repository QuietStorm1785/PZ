#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * This building will be almost empty of loot, and lot of the doors/windows will be broken
 */
class RBLooted : public RandomizedBuildingBase {
public:
 void randomizeBuilding(BuildingDef def) {
 def.bAlarmed = false;
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = def.x - 1; int0 < def.x2 + 1; int0++) {
 for (int int1 = def.y - 1; int1 < def.y2 + 1; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square = cell.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
 IsoObject object = square.getObjects().get(int3);
 if (Rand.Next(100) >= 85 && object instanceof IsoDoor && ((IsoDoor)object).isExteriorDoor(nullptr) {
 ((IsoDoor)object).destroy();
 }

 if (Rand.Next(100) >= 85 && object instanceof IsoWindow) {
 ((IsoWindow)object).smashWindow(false, false);
 }

 if (object.getContainer() != nullptr && object.getContainer().getItems() != nullptr) {
 for (int int4 = 0; int4 < object.getContainer().getItems().size(); int4++) {
 if (Rand.Next(100) < 80) {
 object.getContainer().getItems().remove(int4);
 int4--;
 }
 }

 ItemPickerJava.updateOverlaySprite(object);
 object.getContainer().setExplored(true);
 }
 }
 }
 }
 }
 }

 def.setAllExplored(true);
 def.bAlarmed = false;
 }

 public RBLooted() {
 this->name = "Looted";
 this->setChance(10);
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
