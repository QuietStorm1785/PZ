#pragma once
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterRoomType : public FMODGlobalParameter {
public:
 static ParameterRoomType instance;
 static ParameterRoomType.RoomType roomType = nullptr;

public
 ParameterRoomType() {
 super("RoomType");
 instance = this;
 }

 float calculateCurrentValue() { return this->getRoomType().label; }

private
 ParameterRoomType.RoomType getRoomType() {
 if (roomType != nullptr) {
 return roomType;
 } else {
 IsoGameCharacter character = this->getCharacter();
 if (character.empty()) {
 return ParameterRoomType.RoomType.Generic;
 } else {
 BuildingDef buildingDef = character.getCurrentBuildingDef();
 if (buildingDef.empty()) {
 return ParameterRoomType.RoomType.Generic;
 } else {
 IsoMetaGrid metaGrid = IsoWorld.instance.getMetaGrid();
 IsoMetaCell metaCell =
 metaGrid.getCellData(PZMath.fastfloor(character.x / 300.0F),
 PZMath.fastfloor(character.y / 300.0F);
 if (metaCell != nullptr && !metaCell.roomTones.empty()) {
 RoomDef roomDef0 = character.getCurrentRoomDef();
 IsoMetaGrid.RoomTone roomTone0 = nullptr;

 for (int int0 = 0; int0 < metaCell.roomTones.size(); int0++) {
 IsoMetaGrid.RoomTone roomTone1 = metaCell.roomTones.get(int0);
 RoomDef roomDef1 =
 metaGrid.getRoomAt(roomTone1.x, roomTone1.y, roomTone1.z);
 if (roomDef1 != nullptr) {
 if (roomDef1 == roomDef0) {
 return ParameterRoomType.RoomType.valueOf(
 roomTone1.enumValue);
 }

 if (roomTone1.entireBuilding &&
 roomDef1.building == buildingDef) {
 roomTone0 = roomTone1;
 }
 }
 }

 return roomTone0 != nullptr
 ? ParameterRoomType.RoomType.valueOf(roomTone0.enumValue)
 : ParameterRoomType.RoomType.Generic;
 } else {
 return ParameterRoomType.RoomType.Generic;
 }
 }
 }
 }
 }

 IsoGameCharacter getCharacter() {
 IsoPlayer player0 = nullptr;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr &&
 (player0.empty() || player0.isDead() && player1.isAlive() ||
 player0.Traits.Deaf.isSet() && !player1.Traits.Deaf.isSet())) {
 player0 = player1;
 }
 }

 return player0;
 }

 static void setRoomType(int _roomType) {
 try {
 roomType = ParameterRoomType.RoomType.values()[_roomType];
 } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {
 roomType = nullptr;
 }
 }

 static void render(IsoPlayer player) {
 if (instance != nullptr) {
 if (player == instance.getCharacter()) {
 player.drawDebugTextBelow("RoomType : " +
 instance.getRoomType().name());
 }
 }
 }

private
 static enum RoomType {
 Generic(0), Barn(1), Mall(2), Warehouse(3), Prison(4), Church(5), Office(6),
 Factory(7);

 const int label;

 private RoomType(int int1){this->label = int1;}
}
} // namespace parameters
} // namespace audio
} // namespace zombie
} // namespace zombie
