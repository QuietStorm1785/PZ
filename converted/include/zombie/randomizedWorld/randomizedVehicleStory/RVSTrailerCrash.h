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


class RVSTrailerCrash : public RandomizedVehicleStoryBase {
public:
 public RVSTrailerCrash() {
 this->name = "Trailer Crash";
 this->minZoneWidth = 5;
 this->minZoneHeight = 12;
 this->setChance(3);
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
 float float1 = 0.0F;
 float float2 = -1.5F;
 vehicleStorySpawner.addElement("vehicle1", float1, float2, vector.getDirection(), 2.0F, 5.0F);
 uint8_t byte0 = 4;
 vehicleStorySpawner.addElement("trailer", float1, float2 + 2.5F + 1.0F + byte0 / 2.0F, vector.getDirection(), 2.0F, byte0);
 bool boolean0 = Rand.NextBool(2);
 vector = boolean0 ? IsoDirections.E.ToVector() : IsoDirections.W.ToVector();
 vector.rotate(Rand.Next(-float0, float0);
 float float3 = 0.0F;
 float float4 = float2 - 2.5F - 1.0F;
 vehicleStorySpawner.addElement("vehicle2", float3, float4, vector.getDirection(), 2.0F, 5.0F);
 vehicleStorySpawner.setParameter("zone", zone);
 vehicleStorySpawner.setParameter("east", boolean0);
 return true;
 }

 void spawnElement(VehicleStorySpawner spawner, VehicleStorySpawner.Element element) {
 IsoGridSquare square = element.square;
 if (square != nullptr) {
 float float0 = element.z;
 IsoMetaGrid.Zone zone = spawner.getParameter("zone", IsoMetaGrid.Zone.class);
 bool boolean0 = spawner.getParameterBoolean("east");
 std::string string0 = element.id;
 switch (string0) {
 case "vehicle1":
 BaseVehicle vehicle1 = this->addVehicle(
 zone, element.position.x, element.position.y, float0, element.direction, nullptr, "Base.PickUpVan", nullptr, nullptr
 );
 if (vehicle1 != nullptr) {
 vehicle1 = vehicle1.setSmashed("Front");
 vehicle1.setBloodIntensity("Front", 1.0F);
 std::string string2 = Rand.NextBool(2) ? "Base.Trailer" : "Base.TrailerCover";
 if (Rand.NextBool(6) {
 string2 = "Base.TrailerAdvert";
 }

 BaseVehicle vehicle2 = this->addTrailer(vehicle1, zone, square.getChunk(), nullptr, nullptr, string2);
 if (vehicle2 != nullptr && Rand.NextBool(3) {
 vehicle2.setAngles(vehicle2.getAngleX(), Rand.Next(90.0F, 110.0F), vehicle2.getAngleZ());
 }

 if (Rand.Next(10) < 4) {
 this->addZombiesOnVehicle(Rand.Next(2, 5), nullptr, nullptr, vehicle1);
 }

 spawner.setParameter("vehicle1", vehicle1);
 }
 break;
 case "vehicle2":
 BaseVehicle vehicle0 = this->addVehicle(zone, element.position.x, element.position.y, float0, element.direction, "bad", nullptr, nullptr, nullptr);
 if (vehicle0 != nullptr) {
 std::string string1 = boolean0 ? "Right" : "Left";
 vehicle0 = vehicle0.setSmashed(string1);
 vehicle0.setBloodIntensity(string1, 1.0F);
 spawner.setParameter("vehicle2", vehicle0);
 }
 }
 }
 }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
