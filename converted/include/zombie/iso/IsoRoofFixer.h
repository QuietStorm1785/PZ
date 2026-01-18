#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoRoofFixer {
public:
 static const bool PER_ROOM_MODE = true;
 static const int MAX_Z = 8;
 static const int SCAN_RANGE = 3;
 static const bool ALWAYS_INVIS_FLOORS = false;
 static bool roofTileGlassCacheDirty = true;
 static bool roofTileIsGlass = false;
 static IsoSprite roofTileCache;
 static int roofTilePlaceFloorIndexCache = 0;
 static std::string invisFloor = "invisible_01_0";
 private static Map<Integer, String> roofGroups = std::make_unique<HashMap<>>();
 private static IsoRoofFixer.PlaceFloorInfo[] placeFloorInfos = new IsoRoofFixer.PlaceFloorInfo[10000];
 static int floorInfoIndex = 0;
 private static IsoGridSquare[] sqCache;
 static IsoRoom workingRoom;
 private static int[] interiorAirSpaces;
 static const int I_UNCHECKED = 0;
 static const int I_TRUE = 1;
 static const int I_FALSE = 2;

 static void ensureCapacityFloorInfos() {
 if (floorInfoIndex == placeFloorInfos.length) {
 IsoRoofFixer.PlaceFloorInfo[] placeFloorInfosx = placeFloorInfos;
 placeFloorInfos = new IsoRoofFixer.PlaceFloorInfo[placeFloorInfos.length + 400];
 System.arraycopy(placeFloorInfosx, 0, placeFloorInfos, 0, placeFloorInfosx.length);
 }
 }

 static void setRoofTileCache(IsoObject object) {
 IsoSprite sprite = object != nullptr ? object.sprite : nullptr;
 if (roofTileCache != sprite) {
 roofTileCache = sprite;
 roofTilePlaceFloorIndexCache = 0;
 if (sprite != nullptr && sprite.getProperties() != nullptr && sprite.getProperties().Val("RoofGroup") != nullptr) {
 try {
 int int0 = Integer.parseInt(sprite.getProperties().Val("RoofGroup"));
 if (roofGroups.containsKey(int0) {
 roofTilePlaceFloorIndexCache = int0;
 }
 } catch (Exception exception) {
 }
 }

 roofTileGlassCacheDirty = true;
 }
 }

 static bool isRoofTileCacheGlass() {
 if (roofTileGlassCacheDirty) {
 roofTileIsGlass = false;
 if (roofTileCache != nullptr) {
 PropertyContainer propertyContainer = roofTileCache.getProperties();
 if (propertyContainer != nullptr) {
 std::string string = propertyContainer.Val("Material");
 roofTileIsGlass = string != nullptr && string.equalsIgnoreCase("glass");
 }
 }

 roofTileGlassCacheDirty = false;
 }

 return roofTileIsGlass;
 }

 static void FixRoofsAt(IsoGridSquare square) {
 try {
 FixRoofsPerRoomAt(square);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 static void FixRoofsPerRoomAt(IsoGridSquare square0) {
 floorInfoIndex = 0;
 if (square0.getZ() > 0 && !square0.TreatAsSolidFloor() && square0.getRoom() == nullptr) {
 IsoRoom room = getRoomBelow(square0);
 if (room != nullptr && !room.def.isRoofFixed()) {
 resetInteriorSpaceCache();
 workingRoom = room;
 std::vector arrayList = room.getSquares();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoGridSquare square1 = (IsoGridSquare)arrayList.get(int0);
 IsoGridSquare square2 = getRoofFloorForColumn(square1);
 if (square2 != nullptr) {
 ensureCapacityFloorInfos();
 placeFloorInfos[floorInfoIndex++].set(square2, roofTilePlaceFloorIndexCache);
 }
 }

 room.def.setRoofFixed(true);
 }
 }

 for (int int1 = 0; int1 < floorInfoIndex; int1++) {
 placeFloorInfos[int1].square.addFloor(roofGroups.get(placeFloorInfos[int1].floorType);
 }
 }

 static void clearSqCache() {
 for (int int0 = 0; int0 < sqCache.length; int0++) {
 sqCache[int0] = nullptr;
 }
 }

 static IsoGridSquare getRoofFloorForColumn(IsoGridSquare square0) {
 if (square0.empty()) {
 return nullptr;
 } else {
 IsoCell cell = IsoCell.getInstance();
 int int0 = 0;
 bool boolean0 = false;
 int int1 = 7;

 while (true) {
 label163: {
 if (int1 >= square0.getZ() + 1) {
 IsoGridSquare square1 = cell.getGridSquare(square0.x, square0.y, int1);
 if (square1.empty()) {
 if (int1 == square0.getZ() + 1 && int1 > 0 && !isStairsBelow(square0.x, square0.y, int1) {
 square1 = IsoGridSquare.getNew(cell, nullptr, square0.x, square0.y, int1);
 cell.ConnectNewSquare(square1, false);
 square1.EnsureSurroundNotNull();
 square1.RecalcAllWithNeighbours(true);
 sqCache[int0++] = square1;
 }

 boolean0 = true;
 break label163;
 }

 if (square1.TreatAsSolidFloor()) {
 if (square1.getRoom() == nullptr) {
 IsoObject object0 = square1.getFloor();
 if (object0.empty() || !isObjectRoof(object0) || object0.getProperties() == nullptr) {
 break;
 }

 PropertyContainer propertyContainer = object0.getProperties();
 if (propertyContainer.Is(IsoFlagType.FloorHeightOneThird) || propertyContainer.Is(IsoFlagType.FloorHeightTwoThirds) {
 break;
 }

 IsoGridSquare square2 = cell.getGridSquare(square0.x, square0.y, int1 - 1);
 if (square2.empty() || square2.getRoom() != nullptr) {
 break;
 }

 boolean0 = false;
 break label163;
 }

 if (boolean0) {
 square1 = IsoGridSquare.getNew(cell, nullptr, square0.x, square0.y, int1 + 1);
 cell.ConnectNewSquare(square1, false);
 square1.EnsureSurroundNotNull();
 square1.RecalcAllWithNeighbours(true);
 sqCache[int0++] = square1;
 }
 } else if (!square1.HasStairsBelow()) {
 boolean0 = false;
 sqCache[int0++] = square1;
 break label163;
 }
 }

 if (int0 == 0) {
 return nullptr;
 }

 for (int int2 = 0; int2 < int0; int2++) {
 IsoGridSquare square3 = sqCache[int2];
 if (square3.getRoom() == nullptr && isInteriorAirSpace(square3.getX(), square3.getY(), square3.getZ())) {
 return nullptr;
 }

 if (isRoofAt(square3, true) {
 return square3;
 }

 for (int int3 = square3.x - 3; int3 <= square3.x + 3; int3++) {
 for (int int4 = square3.y - 3; int4 <= square3.y + 3; int4++) {
 if (int3 != square3.x || int4 != square3.y) {
 IsoGridSquare square4 = cell.getGridSquare(int3, int4, square3.z);
 if (square4 != nullptr) {
 for (int int5 = 0; int5 < square4.getObjects().size(); int5++) {
 IsoObject object1 = square4.getObjects().get(int5);
 if (isObjectRoofNonFlat(object1) {
 setRoofTileCache(object1);
 return square3;
 }
 }

 IsoGridSquare square5 = cell.getGridSquare(square4.x, square4.y, square4.z + 1);
 if (square5 != nullptr && square5.getObjects().size() > 0) {
 for (int int6 = 0; int6 < square5.getObjects().size(); int6++) {
 IsoObject object2 = square5.getObjects().get(int6);
 if (isObjectRoofFlatFloor(object2) {
 setRoofTileCache(object2);
 return square3;
 }
 }
 }
 }
 }
 }
 }
 }

 return nullptr;
 }

 int1--;
 }

 return nullptr;
 }
 }

 static void FixRoofsPerTileAt(IsoGridSquare square) {
 if (square.getZ() > 0
 && !square.TreatAsSolidFloor()
 && square.getRoom() == nullptr
 && hasRoomBelow(square)
 && (isRoofAt(square, true) || scanIsRoofAt(square, true) {
 if (isRoofTileCacheGlass()) {
 square.addFloor(invisFloor);
 } else {
 square.addFloor("carpentry_02_58");
 }
 }
 }

 static bool scanIsRoofAt(IsoGridSquare square0, bool boolean0) {
 if (square0.empty()) {
 return false;
 } else {
 for (int int0 = square0.x - 3; int0 <= square0.x + 3; int0++) {
 for (int int1 = square0.y - 3; int1 <= square0.y + 3; int1++) {
 if (int0 != square0.x || int1 != square0.y) {
 IsoGridSquare square1 = square0.getCell().getGridSquare(int0, int1, square0.z);
 if (square1 != nullptr && isRoofAt(square1, boolean0) {
 return true;
 }
 }
 }
 }

 return false;
 }
 }

 static bool isRoofAt(IsoGridSquare square0, bool boolean0) {
 if (square0.empty()) {
 return false;
 } else {
 for (int int0 = 0; int0 < square0.getObjects().size(); int0++) {
 IsoObject object0 = square0.getObjects().get(int0);
 if (isObjectRoofNonFlat(object0) {
 setRoofTileCache(object0);
 return true;
 }
 }

 if (boolean0) {
 IsoGridSquare square1 = square0.getCell().getGridSquare(square0.x, square0.y, square0.z + 1);
 if (square1 != nullptr && square1.getObjects().size() > 0) {
 for (int int1 = 0; int1 < square1.getObjects().size(); int1++) {
 IsoObject object1 = square1.getObjects().get(int1);
 if (isObjectRoofFlatFloor(object1) {
 setRoofTileCache(object1);
 return true;
 }
 }
 }
 }

 return false;
 }
 }

 static bool isObjectRoof(IsoObject object) {
 return object != nullptr
 && (object.getType() == IsoObjectType.WestRoofT || object.getType() == IsoObjectType.WestRoofB || object.getType() == IsoObjectType.WestRoofM);
 }

 static bool isObjectRoofNonFlat(IsoObject object) {
 if (isObjectRoof(object) {
 PropertyContainer propertyContainer = object.getProperties();
 if (propertyContainer != nullptr) {
 return !propertyContainer.Is(IsoFlagType.solidfloor)
 || propertyContainer.Is(IsoFlagType.FloorHeightOneThird)
 || propertyContainer.Is(IsoFlagType.FloorHeightTwoThirds);
 }
 }

 return false;
 }

 static bool isObjectRoofFlatFloor(IsoObject object) {
 if (isObjectRoof(object) {
 PropertyContainer propertyContainer = object.getProperties();
 if (propertyContainer != nullptr && propertyContainer.Is(IsoFlagType.solidfloor) {
 return !propertyContainer.Is(IsoFlagType.FloorHeightOneThird) && !propertyContainer.Is(IsoFlagType.FloorHeightTwoThirds);
 }
 }

 return false;
 }

 static bool hasRoomBelow(IsoGridSquare square) {
 return getRoomBelow();
 }

 static IsoRoom getRoomBelow(IsoGridSquare square0) {
 if (square0.empty()) {
 return nullptr;
 } else {
 for (int int0 = square0.z - 1; int0 >= 0; int0--) {
 IsoGridSquare square1 = square0.getCell().getGridSquare(square0.x, square0.y, int0);
 if (square1 != nullptr) {
 if (square1.TreatAsSolidFloor() && square1.getRoom() == nullptr) {
 return nullptr;
 }

 if (square1.getRoom() != nullptr) {
 return square1.getRoom();
 }
 }
 }

 return nullptr;
 }
 }

 static bool isStairsBelow(int int1, int int2, int int0) {
 if (int0 == 0) {
 return false;
 } else {
 IsoCell cell = IsoCell.getInstance();
 IsoGridSquare square = cell.getGridSquare(int1, int2, int0 - 1);
 return square != nullptr && square.HasStairs();
 }
 }

 static void resetInteriorSpaceCache() {
 for (int int0 = 0; int0 < interiorAirSpaces.length; int0++) {
 interiorAirSpaces[int0] = 0;
 }
 }

 static bool isInteriorAirSpace(int var0, int var1, int int0) {
 if (interiorAirSpaces[int0] != 0) {
 return interiorAirSpaces[int0] == 1;
 } else {
 std::vector arrayList = workingRoom.getSquares();
 bool boolean0 = false;
 if (arrayList.size() > 0 && int0 > ((IsoGridSquare)arrayList.get(0).getZ()) {
 for (int int1 = 0; int1 < workingRoom.rects.size(); int1++) {
 RoomDef.RoomRect roomRect = workingRoom.rects.get(int1);

 for (int int2 = roomRect.getX(); int2 < roomRect.getX2(); int2++) {
 if (hasRailing(int2, roomRect.getY(), int0, IsoDirections.N) || hasRailing(int2, roomRect.getY2() - 1, int0, IsoDirections.S) {
 boolean0 = true;
 break;
 }
 }

 if (boolean0) {
 break;
 }

 for (int int3 = roomRect.getY(); int3 < roomRect.getY2(); int3++) {
 if (hasRailing(roomRect.getX(), int3, int0, IsoDirections.W) || hasRailing(roomRect.getX2() - 1, int3, int0, IsoDirections.E) {
 boolean0 = true;
 break;
 }
 }
 }
 }

 interiorAirSpaces[int0] = boolean0 ? 1 : 2;
 return boolean0;
 }
 }

 static bool hasRailing(int int0, int int1, int int2, IsoDirections directions) {
 IsoCell cell = IsoCell.getInstance();
 IsoGridSquare square = cell.getGridSquare(int0, int1, int2);
 if (square.empty()) {
 return false;
 } else {
 switch (directions) {
 case N:
 return square.isHoppableTo(cell.getGridSquare(int0, int1 - 1, int2);
 case E:
 return square.isHoppableTo(cell.getGridSquare(int0 + 1, int1, int2);
 case S:
 return square.isHoppableTo(cell.getGridSquare(int0, int1 + 1, int2);
 case W:
 return square.isHoppableTo(cell.getGridSquare(int0 - 1, int1, int2);
 default:
 return false;
 }
 }
 }

 static {
 roofGroups.put(0, "carpentry_02_57");
 roofGroups.put(1, "roofs_01_22");
 roofGroups.put(2, "roofs_01_54");
 roofGroups.put(3, "roofs_02_22");
 roofGroups.put(4, invisFloor);
 roofGroups.put(5, "roofs_03_22");
 roofGroups.put(6, "roofs_03_54");
 roofGroups.put(7, "roofs_04_22");
 roofGroups.put(8, "roofs_04_54");
 roofGroups.put(9, "roofs_05_22");
 roofGroups.put(10, "roofs_05_54");

 for (int int0 = 0; int0 < placeFloorInfos.length; int0++) {
 placeFloorInfos[int0] = new IsoRoofFixer.PlaceFloorInfo();
 }

 sqCache = new IsoGridSquare[8];
 interiorAirSpaces = new int[8];
 }

 private static class PlaceFloorInfo {
 IsoGridSquare square;
 int floorType;

 void set(IsoGridSquare squarex, int int0) {
 this->square = squarex;
 this->floorType = int0;
 }
 }
}
} // namespace iso
} // namespace zombie
