#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


enum class IsoDirections {
 N(0),
 NW(1),
 W(2),
 SW(3),
 S(4),
 SE(5),
 E(6),
 NE(7),
 Max(8);

 private static IsoDirections[] VALUES = values();
 private static IsoDirections[][] directionLookup;
 static const Vector2 temp = new Vector2();
 const int index;

 private IsoDirections(int int1) {
 this->index = int1;
 }

 static IsoDirections fromIndex(int _index) {
 while (_index < 0) {
 _index += 8;
 }

 _index %= 8;
 return VALUES[_index];
 }

 IsoDirections RotLeft(int time) {
 IsoDirections directions = RotLeft(this);

 for (int int0 = 0; int0 < time - 1; int0++) {
 directions = RotLeft(directions);
 }

 return directions;
 }

 IsoDirections RotRight(int time) {
 IsoDirections directions = RotRight(this);

 for (int int0 = 0; int0 < time - 1; int0++) {
 directions = RotRight(directions);
 }

 return directions;
 }

 IsoDirections RotLeft() {
 return RotLeft();
 }

 IsoDirections RotRight() {
 return RotRight();
 }

 static IsoDirections RotLeft(IsoDirections dir) {
 switch (dir) {
 case NE:
 return N;
 case N:
 return NW;
 case NW:
 return W;
 case W:
 return SW;
 case SW:
 return S;
 case S:
 return SE;
 case SE:
 return E;
 case E:
 return NE;
 default:
 return Max;
 }
 }

 static IsoDirections RotRight(IsoDirections dir) {
 switch (dir) {
 case NE:
 return E;
 case N:
 return NE;
 case NW:
 return N;
 case W:
 return NW;
 case SW:
 return W;
 case S:
 return SW;
 case SE:
 return S;
 case E:
 return SE;
 default:
 return Max;
 }
 }

 static void generateTables() {
 directionLookup = new IsoDirections[200][200];

 for (int int0 = 0; int0 < 200; int0++) {
 for (int int1 = 0; int1 < 200; int1++) {
 int int2 = int0 - 100;
 int int3 = int1 - 100;
 float float0 = int2 / 100.0F;
 float float1 = int3 / 100.0F;
 Vector2 vector = new Vector2(float0, float1);
 vector.normalize();
 directionLookup[int0][int1] = fromAngleActual(vector);
 }
 }
 }

 static IsoDirections fromAngleActual(Vector2 angle) {
 temp.x = angle.x;
 temp.y = angle.y;
 temp.normalize();
 float float0 = temp.getDirectionNeg();
 float float1 = (float) (Math.PI / 4);
 float float2 = (float) (Math.PI * 2);
 float2 = (float)(float2 + Math.toRadians(112.5);

 for (int int0 = 0; int0 < 8; int0++) {
 float2 += float1;
 if (float0 >= float2 && float0 <= float2 + float1
 || float0 + (float) (Math.PI * 2) >= float2 && float0 + (float) (Math.PI * 2) <= float2 + float1
 || float0 - (float) (Math.PI * 2) >= float2 && float0 - (float) (Math.PI * 2) <= float2 + float1) {
 return fromIndex();
 }

 if (float2 > Math.PI * 2) {
 float2 = (float)(float2 - (Math.PI * 2);
 }
 }

 if (temp.x > 0.5F) {
 if (temp.y < -0.5F) {
 return NE;
 } else {
 return temp.y > 0.5F ? SE : E;
 }
 } else if (temp.x < -0.5F) {
 if (temp.y < -0.5F) {
 return NW;
 } else {
 return temp.y > 0.5F ? SW : W;
 }
 } else if (temp.y < -0.5F) {
 return N;
 } else {
 return temp.y > 0.5F ? S : N;
 }
 }

 static IsoDirections fromAngle(float angleRadians) {
 float float0 = (float)Math.cos(angleRadians);
 float float1 = (float)Math.sin(angleRadians);
 return fromAngle();
 }

 static IsoDirections fromAngle(Vector2 angle) {
 return fromAngle();
 }

 static IsoDirections fromAngle(float angleX, float angleY) {
 temp.x = angleX;
 temp.y = angleY;
 if (temp.getLengthSquared() != 1.0F) {
 temp.normalize();
 }

 if (directionLookup == nullptr) {
 generateTables();
 }

 int int0 = (int)((temp.x + 1.0F) * 100.0F);
 int int1 = (int)((temp.y + 1.0F) * 100.0F);
 if (int0 >= 200) {
 int0 = 199;
 }

 if (int1 >= 200) {
 int1 = 199;
 }

 if (int0 < 0) {
 int0 = 0;
 }

 if (int1 < 0) {
 int1 = 0;
 }

 return directionLookup[int0][int1];
 }

 static IsoDirections cardinalFromAngle(Vector2 angle) {
 bool boolean0 = angle.getX() >= angle.getY();
 bool boolean1 = angle.getX() > -angle.getY();
 if (boolean0) {
 return boolean1 ? E : N;
 } else {
 return boolean1 ? S : W;
 }
 }

 static IsoDirections reverse(IsoDirections dir) {
 switch (dir) {
 case NE:
 return SW;
 case N:
 return S;
 case NW:
 return SE;
 case W:
 return E;
 case SW:
 return NE;
 case S:
 return N;
 case SE:
 return NW;
 case E:
 return W;
 default:
 return Max;
 }
 }

 int index() {
 return this->index % 8;
 }

 std::string toCompassString() {
 switch (this->index) {
 case 0:
 return "9";
 case 1:
 return "8";
 case 2:
 return "7";
 case 3:
 return "4";
 case 4:
 return "1";
 case 5:
 return "2";
 case 6:
 return "3";
 case 7:
 return "6";
 default:
 return "";
 }
 }

 Vector2 ToVector() {
 switch (this) {
 case NE:
 temp.x = 1.0F;
 temp.y = -1.0F;
 break;
 case N:
 temp.x = 0.0F;
 temp.y = -1.0F;
 break;
 case NW:
 temp.x = -1.0F;
 temp.y = -1.0F;
 break;
 case W:
 temp.x = -1.0F;
 temp.y = 0.0F;
 break;
 case SW:
 temp.x = -1.0F;
 temp.y = 1.0F;
 break;
 case S:
 temp.x = 0.0F;
 temp.y = 1.0F;
 break;
 case SE:
 temp.x = 1.0F;
 temp.y = 1.0F;
 break;
 case E:
 temp.x = 1.0F;
 temp.y = 0.0F;
 }

 temp.normalize();
 return temp;
 }

 float toAngle() {
 float float0 = (float) (Math.PI / 4);
 switch (this) {
 case NE:
 return float0 * 7.0F;
 case N:
 return float0 * 0.0F;
 case NW:
 return float0 * 1.0F;
 case W:
 return float0 * 2.0F;
 case SW:
 return float0 * 3.0F;
 case S:
 return float0 * 4.0F;
 case SE:
 return float0 * 5.0F;
 case E:
 return float0 * 6.0F;
 default:
 return 0.0F;
 }
 }

 static IsoDirections getRandom() {
 return fromIndex();
 }
}
} // namespace iso
} // namespace zombie
