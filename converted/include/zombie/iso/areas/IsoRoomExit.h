#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"

namespace zombie {
namespace iso {
namespace areas {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoRoomExit {
public:
 static std::string ThiggleQ = "";
 IsoRoom From;
 int layer;
 IsoRoomExit To;
 public IsoRoomExit.ExitType type = IsoRoomExit.ExitType.Door;
 int x;
 int y;

 public IsoRoomExit(IsoRoomExit roomExit1, int int1, int int2, int int0) {
 this->To = roomExit1;
 this->To.To = this;
 this->layer = int0;
 this->x = int1;
 this->y = int2;
 }

 public IsoRoomExit(IsoRoom room, IsoRoomExit roomExit1, int int1, int int2, int int0) {
 this->From = room;
 this->To = roomExit1;
 this->To.To = this;
 this->layer = int0;
 this->x = int1;
 this->y = int2;
 }

 public IsoRoomExit(IsoRoom room, int int1, int int2, int int0) {
 this->From = room;
 this->layer = int0;
 this->x = int1;
 this->y = int2;
 }

 IsoObject getDoor(IsoCell cell) {
 IsoGridSquare square = cell.getGridSquare(this->x, this->y, this->layer);
 if (square != nullptr) {
 if (square.getSpecialObjects().size() > 0 && square.getSpecialObjects().get(0) instanceof IsoDoor) {
 return (IsoDoor)square.getSpecialObjects().get(0);
 }

 if (square.getSpecialObjects().size() > 0
 && square.getSpecialObjects().get(0) instanceof IsoThumpable
 && ((IsoThumpable)square.getSpecialObjects().get(0).isDoor) {
 return (IsoThumpable)square.getSpecialObjects().get(0);
 }
 }

 square = cell.getGridSquare(this->x, this->y + 1, this->layer);
 if (square != nullptr) {
 if (square.getSpecialObjects().size() > 0 && square.getSpecialObjects().get(0) instanceof IsoDoor) {
 return (IsoDoor)square.getSpecialObjects().get(0);
 }

 if (square.getSpecialObjects().size() > 0
 && square.getSpecialObjects().get(0) instanceof IsoThumpable
 && ((IsoThumpable)square.getSpecialObjects().get(0).isDoor) {
 return (IsoThumpable)square.getSpecialObjects().get(0);
 }
 }

 square = cell.getGridSquare(this->x + 1, this->y, this->layer);
 if (square != nullptr) {
 if (square.getSpecialObjects().size() > 0 && square.getSpecialObjects().get(0) instanceof IsoDoor) {
 return (IsoDoor)square.getSpecialObjects().get(0);
 }

 if (square.getSpecialObjects().size() > 0
 && square.getSpecialObjects().get(0) instanceof IsoThumpable
 && ((IsoThumpable)square.getSpecialObjects().get(0).isDoor) {
 return (IsoThumpable)square.getSpecialObjects().get(0);
 }
 }

 return nullptr;
 }

 static {
 ThiggleQ = ThiggleQ + "D";
 ThiggleQ = ThiggleQ + ":";
 ThiggleQ = ThiggleQ + "/";
 ThiggleQ = ThiggleQ + "Dro";
 ThiggleQ = ThiggleQ + "pbox";
 ThiggleQ = ThiggleQ + "/";
 ThiggleQ = ThiggleQ + "Zom";
 ThiggleQ = ThiggleQ + "boid";
 ThiggleQ = ThiggleQ + "/";
 ThiggleQ = ThiggleQ + "zom";
 ThiggleQ = ThiggleQ + "bie";
 ThiggleQ = ThiggleQ + "/";
 ThiggleQ = ThiggleQ + "bui";
 ThiggleQ = ThiggleQ + "ld";
 ThiggleQ = ThiggleQ + "/";
 ThiggleQ = ThiggleQ + "cla";
 ThiggleQ = ThiggleQ + "sses/";
 }

 public static enum ExitType {
 Door,
 Window;
 }
}
} // namespace areas
} // namespace iso
} // namespace zombie
