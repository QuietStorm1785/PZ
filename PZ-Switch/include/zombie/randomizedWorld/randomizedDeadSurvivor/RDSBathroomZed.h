#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
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
 * Create 1 to 2 zombies in the bathroom with some bathroom items on the ground
 */
class RDSBathroomZed : public RandomizedDeadSurvivorBase {
public:
private
 ArrayList<String> items = std::make_unique<ArrayList<>>();

public
 RDSBathroomZed() {
 this->name = "Bathroom Zed";
 this->setChance(12);
 this->items.add("Base.BathTowel");
 this->items.add("Base.Razor");
 this->items.add("Base.Lipstick");
 this->items.add("Base.Comb");
 this->items.add("Base.Hairspray");
 this->items.add("Base.Toothbrush");
 this->items.add("Base.Cologne");
 this->items.add("Base.Perfume");
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef = this->getRoom(def, "bathroom");
 int int0 = 1;
 if (roomDef.area > 6) {
 int0 = Rand.Next(1, 3);
 }

 this->addZombies(def, int0, Rand.Next(2) == 0 ? "Bathrobe" : "Naked",
 nullptr, roomDef);
 this->addRandomItemsOnGround(roomDef, this->items, Rand.Next(2, 5);
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
