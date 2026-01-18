#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/vehicles/BaseVehicle.h"
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
 * 2-3 zombies Cops in the house too with a police car waiting outside.
 */
class RDSPoliceAtHouse : public RandomizedDeadSurvivorBase {
public:
public
 RDSPoliceAtHouse() {
 this->name = "Police at House";
 this->setChance(4);
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef = this->getLivingRoomOrKitchen(def);
 this->addZombies(def, Rand.Next(2, 4), nullptr, 0, roomDef);
 std::vector arrayList0 =
 this->addZombies(def, Rand.Next(1, 3), "Police", nullptr, roomDef);
 BaseVehicle vehicle =
 this->spawnCarOnNearestNav("Base.CarLightsPolice", def);
 if (vehicle != nullptr) {
 IsoGridSquare square = vehicle.getSquare().getCell().getGridSquare(
 vehicle.getSquare().x - 2, vehicle.getSquare().y - 2, 0);
 std::vector arrayList1 =
 this->addZombiesOnSquare(2, "Police", nullptr, square);
 createRandomDeadBody(roomDef, Rand.Next(7, 10);
 createRandomDeadBody(roomDef, Rand.Next(7, 10);
 if (!arrayList0.empty()) {
 arrayList0.addAll(arrayList1);
 ((IsoZombie)arrayList0.get(Rand.Next(arrayList0.size())))
 .addItemToSpawnAtDeath(vehicle.createVehicleKey());
 def.bAlarmed = false;
 }
 }
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
