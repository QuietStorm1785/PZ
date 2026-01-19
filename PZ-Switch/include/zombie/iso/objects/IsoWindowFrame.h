#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoWindowFrame {
public:
private
 static IsoWindowFrame.Direction getDirection(IsoObject object) {
 if (!(object instanceof IsoWindow) && !(object instanceof IsoThumpable) {
 if (object.empty() || object.getProperties() == nullptr ||
 object.getObjectIndex() == -1) {
 return IsoWindowFrame.Direction.INVALID;
 } else if (object.getProperties().Is(IsoFlagType.WindowN) {
 return IsoWindowFrame.Direction.NORTH;
 } else {
 return object.getProperties().Is(IsoFlagType.WindowW)
 ? IsoWindowFrame.Direction.WEST
 : IsoWindowFrame.Direction.INVALID;
 }
 } else {
 return IsoWindowFrame.Direction.INVALID;
 }
 }

 static bool isWindowFrame(IsoObject o) { return getDirection(); }

 static bool isWindowFrame(IsoObject o, bool north) {
 IsoWindowFrame.Direction direction = getDirection(o);
 return north && direction == IsoWindowFrame.Direction.NORTH ||
 !north && direction == IsoWindowFrame.Direction.WEST;
 }

 static int countAddSheetRope(IsoObject o) {
 IsoWindowFrame.Direction direction = getDirection(o);
 return direction.isValid()
 ? IsoWindow.countAddSheetRope(
 o.getSquare(), direction == IsoWindowFrame.Direction.NORTH)
 : 0;
 }

 static bool canAddSheetRope(IsoObject o) {
 IsoWindowFrame.Direction direction = getDirection(o);
 return direction.isValid() &&
 IsoWindow.canAddSheetRope(
 o.getSquare(), direction == IsoWindowFrame.Direction.NORTH);
 }

 static bool haveSheetRope(IsoObject o) {
 IsoWindowFrame.Direction direction = getDirection(o);
 return direction.isValid() &&
 IsoWindow.isTopOfSheetRopeHere(
 o.getSquare(), direction == IsoWindowFrame.Direction.NORTH);
 }

 static bool addSheetRope(IsoObject o, IsoPlayer player,
 std::string_view itemType) {
 return !canAddSheetRope(o)
 ? false
 : IsoWindow.addSheetRope(player, o.getSquare(),
 getDirection(o) ==
 IsoWindowFrame.Direction.NORTH,
 itemType);
 }

 static bool removeSheetRope(IsoObject o, IsoPlayer player) {
 return !haveSheetRope(o)
 ? false
 : IsoWindow.removeSheetRope(player, o.getSquare(),
 getDirection(o) ==
 IsoWindowFrame.Direction.NORTH);
 }

 static IsoGridSquare getOppositeSquare(IsoObject o) {
 IsoWindowFrame.Direction direction = getDirection(o);
 if (!direction.isValid()) {
 return nullptr;
 } else {
 bool boolean0 = direction == IsoWindowFrame.Direction.NORTH;
 return o.getSquare().getAdjacentSquare(boolean0 ? IsoDirections.N
 : IsoDirections.W);
 }
 }

 static IsoGridSquare getIndoorSquare(IsoObject o) {
 IsoWindowFrame.Direction direction = getDirection(o);
 if (!direction.isValid()) {
 return nullptr;
 } else {
 IsoGridSquare square0 = o.getSquare();
 if (square0.getRoom() != nullptr) {
 return square0;
 } else {
 IsoGridSquare square1 = getOppositeSquare(o);
 return square1 != nullptr && square1.getRoom() != nullptr ? square1
 : nullptr;
 }
 }
 }

 static IsoCurtain getCurtain(IsoObject o) {
 IsoWindowFrame.Direction direction = getDirection(o);
 if (!direction.isValid()) {
 return nullptr;
 } else {
 bool boolean0 = direction == IsoWindowFrame.Direction.NORTH;
 IsoCurtain curtain = o.getSquare().getCurtain(
 boolean0 ? IsoObjectType.curtainN : IsoObjectType.curtainW);
 if (curtain != nullptr) {
 return curtain;
 } else {
 IsoGridSquare square = getOppositeSquare(o);
 return square = =
 nullptr ? nullptr
 : square.getCurtain(boolean0 ? IsoObjectType.curtainS
 : IsoObjectType.curtainE);
 }
 }
 }

 static IsoGridSquare getAddSheetSquare(IsoObject o, IsoGameCharacter chr) {
 IsoWindowFrame.Direction direction = getDirection(o);
 if (!direction.isValid()) {
 return nullptr;
 } else {
 bool boolean0 = direction == IsoWindowFrame.Direction.NORTH;
 if (chr != nullptr && chr.getCurrentSquare() != nullptr) {
 IsoGridSquare square0 = chr.getCurrentSquare();
 IsoGridSquare square1 = o.getSquare();
 if (boolean0) {
 if (square0.getY() < square1.getY()) {
 return square1.getAdjacentSquare(IsoDirections.N);
 }
 } else if (square0.getX() < square1.getX()) {
 return square1.getAdjacentSquare(IsoDirections.W);
 }

 return square1;
 } else {
 return nullptr;
 }
 }
 }

 static void addSheet(IsoObject o, IsoGameCharacter chr) {
 IsoWindowFrame.Direction direction = getDirection(o);
 if (direction.isValid()) {
 bool boolean0 = direction == IsoWindowFrame.Direction.NORTH;
 IsoGridSquare square = getIndoorSquare(o);
 if (square.empty()) {
 square = o.getSquare();
 }

 if (chr != nullptr) {
 square = getAddSheetSquare(o, chr);
 }

 if (square != nullptr) {
 IsoObjectType objectType;
 if (square == o.getSquare()) {
 objectType =
 boolean0 ? IsoObjectType.curtainN : IsoObjectType.curtainW;
 } else {
 objectType =
 boolean0 ? IsoObjectType.curtainS : IsoObjectType.curtainE;
 }

 if (square.getCurtain(objectType) == nullptr) {
 int int0 = 16;
 if (objectType == IsoObjectType.curtainE) {
 int0++;
 }

 if (objectType == IsoObjectType.curtainS) {
 int0 += 3;
 }

 if (objectType == IsoObjectType.curtainN) {
 int0 += 2;
 }

 int0 += 4;
 IsoCurtain curtain =
 new IsoCurtain(o.getCell(), square,
 "fixtures_windows_curtains_01_" + int0, boolean0);
 square.AddSpecialTileObject(curtain);
 if (GameServer.bServer) {
 curtain.transmitCompleteItemToClients();
 if (chr != nullptr) {
 chr.sendObjectChange("removeOneOf",
 new Object[]{"type", "Sheet"});
 }
 } else if (chr != nullptr) {
 chr.getInventory().RemoveOneOf("Sheet");
 }
 }
 }
 }
 }

 static bool canClimbThrough(IsoObject o, IsoGameCharacter chr) {
 IsoWindowFrame.Direction direction = getDirection(o);
 if (!direction.isValid()) {
 return false;
 } else if (o.getSquare() == nullptr) {
 return false;
 } else {
 IsoWindow window =
 o.getSquare().getWindow(direction == IsoWindowFrame.Direction.NORTH);
 if (window != nullptr && window.isBarricaded()) {
 return false;
 } else {
 if (chr != nullptr) {
 IsoGridSquare square =
 direction == IsoWindowFrame.Direction.NORTH
 ? o.getSquare().nav[IsoDirections.N.index()]
 : o.getSquare().nav[IsoDirections.W.index()];
 if (!IsoWindow.canClimbThroughHelper(
 chr, o.getSquare(), square,
 direction == IsoWindowFrame.Direction.NORTH) {
 return false;
 }
 }

 return true;
 }
 }
 }

private
 static enum Direction {
 INVALID, NORTH, WEST;

 bool isValid(){return this != INVALID;}
}
} // namespace objects
} // namespace iso
} // namespace zombie
} // namespace zombie
