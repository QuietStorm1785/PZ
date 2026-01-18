#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RZSSexyTime : public RandomizedZoneStoryBase {
public:
 private ArrayList<String> pantsMaleItems = std::make_unique<ArrayList<>>();
 private ArrayList<String> pantsFemaleItems = std::make_unique<ArrayList<>>();
 private ArrayList<String> topItems = std::make_unique<ArrayList<>>();
 private ArrayList<String> shoesItems = std::make_unique<ArrayList<>>();

 public RZSSexyTime() {
 this->name = "Sexy Time";
 this->chance = 5;
 this->minZoneHeight = 5;
 this->minZoneWidth = 5;
 this->zoneType.add(RandomizedZoneStoryBase.ZoneType.Beach.toString());
 this->zoneType.add(RandomizedZoneStoryBase.ZoneType.Forest.toString());
 this->zoneType.add(RandomizedZoneStoryBase.ZoneType.Lake.toString());
 this->shoesItems.add("Base.Shoes_Random");
 this->shoesItems.add("Base.Shoes_TrainerTINT");
 this->pantsMaleItems.add("Base.TrousersMesh_DenimLight");
 this->pantsMaleItems.add("Base.Trousers_DefaultTEXTURE_TINT");
 this->pantsMaleItems.add("Base.Trousers_Denim");
 this->pantsFemaleItems.add("Base.Skirt_Knees");
 this->pantsFemaleItems.add("Base.Skirt_Long");
 this->pantsFemaleItems.add("Base.Skirt_Short");
 this->pantsFemaleItems.add("Base.Skirt_Normal");
 this->topItems.add("Base.Shirt_FormalWhite");
 this->topItems.add("Base.Shirt_FormalWhite_ShortSleeve");
 this->topItems.add("Base.Tshirt_DefaultTEXTURE_TINT");
 this->topItems.add("Base.Tshirt_PoloTINT");
 this->topItems.add("Base.Tshirt_WhiteLongSleeveTINT");
 this->topItems.add("Base.Tshirt_WhiteTINT");
 }

 void randomizeZoneStory(IsoMetaGrid.Zone zone) {
 this->cleanAreaForStory(this, zone);
 BaseVehicle vehicle = this->addVehicle(
 zone, this->getSq(zone.pickedXForZoneStory, zone.pickedYForZoneStory, zone.z), nullptr, nullptr, "Base.VanAmbulance", nullptr, nullptr, nullptr
 );
 if (vehicle != nullptr) {
 vehicle.setAlarmed(false);
 }

 bool boolean0 = Rand.Next(7) == 0;
 bool boolean1 = Rand.Next(7) == 0;
 if (boolean0) {
 this->addItemsOnGround(zone, true, vehicle);
 this->addItemsOnGround(zone, true, vehicle);
 } else if (boolean1) {
 this->addItemsOnGround(zone, false, vehicle);
 this->addItemsOnGround(zone, false, vehicle);
 } else {
 this->addItemsOnGround(zone, true, vehicle);
 this->addItemsOnGround(zone, false, vehicle);
 }
 }

 void addItemsOnGround(IsoMetaGrid.Zone var1, bool boolean0, BaseVehicle vehicle) {
 uint8_t byte0 = 100;
 if (!boolean0) {
 byte0 = 0;
 }

 std::vector arrayList = this->addZombiesOnVehicle(1, "Naked", Integer.valueOf(byte0), vehicle);
 if (!arrayList.empty()) {
 IsoZombie zombie0 = (IsoZombie)arrayList.get(0);
 this->addRandomItemOnGround(zombie0.getSquare(), this->shoesItems);
 this->addRandomItemOnGround(zombie0.getSquare(), this->topItems);
 this->addRandomItemOnGround(zombie0.getSquare(), boolean0 ? this->pantsMaleItems : this->pantsFemaleItems);
 }
 }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
