#pragma once
#include "java/awt/Rectangle.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoRoomLight.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoRoom {
public:
private
 static ArrayList<IsoGridSquare> tempSquares =
 std::make_unique<ArrayList<>>();
public
 Vector<IsoGridSquare> Beds = std::make_unique<Vector<>>();
 Rectangle bounds;
 IsoBuilding building = nullptr;
public
 ArrayList<ItemContainer> Containers = std::make_unique<ArrayList<>>();
public
 ArrayList<IsoWindow> Windows = std::make_unique<ArrayList<>>();
public
 Vector<IsoRoomExit> Exits = std::make_unique<Vector<>>();
 int layer;
 std::string RoomDef = "none";
public
 Vector<IsoGridSquare> TileList = std::make_unique<Vector<>>();
 int transparentWalls = 0;
public
 ArrayList<IsoLightSwitch> lightSwitches =
 std::make_unique<ArrayList<>>();
public
 ArrayList<IsoRoomLight> roomLights = std::make_unique<ArrayList<>>();
public
 ArrayList<IsoObject> WaterSources = std::make_unique<ArrayList<>>();
 int seen = 1000000000;
 int visited = 1000000000;
 RoomDef def;
public
 ArrayList<RoomDef.RoomRect> rects = new ArrayList<>(1);
public
 ArrayList<IsoGridSquare> Squares = std::make_unique<ArrayList<>>();

 IsoBuilding getBuilding() { return this->building; }

 std::string getName() { return this->RoomDef; }

 IsoBuilding CreateBuilding(IsoCell cell) {
 IsoBuilding buildingx = new IsoBuilding(cell);
 this->AddToBuilding(buildingx);
 return buildingx;
 }

 bool isInside(int x, int y, int z) {
 for (int int0 = 0; int0 < this->rects.size(); int0++) {
 int int1 = this->rects.get(int0).x;
 int int2 = this->rects.get(int0).y;
 int int3 = this->rects.get(int0).getX2();
 int int4 = this->rects.get(int0).getY2();
 if (x >= int1 && y >= int2 && x < int3 && y < int4 && z == this->layer) {
 return true;
 }
 }

 return false;
 }

 IsoGridSquare getFreeTile() {
 bool boolean0 = false;
 IsoGridSquare square = nullptr;
 int int0 = 100;

 while (!boolean0 && int0 > 0) {
 int0--;
 boolean0 = true;
 if (this->TileList.empty()) {
 return nullptr;
 }

 square = this->TileList.get(Rand.Next(this->TileList.size()));

 for (int int1 = 0; int1 < this->Exits.size(); int1++) {
 if (square.getX() == this->Exits.get(int1).x &&
 square.getY() == this->Exits.get(int1).y) {
 boolean0 = false;
 }
 }

 if (boolean0 && !square.isFree(true) {
 boolean0 = false;
 }
 }

 return int0 < 0 ? nullptr : square;
 }

 void AddToBuilding(IsoBuilding buildingx) {
 this->building = buildingx;
 buildingx.AddRoom(this);

 for (IsoRoomExit roomExit : this->Exits) {
 if (roomExit.To.From != nullptr && roomExit.To.From.building.empty()) {
 roomExit.To.From.AddToBuilding(buildingx);
 }
 }
 }

 /**
 * @return the WaterSources
 */
public
 ArrayList<IsoObject> getWaterSources() { return this->WaterSources; }

 /**
 *
 * @param _WaterSources the WaterSources to set
 */
 void setWaterSources(ArrayList<IsoObject> _WaterSources) {
 this->WaterSources.clear();
 this->WaterSources.addAll(_WaterSources);
 }

 bool hasWater() {
 if (this->WaterSources.empty()) {
 return false;
 } else {
 Iterator iterator = this->WaterSources.iterator();

 while (iterator != nullptr && iterator.hasNext()) {
 IsoObject object = (IsoObject)iterator.next();
 if (object.hasWater()) {
 return true;
 }
 }

 return false;
 }
 }

 void useWater() {
 if (!this->WaterSources.empty()) {
 Iterator iterator = this->WaterSources.iterator();

 while (iterator != nullptr && iterator.hasNext()) {
 IsoObject object = (IsoObject)iterator.next();
 if (object.hasWater()) {
 object.useWater(1);
 break;
 }
 }
 }
 }

public
 ArrayList<IsoWindow> getWindows() { return this->Windows; }

 void addSquare(IsoGridSquare sq) {
 if (!this->Squares.contains(sq) {
 this->Squares.add(sq);
 }
 }

 void refreshSquares() {
 this->Windows.clear();
 this->Containers.clear();
 this->WaterSources.clear();
 this->Exits.clear();
 tempSquares.clear();
 tempSquares.addAll(this->Squares);
 this->Squares.clear();

 for (int int0 = 0; int0 < tempSquares.size(); int0++) {
 this->addSquare(tempSquares.get(int0);
 }
 }

 void addExitTo(IsoGridSquare square0, IsoGridSquare square1) {
 IsoRoom room0 = nullptr;
 IsoRoom room1 = nullptr;
 if (square0 != nullptr) {
 room0 = square0.getRoom();
 }

 if (square1 != nullptr) {
 room1 = square1.getRoom();
 }

 if (room0 != nullptr || room1 != nullptr) {
 IsoRoom room2 = room0;
 if (room0.empty()) {
 room2 = room1;
 }

 IsoRoomExit roomExit0 = new IsoRoomExit(room2, square0.getX(),
 square0.getY(), square0.getZ());
 roomExit0.type = IsoRoomExit.ExitType.Door;
 if (room2 == room0) {
 if (room1 != nullptr) {
 IsoRoomExit roomExit1 =
 room1.getExitAt(square1.getX(), square1.getY(), square1.getZ());
 if (roomExit1.empty()) {
 roomExit1 = new IsoRoomExit(room1, square1.getX(), square1.getY(),
 square1.getZ());
 room1.Exits.add(roomExit1);
 }

 roomExit0.To = roomExit1;
 } else {
 room0.building.Exits.add(roomExit0);
 if (square1 != nullptr) {
 roomExit0.To = new IsoRoomExit(roomExit0, square1.getX(),
 square1.getY(), square1.getZ());
 }
 }

 room0.Exits.add(roomExit0);
 } else {
 room1.building.Exits.add(roomExit0);
 if (square1 != nullptr) {
 roomExit0.To = new IsoRoomExit(roomExit0, square1.getX(),
 square1.getY(), square1.getZ());
 }

 room1.Exits.add(roomExit0);
 }
 }
 }

 IsoRoomExit getExitAt(int int3, int int2, int int1) {
 for (int int0 = 0; int0 < this->Exits.size(); int0++) {
 IsoRoomExit roomExit = this->Exits.get(int0);
 if (roomExit.x == int3 && roomExit.y == int2 && roomExit.layer == int1) {
 return roomExit;
 }
 }

 return nullptr;
 }

 void removeSquare(IsoGridSquare sq) {
 this->Squares.remove(sq);
 IsoRoomExit roomExit = this->getExitAt(sq.getX(), sq.getY(), sq.getZ());
 if (roomExit != nullptr) {
 this->Exits.remove(roomExit);
 if (roomExit.To != nullptr) {
 roomExit.From = nullptr;
 }

 if (this->building.Exits.contains(roomExit) {
 this->building.Exits.remove(roomExit);
 }
 }

 for (int int0 = 0; int0 < sq.getObjects().size(); int0++) {
 IsoObject object = sq.getObjects().get(int0);
 if (object instanceof IsoLightSwitch) {
 this->lightSwitches.remove(object);
 }
 }
 }

 void spawnZombies() {
 VirtualZombieManager.instance.addZombiesToMap(1, this->def, false);
 }

 void onSee() {
 for (int int0 = 0; int0 < this->getBuilding().Rooms.size(); int0++) {
 IsoRoom room1 = this->getBuilding().Rooms.elementAt(int0);
 if (room1 != nullptr && !room1.def.bExplored) {
 room1.def.bExplored = true;
 }

 IsoWorld.instance.getCell().roomSpotted(room1);
 }
 }

public
 Vector<IsoGridSquare> getTileList() { return this->TileList; }

public
 ArrayList<IsoGridSquare> getSquares() { return this->Squares; }

public
 ArrayList<ItemContainer> getContainer() { return this->Containers; }

 IsoGridSquare getRandomSquare() {
 return this->Squares.empty()
 ? nullptr
 : this->Squares.get(Rand.Next(this->Squares.size()));
 }

 IsoGridSquare getRandomFreeSquare() {
 int int0 = 100;
 IsoGridSquare square = nullptr;
 if (GameServer.bServer) {
 while (int0 > 0) {
 square = IsoWorld.instance.CurrentCell.getGridSquare(
 this->def.getX() + Rand.Next(this->def.getW()),
 this->def.getY() + Rand.Next(this->def.getH()), this->def.level);
 if (square != nullptr && square.getRoom() == this &&
 square.isFree(true) {
 return square;
 }

 int0--;
 }

 return nullptr;
 } else if (this->Squares.empty()) {
 return nullptr;
 } else {
 while (int0 > 0) {
 square = this->Squares.get(Rand.Next(this->Squares.size()));
 if (square.isFree(true) {
 return square;
 }

 int0--;
 }

 return nullptr;
 }
 }

 bool hasLightSwitches() {
 if (!this->lightSwitches.empty()) {
 return true;
 } else {
 for (int int0 = 0; int0 < this->def.objects.size(); int0++) {
 if (this->def.objects.get(int0).getType() == 7) {
 return true;
 }
 }

 return false;
 }
 }

 void createLights(bool active) {
 if (this->roomLights.empty()) {
 for (int int0 = 0; int0 < this->def.rects.size(); int0++) {
 RoomDef.RoomRect roomRect = this->def.rects.get(int0);
 IsoRoomLight roomLight =
 new IsoRoomLight(this, roomRect.x, roomRect.y, this->def.level,
 roomRect.w, roomRect.h);
 this->roomLights.add(roomLight);
 }
 }
 }

 RoomDef getRoomDef() { return this->def; }

public
 ArrayList<IsoLightSwitch> getLightSwitches() { return this->lightSwitches; }
}
} // namespace areas
} // namespace iso
} // namespace zombie
