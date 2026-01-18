#pragma once
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoZombie.h"
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

class RVSAmbulanceCrash : public RandomizedVehicleStoryBase {
public:
public
 RVSAmbulanceCrash() {
 this->name = "Ambulance Crash";
 this->minZoneWidth = 5;
 this->minZoneHeight = 7;
 this->setChance(5);
 }

 void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
 this->callVehicleStorySpawner(zone, chunk, 0.0F);
 }

 bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk,
 bool debug) {
 VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
 vehicleStorySpawner.clear();
 float float0 = (float)(Math.PI / 6);
 if (debug) {
 float0 = 0.0F;
 }

 Vector2 vector = IsoDirections.N.ToVector();
 vector.rotate(Rand.Next(-float0, float0);
 vehicleStorySpawner.addElement("vehicle1", 0.0F, 1.0F,
 vector.getDirection(), 2.0F, 5.0F);
 bool boolean0 = Rand.NextBool(2);
 vector = boolean0 ? IsoDirections.E.ToVector() : IsoDirections.W.ToVector();
 vector.rotate(Rand.Next(-float0, float0);
 vehicleStorySpawner.addElement("vehicle2", 0.0F, -2.5F,
 vector.getDirection(), 2.0F, 5.0F);
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
 std::string string = element.id;
 switch (string) {
 case "vehicle1":
 BaseVehicle vehicle1 = this->addVehicle(
 zone, element.position.x, element.position.y, float0,
 element.direction, nullptr, "Base.VanAmbulance", nullptr, nullptr);
 if (vehicle1 != nullptr) {
 this->addZombiesOnVehicle(Rand.Next(1, 3), "AmbulanceDriver", nullptr,
 vehicle1);
 std::vector arrayList = this->addZombiesOnVehicle(
 Rand.Next(1, 3), "HospitalPatient", nullptr, vehicle1);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 for (int int1 = 0; int1 < 7; int1++) {
 if (Rand.NextBool(2) {
 ((IsoZombie)arrayList.get(int0)
 .addVisualBandage(BodyPartType.getRandom(), true);
 }
 }
 }
 }
 break;
 case "vehicle2":
 BaseVehicle vehicle0 =
 this->addVehicle(zone, element.position.x, element.position.y,
 float0, element.direction, "bad", nullptr, nullptr, nullptr);
 if (vehicle0.empty()) {
 }
 }
 }
 }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
