#pragma once
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Create a dead survivor in the kitchen with empty bleach bottle around him
 */
class RDSBleach : public RandomizedDeadSurvivorBase {
public:
public
 RDSBleach() {
 this->name = "Suicide by Bleach";
 this->setChance(10);
 this->setMinimumDays(60);
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef = this->getLivingRoomOrKitchen(def);
 IsoDeadBody deadBody =
 RandomizedDeadSurvivorBase.createRandomDeadBody(roomDef, 0);
 if (deadBody != nullptr) {
 int int0 = Rand.Next(1, 3);

 for (int int1 = 0; int1 < int0; int1++) {
 InventoryItem item =
 InventoryItemFactory.CreateItem("Base.BleachEmpty");
 deadBody.getSquare().AddWorldInventoryItem(item, Rand.Next(0.5F, 1.0F),
 Rand.Next(0.5F, 1.0F), 0.0F);
 }

 deadBody.setPrimaryHandItem(
 InventoryItemFactory.CreateItem("Base.BleachEmpty"));
 def.bAlarmed = false;
 }
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
