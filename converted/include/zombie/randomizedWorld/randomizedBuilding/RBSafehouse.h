#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * This building will be barricaded, have a lot of canned food but also lot of zombies inside it
 */
class RBSafehouse : public RandomizedBuildingBase {
public:
 void randomizeBuilding(BuildingDef def) {
 def.bAlarmed = false;
 def.setHasBeenVisited(true);
 ItemPickerJava.ItemPickerRoom itemPickerRoom = ItemPickerJava.rooms.get("SafehouseLoot");
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = def.x - 1; int0 < def.x2 + 1; int0++) {
 for (int int1 = def.y - 1; int1 < def.y2 + 1; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square0 = cell.getGridSquare(int0, int1, int2);
 if (square0 != nullptr) {
 for (int int3 = 0; int3 < square0.getObjects().size(); int3++) {
 IsoObject object = square0.getObjects().get(int3);
 if (object instanceof IsoDoor && ((IsoDoor)object).isBarricadeAllowed() && !SpawnPoints.instance.isSpawnBuilding(def) {
 IsoGridSquare square1 = square0.getRoom() == nullptr ? square0 : ((IsoDoor)object).getOppositeSquare();
 if (square1 != nullptr && square1.getRoom() == nullptr) {
 bool boolean0 = square1 != square0;
 IsoBarricade barricade0 = IsoBarricade.AddBarricadeToObject((IsoDoor)object, boolean0);
 if (barricade0 != nullptr) {
 int int4 = Rand.Next(1, 4);

 for (int int5 = 0; int5 < int4; int5++) {
 barricade0.addPlank(nullptr, nullptr);
 }

 if (GameServer.bServer) {
 barricade0.transmitCompleteItemToClients();
 }
 }
 }
 }

 if (object instanceof IsoWindow) {
 IsoGridSquare square2 = square0.getRoom() == nullptr ? square0 : ((IsoWindow)object).getOppositeSquare();
 if (((IsoWindow)object).isBarricadeAllowed() && int2 == 0 && square2 != nullptr && square2.getRoom() == nullptr) {
 bool boolean1 = square2 != square0;
 IsoBarricade barricade1 = IsoBarricade.AddBarricadeToObject((IsoWindow)object, boolean1);
 if (barricade1 != nullptr) {
 int int6 = Rand.Next(1, 4);

 for (int int7 = 0; int7 < int6; int7++) {
 barricade1.addPlank(nullptr, nullptr);
 }

 if (GameServer.bServer) {
 barricade1.transmitCompleteItemToClients();
 }
 }
 } else {
 ((IsoWindow)object).addSheet(nullptr);
 ((IsoWindow)object).HasCurtains().ToggleDoor(nullptr);
 }
 }

 if (object.getContainer() != nullptr
 && square0.getRoom() != nullptr
 && square0.getRoom().getBuilding().getDef() == def
 && Rand.Next(100) <= 70
 && square0.getRoom().getName() != nullptr
 && itemPickerRoom.Containers.containsKey(object.getContainer().getType())) {
 object.getContainer().clear();
 ItemPickerJava.fillContainerType(itemPickerRoom, object.getContainer(), "", nullptr);
 ItemPickerJava.updateOverlaySprite(object);
 object.getContainer().setExplored(true);
 }
 }
 }
 }
 }
 }

 def.setAllExplored(true);
 def.bAlarmed = false;
 this->addZombies(def);
 }

 void addZombies(BuildingDef buildingDef) {
 this->addZombies(buildingDef, 0, nullptr, nullptr, nullptr);
 if (Rand.Next(5) == 0) {
 this->addZombies(buildingDef, 1, "Survivalist", nullptr, nullptr);
 }

 if (Rand.Next(100) <= 60) {
 RandomizedBuildingBase.createRandomDeadBody(this->getLivingRoomOrKitchen(buildingDef), Rand.Next(3, 7);
 }

 if (Rand.Next(100) <= 60) {
 RandomizedBuildingBase.createRandomDeadBody(this->getLivingRoomOrKitchen(buildingDef), Rand.Next(3, 7);
 }
 }

 bool isValid(BuildingDef buildingDef, bool boolean0) {
 if (!super.isValid(buildingDef, boolean0) {
 return false;
 } else {
 return buildingDef.getRooms().size() > 20 ? false : !SpawnPoints.instance.isSpawnBuilding(buildingDef);
 }
 }

 public RBSafehouse() {
 this->name = "Safehouse";
 this->setChance(10);
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
