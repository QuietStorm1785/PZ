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
 * Create a dead survivor with alcohol bottles around him
 */
class RDSDeadDrunk : public RandomizedDeadSurvivorBase {
public:
 ArrayList<String> alcoholList = std::make_unique<ArrayList<>>();

public
 RDSDeadDrunk() {
 this->name = "Dead Drunk";
 this->setChance(10);
 this->alcoholList.add("Base.WhiskeyFull");
 this->alcoholList.add("Base.WhiskeyEmpty");
 this->alcoholList.add("Base.Wine");
 this->alcoholList.add("Base.WineEmpty");
 this->alcoholList.add("Base.Wine2");
 this->alcoholList.add("Base.WineEmpty2");
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef = this->getLivingRoomOrKitchen(def);
 IsoDeadBody deadBody =
 RandomizedDeadSurvivorBase.createRandomDeadBody(roomDef, 0);
 if (deadBody != nullptr) {
 int int0 = Rand.Next(2, 4);

 for (int int1 = 0; int1 < int0; int1++) {
 InventoryItem item = InventoryItemFactory.CreateItem(
 this->alcoholList.get(Rand.Next(0, this->alcoholList.size())));
 deadBody.getSquare().AddWorldInventoryItem(item, Rand.Next(0.5F, 1.0F),
 Rand.Next(0.5F, 1.0F), 0.0F);
 def.bAlarmed = false;
 }

 deadBody.setPrimaryHandItem(
 InventoryItemFactory.CreateItem("Base.WhiskeyEmpty"));
 }
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
