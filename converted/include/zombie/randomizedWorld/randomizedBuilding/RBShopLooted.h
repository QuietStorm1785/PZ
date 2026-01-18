#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Shop being looted by bandits + 2 cops and corpses inside the shop
 */
class RBShopLooted : public RandomizedBuildingBase {
public:
 private ArrayList<String> buildingList = std::make_unique<ArrayList<>>();

 void randomizeBuilding(BuildingDef def) {
 def.bAlarmed = false;
 def.setAllExplored(true);
 RoomDef roomDef0 = nullptr;

 for (int int0 = 0; int0 < def.rooms.size(); int0++) {
 RoomDef roomDef1 = def.rooms.get(int0);
 if (this->buildingList.contains(roomDef1.name) {
 roomDef0 = roomDef1;
 break;
 }
 }

 if (roomDef0 != nullptr) {
 int int1 = Rand.Next(3, 8);

 for (int int2 = 0; int2 < int1; int2++) {
 this->addZombiesOnSquare(1, "Bandit", nullptr, roomDef0.getFreeSquare());
 }

 this->addZombiesOnSquare(2, "Police", nullptr, roomDef0.getFreeSquare());
 int int3 = Rand.Next(3, 8);

 for (int int4 = 0; int4 < int3; int4++) {
 IsoGridSquare square = getRandomSquareForCorpse(roomDef0);
 createRandomDeadBody(square, nullptr, Rand.Next(5, 10), 5, nullptr);
 }
 }
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 this->debugLine = "";
 if (GameClient.bClient) {
 return false;
 } else if (!this->isTimeValid(force) {
 return false;
 } else if (def.isAllExplored() && !force) {
 return false;
 } else {
 if (!force) {
 if (Rand.Next(100) > this->getChance()) {
 return false;
 }

 for (int int0 = 0; int0 < GameServer.Players.size(); int0++) {
 IsoPlayer player = GameServer.Players.get(int0);
 if (player.getSquare() != nullptr && player.getSquare().getBuilding() != nullptr && player.getSquare().getBuilding().def == def) {
 return false;
 }
 }
 }

 for (int int1 = 0; int1 < def.rooms.size(); int1++) {
 RoomDef roomDef = def.rooms.get(int1);
 if (this->buildingList.contains(roomDef.name) {
 return true;
 }
 }

 this->debugLine = this->debugLine + "not a shop";
 return false;
 }
 }

 public RBShopLooted() {
 this->name = "Looted Shop";
 this->setChance(2);
 this->setAlwaysDo(true);
 this->setMaximumDays(30);
 this->buildingList.add("conveniencestore");
 this->buildingList.add("warehouse");
 this->buildingList.add("medclinic");
 this->buildingList.add("grocery");
 this->buildingList.add("zippeestore");
 this->buildingList.add("gigamart");
 this->buildingList.add("fossoil");
 this->buildingList.add("spiffo_dining");
 this->buildingList.add("pizzawhirled");
 this->buildingList.add("bookstore");
 this->buildingList.add("grocers");
 this->buildingList.add("library");
 this->buildingList.add("toolstore");
 this->buildingList.add("bar");
 this->buildingList.add("pharmacy");
 this->buildingList.add("gunstore");
 this->buildingList.add("mechanic");
 this->buildingList.add("bakery");
 this->buildingList.add("aesthetic");
 this->buildingList.add("clothesstore");
 this->buildingList.add("restaurant");
 this->buildingList.add("poststorage");
 this->buildingList.add("generalstore");
 this->buildingList.add("furniturestore");
 this->buildingList.add("fishingstorage");
 this->buildingList.add("cornerstore");
 this->buildingList.add("housewarestore");
 this->buildingList.add("shoestore");
 this->buildingList.add("sportstore");
 this->buildingList.add("giftstore");
 this->buildingList.add("candystore");
 this->buildingList.add("toystore");
 this->buildingList.add("electronicsstore");
 this->buildingList.add("sewingstore");
 this->buildingList.add("medical");
 this->buildingList.add("medicaloffice");
 this->buildingList.add("jewelrystore");
 this->buildingList.add("musicstore");
 this->buildingList.add("departmentstore");
 this->buildingList.add("gasstore");
 this->buildingList.add("gardenstore");
 this->buildingList.add("farmstorage");
 this->buildingList.add("hunting");
 this->buildingList.add("camping");
 this->buildingList.add("butcher");
 this->buildingList.add("optometrist");
 this->buildingList.add("knoxbutcher");
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
