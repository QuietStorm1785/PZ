#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TLongObjectHashMap.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include <algorithm>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LotHeader {
public:
 int cellX;
 int cellY;
 int width = 0;
 int height = 0;
 int levels = 0;
 int version = 0;
 public HashMap<Integer, RoomDef> Rooms = std::make_unique<HashMap<>>();
 public TLongObjectHashMap<RoomDef> RoomByMetaID = std::make_unique<TLongObjectHashMap<>>();
 public ArrayList<RoomDef> RoomList = std::make_unique<ArrayList<>>();
 public ArrayList<BuildingDef> Buildings = std::make_unique<ArrayList<>>();
 public TLongObjectHashMap<BuildingDef> BuildingByMetaID = std::make_unique<TLongObjectHashMap<>>();
 public HashMap<Integer, IsoRoom> isoRooms = std::make_unique<HashMap<>>();
 public HashMap<Integer, IsoBuilding> isoBuildings = std::make_unique<HashMap<>>();
 bool bFixed2x;
 protected ArrayList<String> tilesUsed = std::make_unique<ArrayList<>>();

 int getHeight() {
 return this->height;
 }

 int getWidth() {
 return this->width;
 }

 int getLevels() {
 return this->levels;
 }

 IsoRoom getRoom(int roomID) {
 RoomDef roomDef = this->Rooms.get(roomID);
 if (!this->isoRooms.containsKey(roomID) {
 IsoRoom room = new IsoRoom();
 room.rects.addAll(roomDef.rects);
 room.RoomDef = roomDef.name;
 room.def = roomDef;
 room.layer = roomDef.level;
 IsoWorld.instance.CurrentCell.getRoomList().add(room);
 if (roomDef.building == nullptr) {
 roomDef.building = std::make_unique<BuildingDef>();
 roomDef.building.ID = this->Buildings.size();
 roomDef.building.rooms.add(roomDef);
 roomDef.building.CalculateBounds(std::make_unique<ArrayList<>>());
 roomDef.building.metaID = roomDef.building.calculateMetaID(this->cellX, this->cellY);
 this->Buildings.add(roomDef.building);
 }

 int int0 = roomDef.building.ID;
 this->isoRooms.put(roomID, room);
 if (!this->isoBuildings.containsKey(int0) {
 room.building = std::make_unique<IsoBuilding>();
 room.building.def = roomDef.building;
 this->isoBuildings.put(int0, room.building);
 room.building.CreateFrom(roomDef.building, this);
 } else {
 room.building = this->isoBuildings.get(int0);
 }

 return room;
 } else {
 return this->isoRooms.get(roomID);
 }
 }

 int getRoomAt(int x, int y, int z) {
 for (Entry entry : this->Rooms.entrySet()) {
 RoomDef roomDef = (RoomDef)entry.getValue();

 for (int int0 = 0; int0 < roomDef.rects.size(); int0++) {
 RoomDef.RoomRect roomRect = roomDef.rects.get(int0);
 if (roomRect.x <= x && roomRect.y <= y && roomDef.level == z && roomRect.getX2() > x && roomRect.getY2() > y) {
 return (Integer)entry.getKey();
 }
 }
 }

 return -1;
 }

 void Dispose() {
 this->Rooms.clear();
 this->RoomByMetaID.clear();
 this->RoomList.clear();
 this->Buildings.clear();
 this->BuildingByMetaID.clear();
 this->isoRooms.clear();
 this->isoBuildings.clear();
 this->tilesUsed.clear();
 }
}
} // namespace iso
} // namespace zombie
