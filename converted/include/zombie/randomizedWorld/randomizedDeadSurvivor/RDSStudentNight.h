#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Create some zombies in varsity outfit + 2 naked zombies in bedroom
 */
class RDSStudentNight : public RandomizedDeadSurvivorBase {
public:
 private ArrayList<String> items = std::make_unique<ArrayList<>>();
 private ArrayList<String> otherItems = std::make_unique<ArrayList<>>();
 private ArrayList<String> pantsMaleItems = std::make_unique<ArrayList<>>();
 private ArrayList<String> pantsFemaleItems = std::make_unique<ArrayList<>>();
 private ArrayList<String> topItems = std::make_unique<ArrayList<>>();
 private ArrayList<String> shoesItems = std::make_unique<ArrayList<>>();

 public RDSStudentNight() {
 this->name = "Student Night";
 this->setChance(4);
 this->setMaximumDays(60);
 this->otherItems.add("Base.Cigarettes");
 this->otherItems.add("Base.WhiskeyFull");
 this->otherItems.add("Base.Wine");
 this->otherItems.add("Base.Wine2");
 this->items.add("Base.Crisps");
 this->items.add("Base.Crisps2");
 this->items.add("Base.Crisps3");
 this->items.add("Base.Pop");
 this->items.add("Base.Pop2");
 this->items.add("Base.Pop3");
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

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef0 = this->getLivingRoomOrKitchen(def);
 this->addZombies(def, Rand.Next(2, 5), nullptr, nullptr, roomDef0);
 RoomDef roomDef1 = this->getRoom(def, "bedroom");
 this->addZombies(def, 1, "Naked", 0, roomDef1);
 this->addItemsOnGround(roomDef1, true);
 this->addZombies(def, 1, "Naked", 100, roomDef1);
 this->addItemsOnGround(roomDef1, false);
 this->addRandomItemsOnGround(roomDef0, this->items, Rand.Next(3, 7);
 this->addRandomItemsOnGround(roomDef0, this->otherItems, Rand.Next(2, 6);
 def.bAlarmed = false;
 }

 void addItemsOnGround(RoomDef roomDef, bool boolean0) {
 IsoGridSquare square = getRandomSpawnSquare(roomDef);
 this->addRandomItemOnGround(square, this->shoesItems);
 this->addRandomItemOnGround(square, this->topItems);
 this->addRandomItemOnGround(square, boolean0 ? this->pantsMaleItems : this->pantsFemaleItems);
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
