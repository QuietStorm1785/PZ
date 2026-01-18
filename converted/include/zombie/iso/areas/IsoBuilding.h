#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Rectangle.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LotHeader.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace iso {
namespace areas {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoBuilding : public IsoArea {
public:
 Rectangle bounds;
 public Vector<IsoRoomExit> Exits = std::make_unique<Vector<>>();
 bool IsResidence = true;
 public ArrayList<ItemContainer> container = std::make_unique<ArrayList<>>();
 public Vector<IsoRoom> Rooms = std::make_unique<Vector<>>();
 public Vector<IsoWindow> Windows = std::make_unique<Vector<>>();
 int ID = 0;
 static int IDMax = 0;
 int safety = 0;
 int transparentWalls = 0;
 bool isToxic = false;
 static float PoorBuildingScore = 10.0F;
 static float GoodBuildingScore = 100.0F;
 int scoreUpdate = -1;
 BuildingDef def;
 bool bSeenInside = false;
 public ArrayList<IsoLightSource> lights = std::make_unique<ArrayList<>>();
 static ArrayList<IsoRoom> tempo = std::make_unique<ArrayList<>>();
 static ArrayList<ItemContainer> tempContainer = std::make_unique<ArrayList<>>();
 static ArrayList<String> RandomContainerChoices = std::make_unique<ArrayList<>>();
 static ArrayList<IsoWindow> windowchoices = std::make_unique<ArrayList<>>();

 int getRoomsNumber() {
 return this->Rooms.size();
 }

 public IsoBuilding() {
 this->ID = IDMax++;
 this->scoreUpdate = -120 + Rand.Next(120);
 }

 int getID() {
 return this->ID;
 }

 void TriggerAlarm() {
 }

 public IsoBuilding(IsoCell cell) {
 this->ID = IDMax++;
 this->scoreUpdate = -120 + Rand.Next(120);
 }

 bool ContainsAllItems(Stack<String> items) {
 return false;
 }

 float ScoreBuildingPersonSpecific(SurvivorDesc desc, bool bFarGood) {
 float float0 = 0.0F;
 float0 += this->Rooms.size() * 5;
 float0 += this->Exits.size() * 15;
 float0 -= this->transparentWalls * 10;

 for (int int0 = 0; int0 < this->container.size(); int0++) {
 ItemContainer containerx = this->container.get(int0);
 float0 += containerx.Items.size() * 3;
 }

 if (!IsoWorld.instance.CurrentCell.getBuildingScores().containsKey(this->ID) {
 BuildingScore buildingScore0 = new BuildingScore(this);
 buildingScore0.building = this;
 IsoWorld.instance.CurrentCell.getBuildingScores().put(this->ID, buildingScore0);
 this->ScoreBuildingGeneral(buildingScore0);
 }

 BuildingScore buildingScore1 = IsoWorld.instance.CurrentCell.getBuildingScores().get(this->ID);
 float0 += (buildingScore1.defense + buildingScore1.food + buildingScore1.size + buildingScore1.weapons + buildingScore1.wood) * 10.0F;
 int int1 = -10000;
 int int2 = -10000;
 if (!this->Exits.empty()) {
 IsoRoomExit roomExit = this->Exits.get(0);
 int1 = roomExit.x;
 int2 = roomExit.y;
 }

 float float1 = IsoUtils.DistanceManhatten(desc.getInstance().getX(), desc.getInstance().getY(), int1, int2);
 if (float1 > 0.0F) {
 if (bFarGood) {
 float0 *= float1 * 0.5F;
 } else {
 float0 /= float1 * 0.5F;
 }
 }

 return float0;
 }

 BuildingDef getDef() {
 return this->def;
 }

 void update() {
 if (!this->Exits.empty()) {
 int int0 = 0;
 int int1 = 0;

 for (int int2 = 0; int2 < this->Rooms.size(); int2++) {
 IsoRoom room = this->Rooms.get(int2);
 if (room.layer == 0) {
 for (int int3 = 0; int3 < room.TileList.size(); int3++) {
 int1++;
 IsoGridSquare square = room.TileList.get(int3);
 }
 }
 }

 if (int1 == 0) {
 int1++;
 }

 int0 = (int)((float)int0 / int1);
 this->scoreUpdate--;
 if (this->scoreUpdate <= 0) {
 this->scoreUpdate += 120;
 BuildingScore buildingScore = nullptr;
 if (IsoWorld.instance.CurrentCell.getBuildingScores().containsKey(this->ID) {
 buildingScore = IsoWorld.instance.CurrentCell.getBuildingScores().get(this->ID);
 } else {
 buildingScore = new BuildingScore(this);
 buildingScore.building = this;
 }

 buildingScore = this->ScoreBuildingGeneral(buildingScore);
 buildingScore.defense += int0 * 10;
 this->safety = int0;
 IsoWorld.instance.CurrentCell.getBuildingScores().put(this->ID, buildingScore);
 }
 }
 }

 void AddRoom(IsoRoom room) {
 this->Rooms.add(room);
 if (this->bounds.empty()) {
 this->bounds = (Rectangle)room.bounds.clone();
 }

 if (room != nullptr && room.bounds != nullptr) {
 this->bounds.add(room.bounds);
 }
 }

 void CalculateExits() {
 for (IsoRoom room : this->Rooms) {
 for (IsoRoomExit roomExit : room.Exits) {
 if (roomExit.To.From.empty() && room.layer == 0) {
 this->Exits.add(roomExit);
 }
 }
 }
 }

 void CalculateWindows() {
 for (IsoRoom room : this->Rooms) {
 for (IsoGridSquare square0 : room.TileList) {
 IsoGridSquare square1 = square0.getCell().getGridSquare(square0.getX(), square0.getY() + 1, square0.getZ());
 IsoGridSquare square2 = square0.getCell().getGridSquare(square0.getX() + 1, square0.getY(), square0.getZ());
 if (square0.getProperties().Is(IsoFlagType.collideN) && square0.getProperties().Is(IsoFlagType.transparentN) {
 room.transparentWalls++;
 this->transparentWalls++;
 }

 if (square0.getProperties().Is(IsoFlagType.collideW) && square0.getProperties().Is(IsoFlagType.transparentW) {
 room.transparentWalls++;
 this->transparentWalls++;
 }

 if (square1 != nullptr) {
 bool boolean0 = square1.getRoom() != nullptr;
 if (square1.getRoom() != nullptr && square1.getRoom().building != room.building) {
 boolean0 = false;
 }

 if (square1.getProperties().Is(IsoFlagType.collideN) && square1.getProperties().Is(IsoFlagType.transparentN) && !boolean0) {
 room.transparentWalls++;
 this->transparentWalls++;
 }
 }

 if (square2 != nullptr) {
 bool boolean1 = square2.getRoom() != nullptr;
 if (square2.getRoom() != nullptr && square2.getRoom().building != room.building) {
 boolean1 = false;
 }

 if (square2.getProperties().Is(IsoFlagType.collideW) && square2.getProperties().Is(IsoFlagType.transparentW) && !boolean1) {
 room.transparentWalls++;
 this->transparentWalls++;
 }
 }

 for (int int0 = 0; int0 < square0.getSpecialObjects().size(); int0++) {
 IsoObject object0 = square0.getSpecialObjects().get(int0);
 if (object0 instanceof IsoWindow) {
 this->Windows.add((IsoWindow)object0);
 }
 }

 if (square1 != nullptr) {
 for (int int1 = 0; int1 < square1.getSpecialObjects().size(); int1++) {
 IsoObject object1 = square1.getSpecialObjects().get(int1);
 if (object1 instanceof IsoWindow) {
 this->Windows.add((IsoWindow)object1);
 }
 }
 }

 if (square2 != nullptr) {
 for (int int2 = 0; int2 < square2.getSpecialObjects().size(); int2++) {
 IsoObject object2 = square2.getSpecialObjects().get(int2);
 if (object2 instanceof IsoWindow) {
 this->Windows.add((IsoWindow)object2);
 }
 }
 }
 }
 }
 }

 void FillContainers() {
 bool boolean0 = false;

 for (IsoRoom room : this->Rooms) {
 if (room.RoomDef != nullptr && room.RoomDef.contains("tutorial")) {
 boolean0 = true;
 }

 if (!room.TileList.empty()) {
 IsoGridSquare square0 = room.TileList.get(0);
 if (square0.getX() < 74 && square0.getY() < 32) {
 boolean0 = true;
 }
 }

 if (room.RoomDef.contains("shop")) {
 this->IsResidence = false;
 }

 for (IsoGridSquare square1 : room.TileList) {
 for (int int0 = 0; int0 < square1.getObjects().size(); int0++) {
 IsoObject object = square1.getObjects().get(int0);
 if (object.hasWater()) {
 room.getWaterSources().add(object);
 }

 if (object.container != nullptr) {
 this->container.add(object.container);
 room.Containers.add(object.container);
 }
 }

 if (square1.getProperties().Is(IsoFlagType.bed) {
 room.Beds.add(square1);
 }
 }
 }
 }

 ItemContainer getContainerWith(ItemType itemType) {
 for (IsoRoom room : this->Rooms) {
 for (ItemContainer containerx : room.Containers) {
 if (containerx.HasType(itemType) {
 return containerx;
 }
 }
 }

 return nullptr;
 }

 IsoRoom getRandomRoom() {
 return this->Rooms.size() == 0 ? nullptr : this->Rooms.get(Rand.Next(this->Rooms.size()));
 }

 BuildingScore ScoreBuildingGeneral(BuildingScore buildingScore) {
 buildingScore.food = 0.0F;
 buildingScore.defense = 0.0F;
 buildingScore.weapons = 0.0F;
 buildingScore.wood = 0.0F;
 buildingScore.building = this;
 buildingScore.size = 0;
 buildingScore.defense = buildingScore.defense + (this->Exits.size() - 1) * 140;
 buildingScore.defense = buildingScore.defense - this->transparentWalls * 40;
 buildingScore.size = this->Rooms.size() * 10;
 buildingScore.size = buildingScore.size + this->container.size() * 10;
 return buildingScore;
 }

 IsoGridSquare getFreeTile() {
 IsoGridSquare square = nullptr;

 do {
 IsoRoom room = this->Rooms.get(Rand.Next(this->Rooms.size()));
 square = room.getFreeTile();
 } while (square.empty());

 return square;
 }

 bool hasWater() {
 Iterator iterator = this->Rooms.iterator();

 while (iterator != nullptr && iterator.hasNext()) {
 IsoRoom room = (IsoRoom)iterator.next();
 if (!room.WaterSources.empty()) {
 IsoObject object = nullptr;
 int int0 = 0;

 while (true) {
 if (int0 < room.WaterSources.size()) {
 if (!room.WaterSources.get(int0).hasWater()) {
 int0++;
 continue;
 }

 object = room.WaterSources.get(int0);
 }

 if (object != nullptr) {
 return true;
 }
 break;
 }
 }
 }

 return false;
 }

 void CreateFrom(BuildingDef building, LotHeader info) {
 for (int int0 = 0; int0 < building.rooms.size(); int0++) {
 IsoRoom room = info.getRoom(building.rooms.get(int0).ID);
 room.building = this;
 this->Rooms.add(room);
 }
 }

 void setAllExplored(bool b) {
 this->def.bAlarmed = false;

 for (int int0 = 0; int0 < this->Rooms.size(); int0++) {
 IsoRoom room = this->Rooms.get(int0);
 room.def.setExplored(b);

 for (int int1 = room.def.getX(); int1 <= room.def.getX2(); int1++) {
 for (int int2 = room.def.getY(); int2 <= room.def.getY2(); int2++) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int1, int2, room.def.level);
 if (square != nullptr) {
 square.setHourSeenToCurrent();
 }
 }
 }
 }
 }

 bool isAllExplored() {
 for (int int0 = 0; int0 < this->Rooms.size(); int0++) {
 IsoRoom room = this->Rooms.get(int0);
 if (!room.def.bExplored) {
 return false;
 }
 }

 return true;
 }

 void addWindow(IsoWindow obj, bool bOtherTile, IsoGridSquare from, IsoBuilding building) {
 this->Windows.add(obj);
 IsoGridSquare square = nullptr;
 if (bOtherTile) {
 square = obj.square;
 } else {
 square = from;
 }

 if (square != nullptr) {
 if (square.getRoom() == nullptr) {
 float float0 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 float float1 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 float float2 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 uint8_t byte0 = 7;
 IsoLightSource lightSource = new IsoLightSource(square.getX(), square.getY(), square.getZ(), float0, float1, float2, byte0, building);
 this->lights.add(lightSource);
 IsoWorld.instance.CurrentCell.getLamppostPositions().add(lightSource);
 }
 }
 }

 void addWindow(IsoWindow obj, bool bOtherTile) {
 this->addWindow(obj, bOtherTile, obj.square, nullptr);
 }

 void addDoor(IsoDoor obj, bool bOtherTile, IsoGridSquare from, IsoBuilding building) {
 IsoGridSquare square = nullptr;
 if (bOtherTile) {
 square = obj.square;
 } else {
 square = from;
 }

 if (square != nullptr) {
 if (square.getRoom() == nullptr) {
 float float0 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 float float1 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 float float2 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 uint8_t byte0 = 7;
 IsoLightSource lightSource = new IsoLightSource(square.getX(), square.getY(), square.getZ(), float0, float1, float2, byte0, building);
 this->lights.add(lightSource);
 IsoWorld.instance.CurrentCell.getLamppostPositions().add(lightSource);
 }
 }
 }

 void addDoor(IsoDoor obj, bool bOtherTile) {
 this->addDoor(obj, bOtherTile, obj.square, nullptr);
 }

 bool isResidential() {
 return this->containsRoom("bedroom");
 }

 bool containsRoom(const std::string& room) {
 for (int int0 = 0; int0 < this->Rooms.size(); int0++) {
 if (room == this->Rooms.get(int0).getName())) {
 return true;
 }
 }

 return false;
 }

 IsoRoom getRandomRoom(const std::string& room) {
 tempo.clear();

 for (int int0 = 0; int0 < this->Rooms.size(); int0++) {
 if (room == this->Rooms.get(int0).getName())) {
 tempo.add(this->Rooms.get(int0);
 }
 }

 return tempo.empty() ? nullptr : tempo.get(Rand.Next(tempo.size()));
 }

 ItemContainer getRandomContainer(const std::string& type) {
 RandomContainerChoices.clear();
 String[] strings = nullptr;
 if (type != nullptr) {
 strings = type.split(",");
 }

 if (strings != nullptr) {
 for (int int0 = 0; int0 < strings.length; int0++) {
 RandomContainerChoices.add(strings[int0]);
 }
 }

 tempContainer.clear();

 for (int int1 = 0; int1 < this->Rooms.size(); int1++) {
 IsoRoom room = this->Rooms.get(int1);

 for (int int2 = 0; int2 < room.Containers.size(); int2++) {
 ItemContainer containerx = room.Containers.get(int2);
 if (type.empty() || RandomContainerChoices.contains(containerx.getType())) {
 tempContainer.add(containerx);
 }
 }
 }

 return tempContainer.empty() ? nullptr : tempContainer.get(Rand.Next(tempContainer.size()));
 }

 IsoWindow getRandomFirstFloorWindow() {
 windowchoices.clear();
 windowchoices.addAll(this->Windows);

 for (int int0 = 0; int0 < windowchoices.size(); int0++) {
 if (windowchoices.get(int0).getZ() > 0.0F) {
 windowchoices.remove(int0);
 }
 }

 return !windowchoices.empty() ? windowchoices.get(Rand.Next(windowchoices.size())) : nullptr;
 }

 bool isToxic() {
 return this->isToxic;
 }

 void setToxic(bool _isToxic) {
 this->isToxic = _isToxic;
 }

 /**
 * Check for player inside the house and awake them all
 */
 void forceAwake() {
 for (int int0 = this->def.getX(); int0 <= this->def.getX2(); int0++) {
 for (int int1 = this->def.getY(); int1 <= this->def.getY2(); int1++) {
 for (int int2 = 0; int2 <= 4; int2++) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 for (int int3 = 0; int3 < square.getMovingObjects().size(); int3++) {
 if (square.getMovingObjects().get(int3) instanceof IsoGameCharacter) {
 ((IsoGameCharacter)square.getMovingObjects().get(int3).forceAwake();
 }
 }
 }
 }
 }
 }
 }
}
} // namespace areas
} // namespace iso
} // namespace zombie
