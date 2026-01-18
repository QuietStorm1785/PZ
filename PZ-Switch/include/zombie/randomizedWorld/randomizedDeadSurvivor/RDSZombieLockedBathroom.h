#pragma once
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/network/GameServer.h"
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
 * Zombie inside the barricaded bathroom and a dead corpse in front of it with a
 * pistol
 */
class RDSZombieLockedBathroom : public RandomizedDeadSurvivorBase {
public:
 void randomizeDeadSurvivor(BuildingDef def) {
 IsoDeadBody deadBody = nullptr;

 for (int int0 = 0; int0 < def.rooms.size(); int0++) {
 RoomDef roomDef = def.rooms.get(int0);
 IsoGridSquare square0 = nullptr;
 if ("bathroom" == roomDef.name) {
 if (IsoWorld.getZombiesEnabled()) {
 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(
 roomDef.getX(), roomDef.getY(), roomDef.getZ());
 if (square1 != nullptr && square1.getRoom() != nullptr) {
 IsoRoom room = square1.getRoom();
 square1 = room.getRandomFreeSquare();
 if (square1 != nullptr) {
 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square1);
 IsoZombie zombie0 =
 VirtualZombieManager.instance.createRealZombieAlways(
 IsoDirections.fromIndex(Rand.Next(8).index(), false);
 ZombieSpawnRecorder.instance.record(
 zombie0, this->getClass().getSimpleName());
 }
 }
 }

 for (int int1 = roomDef.x - 1; int1 < roomDef.x2 + 1; int1++) {
 for (int int2 = roomDef.y - 1; int2 < roomDef.y2 + 1; int2++) {
 square0 = IsoWorld.instance.getCell().getGridSquare(
 int1, int2, roomDef.getZ());
 if (square0 != nullptr) {
 IsoDoor door = square0.getIsoDoor();
 if (door != nullptr && this->isDoorToRoom(door, roomDef) {
 if (door.IsOpen()) {
 door.ToggleDoor(nullptr);
 }

 IsoBarricade barricade = IsoBarricade.AddBarricadeToObject(
 door, square0.getRoom().def == roomDef);
 if (barricade != nullptr) {
 barricade.addPlank(nullptr, nullptr);
 if (GameServer.bServer) {
 barricade.transmitCompleteItemToClients();
 }
 }

 deadBody = this->addDeadBodyTheOtherSide(door);
 break;
 }
 }
 }

 if (deadBody != nullptr) {
 break;
 }
 }

 if (deadBody != nullptr) {
 deadBody.setPrimaryHandItem(super.addWeapon("Base.Pistol", true);
 }

 return;
 }
 }
 }

 bool isDoorToRoom(IsoDoor door, RoomDef roomDef) {
 if (door != nullptr && roomDef != nullptr) {
 IsoGridSquare square0 = door.getSquare();
 IsoGridSquare square1 = door.getOppositeSquare();
 return square0 != nullptr && square1 != nullptr
 ? square0.getRoomID() == roomDef.ID !=
 (square1.getRoomID() == roomDef.ID)
 : false;
 } else {
 return false;
 }
 }

 bool checkIsBathroom(IsoGridSquare square) {
 return square.getRoom() != nullptr && "bathroom" == square.getRoom().getName());
 }

 IsoDeadBody addDeadBodyTheOtherSide(IsoDoor door) {
 void *object = nullptr;
 if (door.north) {
 object = IsoWorld.instance.getCell().getGridSquare(
 (double)door.getX(), (double)door.getY(), (double)door.getZ());
 if (this->checkIsBathroom((IsoGridSquare)object) {
 object = IsoWorld.instance.getCell().getGridSquare(
 (double)door.getX(), (double)(door.getY() - 1.0F),
 (double)door.getZ());
 }
 } else {
 object = IsoWorld.instance.getCell().getGridSquare(
 (double)door.getX(), (double)door.getY(), (double)door.getZ());
 if (this->checkIsBathroom((IsoGridSquare)object) {
 object = IsoWorld.instance.getCell().getGridSquare(
 (double)(door.getX() - 1.0F), (double)door.getY(),
 (double)door.getZ());
 }
 }

 return RandomizedDeadSurvivorBase.createRandomDeadBody(
 ((IsoGridSquare)object).getX(), ((IsoGridSquare)object).getY(),
 ((IsoGridSquare)object).getZ(), nullptr, Rand.Next(5, 10);
 }

public
 RDSZombieLockedBathroom() {
 this->name = "Locked in Bathroom";
 this->setChance(5);
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
