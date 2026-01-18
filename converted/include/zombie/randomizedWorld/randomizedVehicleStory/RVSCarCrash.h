#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/Vector2.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RVSCarCrash : public RandomizedVehicleStoryBase {
public:
 public RVSCarCrash() {
 this->name = "Basic Car Crash";
 this->minZoneWidth = 5;
 this->minZoneHeight = 7;
 this->setChance(25);
 }

 void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
 this->callVehicleStorySpawner(zone, chunk, 0.0F);
 }

 bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk, bool debug) {
 VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
 vehicleStorySpawner.clear();
 float float0 = (float) (Math.PI / 6);
 if (debug) {
 float0 = 0.0F;
 }

 Vector2 vector = IsoDirections.N.ToVector();
 vector.rotate(Rand.Next(-float0, float0);
 vehicleStorySpawner.addElement("vehicle1", 0.0F, 1.0F, vector.getDirection(), 2.0F, 5.0F);
 bool boolean0 = Rand.NextBool(2);
 vector = boolean0 ? IsoDirections.E.ToVector() : IsoDirections.W.ToVector();
 vector.rotate(Rand.Next(-float0, float0);
 vehicleStorySpawner.addElement("vehicle2", 0.0F, -2.5F, vector.getDirection(), 2.0F, 5.0F);
 vehicleStorySpawner.setParameter("zone", zone);
 vehicleStorySpawner.setParameter("smashed", Rand.NextBool(3);
 vehicleStorySpawner.setParameter("east", boolean0);
 return true;
 }

 void spawnElement(VehicleStorySpawner spawner, VehicleStorySpawner.Element element) {
 IsoGridSquare square = element.square;
 if (square != nullptr) {
 float float0 = element.z;
 IsoMetaGrid.Zone zone = spawner.getParameter("zone", IsoMetaGrid.Zone.class);
 bool boolean0 = spawner.getParameterBoolean("smashed");
 bool boolean1 = spawner.getParameterBoolean("east");
 std::string string0 = element.id;
 switch (string0) {
 case "vehicle1":
 case "vehicle2":
 BaseVehicle vehicle = this->addVehicle(zone, element.position.x, element.position.y, float0, element.direction, "bad", nullptr, nullptr, nullptr);
 if (vehicle != nullptr) {
 if (boolean0) {
 std::string string1 = "Front";
 if ("vehicle2" == element.id) {
 string1 = boolean1 ? "Right" : "Left";
 }

 vehicle = vehicle.setSmashed(string1);
 vehicle.setBloodIntensity(string1, 1.0F);
 }

 if ("vehicle1" == element.id) && Rand.Next(10) < 4) {
 this->addZombiesOnVehicle(Rand.Next(2, 5), nullptr, nullptr, vehicle);
 }
 }
 }
 }
 }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
