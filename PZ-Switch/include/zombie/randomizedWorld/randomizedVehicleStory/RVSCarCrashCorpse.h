#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/Vector2.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RVSCarCrashCorpse : public RandomizedVehicleStoryBase {
public:
 /**
 * Vehicle alone, corpse not so far from the car's front with blood trail
 */
public
 RVSCarCrashCorpse() {
 this->name = "Basic Car Crash Corpse";
 this->minZoneWidth = 6;
 this->minZoneHeight = 11;
 this->setChance(10);
 }

 void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
 float float0 = (float)(Math.PI / 6);
 this->callVehicleStorySpawner(zone, chunk, Rand.Next(-float0, float0);
 }

 bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk,
 bool debug) {
 VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
 vehicleStorySpawner.clear();
 Vector2 vector = IsoDirections.N.ToVector();
 float float0 = 2.5F;
 vehicleStorySpawner.addElement("vehicle1", 0.0F, float0,
 vector.getDirection(), 2.0F, 5.0F);
 vehicleStorySpawner.addElement(
 "corpse", 0.0F, float0 - (debug ? 7 : Rand.Next(4, 7),
 vector.getDirection() + (float)Math.PI, 1.0F, 2.0F);
 vehicleStorySpawner.setParameter("zone", zone);
 return true;
 }

 void spawnElement(VehicleStorySpawner spawner,
 VehicleStorySpawner.Element element) {
 IsoGridSquare square = element.square;
 if (square != nullptr) {
 float float0 = element.z;
 IsoMetaGrid.Zone zone =
 spawner.getParameter("zone", IsoMetaGrid.Zone.class);
 BaseVehicle vehicle = spawner.getParameter("vehicle1", BaseVehicle.class);
 std::string string = element.id;
 switch (string) {
 case "corpse":
 if (vehicle != nullptr) {
 createRandomDeadBody(element.position.x, element.position.y,
 element.z, element.direction, false, 35, 30,
 nullptr);
 this->addTrailOfBlood(element.position.x, element.position.y,
 element.z, element.direction, 15);
 }
 break;
 case "vehicle1":
 vehicle = this->addVehicle(zone, element.position.x, element.position.y,
 float0, element.direction, "bad", nullptr,
 nullptr, nullptr);
 if (vehicle != nullptr) {
 vehicle = vehicle.setSmashed("Front");
 vehicle.setBloodIntensity("Front", 1.0F);
 spawner.setParameter("vehicle1", vehicle);
 }
 }
 }
 }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
