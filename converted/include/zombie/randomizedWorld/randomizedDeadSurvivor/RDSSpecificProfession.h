#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Create a dead survivor in the kitchen with empty bleach bottle around him
 */
class RDSSpecificProfession : public RandomizedDeadSurvivorBase {
public:
 private ArrayList<String> specificProfessionDistribution = std::make_unique<ArrayList<>>();

 void randomizeDeadSurvivor(BuildingDef def) {
 IsoGridSquare square = def.getFreeSquareInRoom();
 if (square != nullptr) {
 IsoDeadBody deadBody = createRandomDeadBody(square.getX(), square.getY(), square.getZ(), nullptr, 0);
 if (deadBody != nullptr) {
 ItemPickerJava.ItemPickerRoom itemPickerRoom = ItemPickerJava.rooms.get(PZArrayUtil.pickRandom(this->specificProfessionDistribution);
 ItemPickerJava.rollItem(itemPickerRoom.Containers.get("counter"), deadBody.getContainer(), true, nullptr, nullptr);
 }
 }
 }

 public RDSSpecificProfession() {
 this->specificProfessionDistribution.add("Carpenter");
 this->specificProfessionDistribution.add("Electrician");
 this->specificProfessionDistribution.add("Farmer");
 this->specificProfessionDistribution.add("Nurse");
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
