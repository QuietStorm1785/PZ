#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/Vector2.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Police barricading a road, 2 police cars, some zombies police with guns/rifle, dead corpses around
 */
class RVSPoliceBlockadeShooting : public RandomizedVehicleStoryBase {
public:
 public RVSPoliceBlockadeShooting() {
 this->name = "Police Blockade Shooting";
 this->minZoneWidth = 8;
 this->minZoneHeight = 8;
 this->setChance(1);
 this->setMaximumDays(30);
 }

 bool isValid(IsoMetaGrid.Zone zone, IsoChunk chunk, bool force) {
 bool boolean0 = super.isValid(zone, chunk, force);
 return !boolean0 ? false : zone.isRectangle();
 }

 void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
 this->callVehicleStorySpawner(zone, chunk, 0.0F);
 }

 bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk, bool debug) {
 VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
 vehicleStorySpawner.clear();
 float float0 = (float) (Math.PI / 18);
 if (debug) {
 float0 = 0.0F;
 }

 float float1 = 1.5F;
 float float2 = 1.0F;
 if (this->zoneWidth >= 10) {
 float1 = 2.5F;
 float2 = 0.0F;
 }

 bool boolean0 = Rand.NextBool(2);
 if (debug) {
 boolean0 = true;
 }

 IsoDirections directions = Rand.NextBool(2) ? IsoDirections.W : IsoDirections.E;
 Vector2 vector = directions.ToVector();
 vector.rotate(Rand.Next(-float0, float0);
 vehicleStorySpawner.addElement("vehicle1", -float1, float2, vector.getDirection(), 2.0F, 5.0F);
 vector = directions.RotLeft(4).ToVector();
 vector.rotate(Rand.Next(-float0, float0);
 vehicleStorySpawner.addElement("vehicle2", float1, -float2, vector.getDirection(), 2.0F, 5.0F);
 vehicleStorySpawner.addElement(
 "barricade", 0.0F, boolean0 ? -float2 - 2.5F : float2 + 2.5F, IsoDirections.N.ToVector().getDirection(), this->zoneWidth, 1.0F
 );
 int int0 = Rand.Next(7, 15);

 for (int int1 = 0; int1 < int0; int1++) {
 vehicleStorySpawner.addElement(
 "corpse",
 Rand.Next(-this->zoneWidth / 2.0F + 1.0F, this->zoneWidth / 2.0F - 1.0F),
 boolean0 ? Rand.Next(-7, -4) - float2 : Rand.Next(5, 8) + float2,
 IsoDirections.getRandom().ToVector().getDirection(),
 1.0F,
 2.0F
 );
 }

 std::string string = "Base.CarLightsPolice";
 if (Rand.NextBool(3) {
 string = "Base.PickUpVanLightsPolice";
 }

 vehicleStorySpawner.setParameter("zone", zone);
 vehicleStorySpawner.setParameter("script", string);
 return true;
 }

 void spawnElement(VehicleStorySpawner spawner, VehicleStorySpawner.Element element) {
 IsoGridSquare square0 = element.square;
 if (square0 != nullptr) {
 float float0 = element.z;
 IsoMetaGrid.Zone zone = spawner.getParameter("zone", IsoMetaGrid.Zone.class);
 std::string string0 = spawner.getParameterString("script");
 std::string string1 = element.id;
 switch (string1) {
 case "barricade":
 if (this->horizontalZone) {
 int int0 = (int)(element.position.y - element.width / 2.0F);
 int int1 = (int)(element.position.y + element.width / 2.0F) - 1;
 int int2 = (int)element.position.x;

 for (int int3 = int0; int3 <= int1; int3++) {
 IsoGridSquare square1 = IsoCell.getInstance().getGridSquare(int2, int3, zone.z);
 if (square1 != nullptr) {
 if (int3 != int0 && int3 != int1) {
 square1.AddTileObject(IsoObject.getNew(square1, "construction_01_9", nullptr, false);
 } else {
 square1.AddTileObject(IsoObject.getNew(square1, "street_decoration_01_26", nullptr, false);
 }
 }
 }
 } else {
 int int4 = (int)(element.position.x - element.width / 2.0F);
 int int5 = (int)(element.position.x + element.width / 2.0F) - 1;
 int int6 = (int)element.position.y;

 for (int int7 = int4; int7 <= int5; int7++) {
 IsoGridSquare square2 = IsoCell.getInstance().getGridSquare(int7, int6, zone.z);
 if (square2 != nullptr) {
 if (int7 != int4 && int7 != int5) {
 square2.AddTileObject(IsoObject.getNew(square2, "construction_01_8", nullptr, false);
 } else {
 square2.AddTileObject(IsoObject.getNew(square2, "street_decoration_01_26", nullptr, false);
 }
 }
 }
 }
 break;
 case "corpse":
 BaseVehicle vehicle1 = spawner.getParameter("vehicle1", BaseVehicle.class);
 if (vehicle1 != nullptr) {
 createRandomDeadBody(element.position.x, element.position.y, zone.z, element.direction, false, 10, 10, nullptr);
 IsoDirections directions = this->horizontalZone
 ? (element.position.x < vehicle1.x ? IsoDirections.W : IsoDirections.E)
 : (element.position.y < vehicle1.y ? IsoDirections.N : IsoDirections.S);
 float float1 = directions.ToVector().getDirection();
 this->addTrailOfBlood(element.position.x, element.position.y, element.z, float1, 5);
 }
 break;
 case "vehicle1":
 case "vehicle2":
 BaseVehicle vehicle0 = this->addVehicle(zone, element.position.x, element.position.y, float0, element.direction, nullptr, string0, nullptr, nullptr);
 if (vehicle0 != nullptr) {
 spawner.setParameter(element.id, vehicle0);
 if (Rand.NextBool(3) {
 vehicle0.setHeadlightsOn(true);
 vehicle0.setLightbarLightsMode(2);
 VehiclePart part = vehicle0.getBattery();
 if (part != nullptr) {
 part.setLastUpdated(0.0F);
 }
 }

 std::string string2 = "PoliceRiot";
 int integer = 0;
 this->addZombiesOnVehicle(Rand.Next(2, 4), string2, integer, vehicle0);
 }
 }
 }
 }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
