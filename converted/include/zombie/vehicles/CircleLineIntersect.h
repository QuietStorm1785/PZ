#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "org/lwjgl/util/vector/Vector2f.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/physics/CarController.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/debug/LineDrawer.h"

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CircleLineIntersect {
public:
 public static CircleLineIntersect.Collideresult checkforcecirclescollidetime(
 List<CircleLineIntersect.ForceCircle> list,
 ArrayList<CircleLineIntersect.StaticLine> arrayList0,
 double[] doubles2,
 boolean[] booleans,
 boolean boolean0
 ) {
 CircleLineIntersect.PointVector[] pointVectors = new CircleLineIntersect.PointVector[list.size()];
 double[] doubles0 = new double[list.size()];
 CircleLineIntersect.Collideclassindex[] collideclassindexs = new CircleLineIntersect.Collideclassindex[list.size()];
 double[] doubles1 = new double[list.size()];

 for (int int0 = list.size() - 1; int0 >= 0; int0--) {
 doubles0[int0] = -1.0;
 collideclassindexs[int0] = new CircleLineIntersect.Collideclassindex();
 pointVectors[int0] = (CircleLineIntersect.PointVector)list.get(int0);
 doubles1[int0] = 1.0;
 }

 for (int int1 = Math.min(list.size(), doubles2.length) - 1; int1 >= 0; int1--) {
 if (boolean0 || booleans[int1]) {
 CircleLineIntersect.ForceCircle forceCircle0 = (CircleLineIntersect.ForceCircle)list.get(int1);

 for (int int2 = arrayList0.size() - 1; int2 >= 0; int2--) {
 CircleLineIntersect.StaticLine staticLine = (CircleLineIntersect.StaticLine)arrayList0.get(int2);
 CircleLineIntersect.Point point0 = CircleLineIntersect.VectorMath.closestpointonline(
 staticLine.getX1(), staticLine.getY1(), staticLine.getX2(), staticLine.getY2(), forceCircle0.getX(), forceCircle0.getY()
 );
 double double0 = CircleLineIntersect.Point.distanceSq(point0.getX(), point0.getY(), forceCircle0.getX(), forceCircle0.getY());
 if (double0 < forceCircle0.getRadiusSq()) {
 double double1 = 0.0;
 double double2 = 0.0;
 if (double0 == 0.0) {
 CircleLineIntersect.Point point1 = CircleLineIntersect.Point.midpoint(staticLine.getP1(), staticLine.getP2());
 double double3 = staticLine.getP1().distance(staticLine.getP2());
 double double4 = forceCircle0.distanceSq(point1);
 if (double4 < Math.pow(forceCircle0.getRadius() + double3 / 2.0, 2.0) {
 if (double4 != 0.0) {
 double double5 = forceCircle0.distance(point1);
 double double6 = (forceCircle0.getX() - point1.getX()) / double5;
 double double7 = (forceCircle0.getY() - point1.getY()) / double5;
 double1 = point1.getX() + (forceCircle0.getRadius() + double3 / 2.0) * double6;
 double2 = point1.getY() + (forceCircle0.getRadius() + double3 / 2.0) * double7;
 } else {
 double1 = forceCircle0.getX();
 double2 = forceCircle0.getY();
 }

 if (doubles0[int1] == -1.0) {
 pointVectors[int1] = new CircleLineIntersect.PointVector(double1, double2);
 } else {
 pointVectors[int1].setPoint(double1, double2);
 }

 if (doubles0[int1] == 0.0) {
 collideclassindexs[int1].addCollided(staticLine, int2, forceCircle0.getVector());
 } else {
 collideclassindexs[int1].setCollided(staticLine, int2, forceCircle0.getVector());
 }

 doubles0[int1] = 0.0;
 continue;
 }

 if (double4 == Math.pow(forceCircle0.getRadius() + double3 / 2.0, 2.0) && forceCircle0.getLength() == 0.0) {
 continue;
 }
 } else {
 if (Math.min(staticLine.getX1(), staticLine.getX2()) <= point0.getX()
 && point0.getX() <= Math.max(staticLine.getX1(), staticLine.getX2())
 && Math.min(staticLine.getY1(), staticLine.getY2()) <= point0.getY()
 && point0.getY() <= Math.max(staticLine.getY1(), staticLine.getY2())) {
 double double8 = Math.sqrt(double0);
 double double9 = (forceCircle0.getX() - point0.getX()) / double8;
 double double10 = (forceCircle0.getY() - point0.getY()) / double8;
 double1 = point0.getX() + forceCircle0.getRadius() * double9;
 double2 = point0.getY() + forceCircle0.getRadius() * double10;
 if (doubles0[int1] == -1.0) {
 pointVectors[int1] = new CircleLineIntersect.PointVector(double1, double2);
 } else {
 pointVectors[int1].setPoint(double1, double2);
 }

 if (doubles0[int1] == 0.0) {
 collideclassindexs[int1].addCollided(staticLine, int2, forceCircle0.getVector());
 } else {
 collideclassindexs[int1].setCollided(staticLine, int2, forceCircle0.getVector());
 }

 doubles0[int1] = 0.0;
 continue;
 }

 if (CircleLineIntersect.Point.distanceSq(forceCircle0.getX(), forceCircle0.getY(), staticLine.getX1(), staticLine.getY1())
 < forceCircle0.getRadiusSq()) {
 double double11 = CircleLineIntersect.Point.distance(
 forceCircle0.getX(), forceCircle0.getY(), staticLine.getX1(), staticLine.getY1()
 );
 double double12 = (forceCircle0.getX() - staticLine.getX1()) / double11;
 double double13 = (forceCircle0.getY() - staticLine.getY1()) / double11;
 double1 = staticLine.getX1() + forceCircle0.getRadius() * double12;
 double2 = staticLine.getY1() + forceCircle0.getRadius() * double13;
 if (doubles0[int1] == -1.0) {
 pointVectors[int1] = new CircleLineIntersect.PointVector(double1, double2);
 } else {
 pointVectors[int1].setPoint(double1, double2);
 }

 if (doubles0[int1] == 0.0) {
 collideclassindexs[int1].addCollided(staticLine, int2, forceCircle0.getVector());
 } else {
 collideclassindexs[int1].setCollided(staticLine, int2, forceCircle0.getVector());
 }

 doubles0[int1] = 0.0;
 continue;
 }

 if (CircleLineIntersect.Point.distanceSq(forceCircle0.getX(), forceCircle0.getY(), staticLine.getX2(), staticLine.getY2())
 < forceCircle0.getRadiusSq()) {
 double double14 = CircleLineIntersect.Point.distance(
 forceCircle0.getX(), forceCircle0.getY(), staticLine.getX2(), staticLine.getY2()
 );
 double double15 = (forceCircle0.getX() - staticLine.getX2()) / double14;
 double double16 = (forceCircle0.getY() - staticLine.getY2()) / double14;
 double1 = staticLine.getX2() + forceCircle0.getRadius() * double15;
 double2 = staticLine.getY2() + forceCircle0.getRadius() * double16;
 if (doubles0[int1] == -1.0) {
 pointVectors[int1] = new CircleLineIntersect.PointVector(double1, double2);
 } else {
 pointVectors[int1].setPoint(double1, double2);
 }

 if (doubles0[int1] == 0.0) {
 collideclassindexs[int1].addCollided(staticLine, int2, forceCircle0.getVector());
 } else {
 collideclassindexs[int1].setCollided(staticLine, int2, forceCircle0.getVector());
 }

 doubles0[int1] = 0.0;
 continue;
 }
 }
 }

 double double17 = staticLine.getY2() - staticLine.getY1();
 double double18 = staticLine.getX1() - staticLine.getX2();
 double double19 = (staticLine.getY2() - staticLine.getY1()) * staticLine.getX1()
 + (staticLine.getX1() - staticLine.getX2()) * staticLine.getY1();
 double double20 = forceCircle0.getvy();
 double double21 = -forceCircle0.getvx();
 double double22 = forceCircle0.getvy() * forceCircle0.getX() + -forceCircle0.getvx() * forceCircle0.getY();
 double double23 = double17 * double21 - double20 * double18;
 double double24 = 0.0;
 double double25 = 0.0;
 if (double23 != 0.0) {
 double24 = (double21 * double19 - double18 * double22) / double23;
 double25 = (double17 * double22 - double20 * double19) / double23;
 }

 CircleLineIntersect.Point point2 = CircleLineIntersect.VectorMath.closestpointonline(
 staticLine.getX1(), staticLine.getY1(), staticLine.getX2(), staticLine.getY2(), forceCircle0.getX2(), forceCircle0.getY2()
 );
 CircleLineIntersect.Point point3 = CircleLineIntersect.VectorMath.closestpointonline(
 forceCircle0.getX(), forceCircle0.getY(), forceCircle0.getX2(), forceCircle0.getY2(), staticLine.getX1(), staticLine.getY1()
 );
 CircleLineIntersect.Point point4 = CircleLineIntersect.VectorMath.closestpointonline(
 forceCircle0.getX(), forceCircle0.getY(), forceCircle0.getX2(), forceCircle0.getY2(), staticLine.getX2(), staticLine.getY2()
 );
 if (CircleLineIntersect.Point.distanceSq(point2.getX(), point2.getY(), forceCircle0.getX2(), forceCircle0.getY2())
 < forceCircle0.getRadiusSq()
 && Math.min(staticLine.getX1(), staticLine.getX2()) <= point2.getX()
 && point2.getX() <= Math.max(staticLine.getX1(), staticLine.getX2())
 && Math.min(staticLine.getY1(), staticLine.getY2()) <= point2.getY()
 && point2.getY() <= Math.max(staticLine.getY1(), staticLine.getY2())
 || CircleLineIntersect.Point.distanceSq(point3.getX(), point3.getY(), staticLine.getX1(), staticLine.getY1())
 < forceCircle0.getRadiusSq()
 && Math.min(forceCircle0.getX(), forceCircle0.getX() + forceCircle0.getvx()) <= point3.getX()
 && point3.getX() <= Math.max(forceCircle0.getX(), forceCircle0.getX() + forceCircle0.getvx())
 && Math.min(forceCircle0.getY(), forceCircle0.getY() + forceCircle0.getvy()) <= point3.getY()
 && point3.getY() <= Math.max(forceCircle0.getY(), forceCircle0.getY() + forceCircle0.getvy())
 || CircleLineIntersect.Point.distanceSq(point4.getX(), point4.getY(), staticLine.getX2(), staticLine.getY2())
 < forceCircle0.getRadiusSq()
 && Math.min(forceCircle0.getX(), forceCircle0.getX() + forceCircle0.getvx()) <= point4.getX()
 && point4.getX() <= Math.max(forceCircle0.getX(), forceCircle0.getX() + forceCircle0.getvx())
 && Math.min(forceCircle0.getY(), forceCircle0.getY() + forceCircle0.getvy()) <= point4.getY()
 && point4.getY() <= Math.max(forceCircle0.getY(), forceCircle0.getY() + forceCircle0.getvy())
 || Math.min(forceCircle0.getX(), forceCircle0.getX() + forceCircle0.getvx()) <= double24
 && double24 <= Math.max(forceCircle0.getX(), forceCircle0.getX() + forceCircle0.getvx())
 && Math.min(forceCircle0.getY(), forceCircle0.getY() + forceCircle0.getvy()) <= double25
 && double25 <= Math.max(forceCircle0.getY(), forceCircle0.getY() + forceCircle0.getvy())
 && Math.min(staticLine.getX1(), staticLine.getX2()) <= double24
 && double24 <= Math.max(staticLine.getX1(), staticLine.getX2())
 && Math.min(staticLine.getY1(), staticLine.getY2()) <= double25
 && double25 <= Math.max(staticLine.getY1(), staticLine.getY2())
 || CircleLineIntersect.Point.distanceSq(staticLine.getX1(), staticLine.getY1(), forceCircle0.getX2(), forceCircle0.getY2())
 <= forceCircle0.getRadiusSq()
 || CircleLineIntersect.Point.distanceSq(staticLine.getX2(), staticLine.getY2(), forceCircle0.getX2(), forceCircle0.getY2())
 <= forceCircle0.getRadiusSq()) {
 double double26 = -double18;
 double double27 = double26 * forceCircle0.getX() + double17 * forceCircle0.getY();
 double double28 = double17 * double17 - double26 * double18;
 double double29 = 0.0;
 double double30 = 0.0;
 if (double28 != 0.0) {
 double29 = (double17 * double19 - double18 * double27) / double28;
 double30 = (double17 * double27 - double26 * double19) / double28;
 double double31 = CircleLineIntersect.Point.distance(double24, double25, forceCircle0.getX(), forceCircle0.getY())
 * forceCircle0.getRadius()
 / CircleLineIntersect.Point.distance(double29, double30, forceCircle0.getX(), forceCircle0.getY());
 double24 += -double31 * forceCircle0.getnormvx();
 double25 += -double31 * forceCircle0.getnormvy();
 double double32 = double26 * double24 + double17 * double25;
 double double33 = (double17 * double19 - double18 * double32) / double28;
 double double34 = (double17 * double32 - double26 * double19) / double28;
 if (Math.min(staticLine.getX1(), staticLine.getX2()) <= double33
 && double33 <= Math.max(staticLine.getX1(), staticLine.getX2())
 && Math.min(staticLine.getY1(), staticLine.getY2()) <= double34
 && double34 <= Math.max(staticLine.getY1(), staticLine.getY2())) {
 double29 += double24 - double33;
 double30 += double25 - double34;
 double double35 = Math.pow(double24 - forceCircle0.getX(), 2.0) + Math.pow(double25 - forceCircle0.getY(), 2.0);
 if (double35 <= doubles0[int1] || doubles0[int1] < 0.0) {
 CircleLineIntersect.RectVector rectVector0 = nullptr;
 if (!collideclassindexs[int1].collided() || doubles0[int1] != double35) {
 for (int int3 = 0; int3 < collideclassindexs[int1].size(); int3++) {
 if (collideclassindexs[int1].collided()
 && collideclassindexs[int1].getColliders().get(int3).getCollideobj() instanceof CircleLineIntersect.ForceCircle
 && doubles0[int1] > double35) {
 pointVectors[collideclassindexs[int1].getColliders().get(int3).getCollidewith()] = new CircleLineIntersect.PointVector(
 (CircleLineIntersect.PointVector)list.get(
 collideclassindexs[int1].getColliders().get(int3).getCollidewith()
 )
 );
 doubles0[collideclassindexs[int1].getColliders().get(int3).getCollidewith()] = -1.0;
 }
 }
 }

 if (CircleLineIntersect.Point.distanceSq(double29, double30, forceCircle0.getX(), forceCircle0.getY()) < 1.0E-8) {
 CircleLineIntersect.Point point5 = CircleLineIntersect.VectorMath.closestpointonline(
 staticLine.getX1() + (double24 - double29),
 staticLine.getY1() + (double25 - double30),
 staticLine.getX2() + (double24 - double29),
 staticLine.getY2() + (double25 - double30),
 forceCircle0.getX2(),
 forceCircle0.getY2()
 );
 rectVector0 = new CircleLineIntersect.RectVector(
 point5.getX() + (point5.getX() - forceCircle0.getX2()) - forceCircle0.getX(),
 point5.getY() + (point5.getY() - forceCircle0.getY2()) - forceCircle0.getY()
 );
 rectVector0 = (CircleLineIntersect.RectVector)rectVector0.getUnitVector();
 rectVector0 = new CircleLineIntersect.RectVector(
 rectVector0.getvx() * forceCircle0.getLength(), rectVector0.getvy() * forceCircle0.getLength()
 );
 } else {
 rectVector0 = new CircleLineIntersect.RectVector(
 forceCircle0.getX() - 2.0 * (double29 - double24) - double24,
 forceCircle0.getY() - 2.0 * (double30 - double25) - double25
 );
 rectVector0 = (CircleLineIntersect.RectVector)rectVector0.getUnitVector();
 rectVector0 = new CircleLineIntersect.RectVector(
 rectVector0.getvx() * forceCircle0.getLength(), rectVector0.getvy() * forceCircle0.getLength()
 );
 }

 rectVector0 = (CircleLineIntersect.RectVector)rectVector0.getUnitVector();
 rectVector0 = new CircleLineIntersect.RectVector(
 rectVector0.getvx() * forceCircle0.getLength(), rectVector0.getvy() * forceCircle0.getLength()
 );
 if (doubles0[int1] == -1.0) {
 pointVectors[int1] = new CircleLineIntersect.PointVector(double24, double25);
 } else {
 pointVectors[int1].setPoint(double24, double25);
 }

 if (doubles0[int1] == double35) {
 collideclassindexs[int1].addCollided(staticLine, int2, rectVector0);
 } else {
 collideclassindexs[int1].setCollided(staticLine, int2, rectVector0);
 }

 doubles0[int1] = double35;
 }
 } else {
 double double36 = forceCircle0.getRadius() * forceCircle0.getRadius();
 CircleLineIntersect.Point point6 = CircleLineIntersect.VectorMath.closestpointonline(
 forceCircle0.getX(),
 forceCircle0.getY(),
 forceCircle0.getX2(),
 forceCircle0.getY2(),
 staticLine.getX1(),
 staticLine.getY1()
 );
 double double37 = CircleLineIntersect.Point.distanceSq(point6.getX(), point6.getY(), staticLine.getX1(), staticLine.getY1());
 double double38 = CircleLineIntersect.Point.distanceSq(point6.getX(), point6.getY(), forceCircle0.getX(), forceCircle0.getY());
 CircleLineIntersect.Point point7 = CircleLineIntersect.VectorMath.closestpointonline(
 forceCircle0.getX(),
 forceCircle0.getY(),
 forceCircle0.getX2(),
 forceCircle0.getY2(),
 staticLine.getX2(),
 staticLine.getY2()
 );
 double double39 = CircleLineIntersect.Point.distanceSq(point7.getX(), point7.getY(), staticLine.getX2(), staticLine.getY2());
 double double40 = CircleLineIntersect.Point.distanceSq(point7.getX(), point7.getY(), forceCircle0.getX(), forceCircle0.getY());
 double double41 = 0.0;
 if (double38 < double40 && double37 <= double39) {
 double41 = Math.sqrt(Math.abs(double36 - double37);
 double24 = point6.getX() - double41 * forceCircle0.getnormvx();
 double25 = point6.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX1();
 double30 = staticLine.getY1();
 } else if (double38 > double40 && double37 >= double39) {
 double41 = Math.sqrt(Math.abs(double36 - double39);
 double24 = point7.getX() - double41 * forceCircle0.getnormvx();
 double25 = point7.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX2();
 double30 = staticLine.getY2();
 } else if (double37 < double39) {
 if (!(double38 < double40)
 && !(CircleLineIntersect.Point.distanceSq(double33, double34, staticLine.getX1(), staticLine.getY1()) <= double36) {
 double41 = Math.sqrt(Math.abs(double36 - double39);
 double24 = point7.getX() - double41 * forceCircle0.getnormvx();
 double25 = point7.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX2();
 double30 = staticLine.getY2();
 } else {
 double41 = Math.sqrt(Math.abs(double36 - double37);
 double24 = point6.getX() - double41 * forceCircle0.getnormvx();
 double25 = point6.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX1();
 double30 = staticLine.getY1();
 }
 } else if (double37 > double39) {
 if (!(double40 < double38)
 && !(CircleLineIntersect.Point.distanceSq(double33, double34, staticLine.getX2(), staticLine.getY2()) <= double36) {
 double41 = Math.sqrt(Math.abs(double36 - double37);
 double24 = point6.getX() - double41 * forceCircle0.getnormvx();
 double25 = point6.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX1();
 double30 = staticLine.getY1();
 } else {
 double41 = Math.sqrt(Math.abs(double36 - double39);
 double24 = point7.getX() - double41 * forceCircle0.getnormvx();
 double25 = point7.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX2();
 double30 = staticLine.getY2();
 }
 } else if ((
 !(Math.min(forceCircle0.getX(), forceCircle0.getX2()) <= point7.getX())
 || !(point7.getX() <= Math.max(forceCircle0.getX(), forceCircle0.getX2()))
 || !(Math.min(forceCircle0.getY(), forceCircle0.getY2()) <= point7.getY())
 || !(point7.getY() <= Math.max(forceCircle0.getY(), forceCircle0.getY2()))
 )
 && !(
 CircleLineIntersect.Point.distanceSq(point7.getX(), point7.getY(), forceCircle0.getX2(), forceCircle0.getY2())
 <= forceCircle0.getRadiusSq()
 )) {
 double41 = Math.sqrt(Math.abs(double36 - double37);
 double24 = point6.getX() - double41 * forceCircle0.getnormvx();
 double25 = point6.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX1();
 double30 = staticLine.getY1();
 } else if ((
 !(Math.min(forceCircle0.getX(), forceCircle0.getX2()) <= point6.getX())
 || !(point6.getX() <= Math.max(forceCircle0.getX(), forceCircle0.getX2()))
 || !(Math.min(forceCircle0.getY(), forceCircle0.getY2()) <= point6.getY())
 || !(point6.getY() <= Math.max(forceCircle0.getY(), forceCircle0.getY2()))
 )
 && !(
 CircleLineIntersect.Point.distanceSq(point7.getX(), point7.getY(), forceCircle0.getX2(), forceCircle0.getY2())
 <= forceCircle0.getRadiusSq()
 )) {
 double41 = Math.sqrt(Math.abs(double36 - double39);
 double24 = point7.getX() - double41 * forceCircle0.getnormvx();
 double25 = point7.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX2();
 double30 = staticLine.getY2();
 } else if (double38 < double40) {
 double41 = Math.sqrt(Math.abs(double36 - double37);
 double24 = point6.getX() - double41 * forceCircle0.getnormvx();
 double25 = point6.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX1();
 double30 = staticLine.getY1();
 } else {
 double41 = Math.sqrt(Math.abs(double36 - double39);
 double24 = point7.getX() - double41 * forceCircle0.getnormvx();
 double25 = point7.getY() - double41 * forceCircle0.getnormvy();
 double29 = staticLine.getX2();
 double30 = staticLine.getY2();
 }

 double double42 = Math.pow(double24 - forceCircle0.getX(), 2.0) + Math.pow(double25 - forceCircle0.getY(), 2.0);
 if (double42 <= doubles0[int1] || doubles0[int1] < 0.0) {
 CircleLineIntersect.RectVector rectVector1 = nullptr;
 if (!collideclassindexs[int1].collided() || doubles0[int1] != double42) {
 for (int int4 = 0; int4 < collideclassindexs[int1].size(); int4++) {
 if (collideclassindexs[int1].collided()
 && collideclassindexs[int1].getColliders().get(int4).getCollideobj() instanceof CircleLineIntersect.ForceCircle
 && doubles0[int1] > double42) {
 pointVectors[collideclassindexs[int1].getColliders().get(int4).getCollidewith()] = new CircleLineIntersect.PointVector(
 (CircleLineIntersect.PointVector)list.get(
 collideclassindexs[int1].getColliders().get(int4).getCollidewith()
 )
 );
 doubles0[collideclassindexs[int1].getColliders().get(int4).getCollidewith()] = -1.0;
 }
 }
 }

 rectVector1 = new CircleLineIntersect.RectVector(
 double24 - (double29 - double24) - double24, double25 - (double30 - double25) - double25
 );
 rectVector1 = (CircleLineIntersect.RectVector)rectVector1.getUnitVector();
 rectVector1 = new CircleLineIntersect.RectVector(
 rectVector1.getvx() * forceCircle0.getLength(), rectVector1.getvy() * forceCircle0.getLength()
 );
 if (doubles0[int1] == -1.0) {
 pointVectors[int1] = new CircleLineIntersect.PointVector(double24, double25);
 } else {
 pointVectors[int1].setPoint(double24, double25);
 }

 if (doubles0[int1] == double42) {
 collideclassindexs[int1].addCollided(staticLine, int2, rectVector1);
 } else {
 collideclassindexs[int1].setCollided(staticLine, int2, rectVector1);
 }

 doubles0[int1] = double42;
 }
 }
 }
 }
 }
 }
 }

 std::vector arrayList1 = new ArrayList((int)Math.ceil(list.size() / 10);

 for (int int5 = 0; int5 < pointVectors.length; int5++) {
 if (collideclassindexs[int5].collided()) {
 CircleLineIntersect.ForceCircle forceCircle1 = (CircleLineIntersect.ForceCircle)list.get(int5);
 if (forceCircle1.isFrozen()) {
 pointVectors[int5].setRect(0.0, 0.0);
 } else {
 double double43 = 0.0;
 double double44 = 0.0;
 bool boolean1 = false;
 double double45 = 0.0;

 for (int int6 = 0; int6 < collideclassindexs[int5].size(); int6++) {
 void* object = collideclassindexs[int5].getColliders().get(int6).getCollideobj();
 double45 += ((CircleLineIntersect.ForceCircle)list.get(int5)
 .getRestitution(collideclassindexs[int5].getColliders().get(int6).getCollideobj());
 if (object instanceof CircleLineIntersect.StaticLine && collideclassindexs[int5].getColliders().get(int6).getCollideforce() != nullptr) {
 double43 += collideclassindexs[int5].getColliders().get(int6).getCollideforce().getvx();
 double44 += collideclassindexs[int5].getColliders().get(int6).getCollideforce().getvy();
 }
 }

 double45 /= collideclassindexs[int5].getColliders().size();
 if (doubles0[int5] == -1.0) {
 pointVectors[int5] = new CircleLineIntersect.PointVector(pointVectors[int5].getX(), pointVectors[int5].getY());
 }

 pointVectors[int5].setRect(double43 * double45, double44 * double45);
 arrayList1.add(int5);
 if (doubles1[int5] == 1.0 && ((CircleLineIntersect.ForceCircle)list.get(int5).getLength() != 0.0 && !boolean1) {
 if (doubles0[int5] == 0.0) {
 doubles1[int5] = 0.0;
 } else if (doubles0[int5] > 0.0) {
 doubles1[int5] = Math.sqrt(doubles0[int5]) / ((CircleLineIntersect.ForceCircle)list.get(int5).getLength();
 } else {
 doubles1[int5] = ((CircleLineIntersect.ForceCircle)list.get(int5).distance(pointVectors[int5])
 / ((CircleLineIntersect.ForceCircle)list.get(int5).getLength();
 }
 }

 doubles2[int5] += doubles1[int5] * (1.0 - doubles2[int5]);
 if (!pointVectors[int5] == list.get(int5)) {
 booleans[int5] = true;
 }
 }
 }
 }

 return new CircleLineIntersect.Collideresult(pointVectors, collideclassindexs, arrayList1, doubles2, doubles1, booleans);
 }

 public static CircleLineIntersect.Collideresult checkforcecirclescollide(
 List<CircleLineIntersect.ForceCircle> list, ArrayList<CircleLineIntersect.StaticLine> arrayList, double[] doubles, boolean[] booleans, boolean boolean0
 ) {
 CircleLineIntersect.Collideresult collideresult = checkforcecirclescollidetime(list, arrayList, doubles, booleans, boolean0);
 new ArrayList();

 for (int int0 = collideresult.resultants.length - 1; int0 >= 0; int0--) {
 if (collideresult.collideinto[int0].collided()) {
 ((CircleLineIntersect.ForceCircle)list.get(int0).setPointVector(collideresult.resultants[int0]);
 }
 }

 return collideresult;
 }

 public static CircleLineIntersect.Collideresult checkforcecirclescollide(
 List<CircleLineIntersect.ForceCircle> list, ArrayList<CircleLineIntersect.StaticLine> arrayList
 ) {
 double[] doubles = new double[list.size()];
 boolean[] booleans = new boolean[list.size()];

 for (int int0 = list.size() - 1; int0 >= 0; int0--) {
 doubles[int0] = 1.0;
 }

 return checkforcecirclescollide();
 }

 static bool TEST(Vector3f vector3f1, float float3, float float5, float float1, float float0, CarController carController) {
 Vector3f vector3f0 = new Vector3f();
 vector3f1.cross(new Vector3f(0.0F, 1.0F, 0.0F), vector3f0);
 vector3f1.x *= float0;
 vector3f1.z *= float0;
 vector3f0.x *= float1;
 vector3f0.z *= float1;
 float float2 = float3 + vector3f1.x;
 float float4 = float5 + vector3f1.z;
 float float6 = float3 - vector3f1.x;
 float float7 = float5 - vector3f1.z;
 float float8 = float2 - vector3f0.x / 2.0F;
 float float9 = float2 + vector3f0.x / 2.0F;
 float float10 = float6 - vector3f0.x / 2.0F;
 float float11 = float6 + vector3f0.x / 2.0F;
 float float12 = float7 - vector3f0.z / 2.0F;
 float float13 = float7 + vector3f0.z / 2.0F;
 float float14 = float4 - vector3f0.z / 2.0F;
 float float15 = float4 + vector3f0.z / 2.0F;
 float8 += WorldSimulation.instance.offsetX;
 float14 += WorldSimulation.instance.offsetY;
 float9 += WorldSimulation.instance.offsetX;
 float15 += WorldSimulation.instance.offsetY;
 float10 += WorldSimulation.instance.offsetX;
 float12 += WorldSimulation.instance.offsetY;
 float11 += WorldSimulation.instance.offsetX;
 float13 += WorldSimulation.instance.offsetY;
 std::vector arrayList0 = new ArrayList();
 CircleLineIntersect.StaticLine staticLine0;
 arrayList0.add(staticLine0 = new CircleLineIntersect.StaticLine(float8, float14, float9, float15);
 CircleLineIntersect.StaticLine staticLine1;
 arrayList0.add(staticLine1 = new CircleLineIntersect.StaticLine(float9, float15, float11, float13);
 CircleLineIntersect.StaticLine staticLine2;
 arrayList0.add(staticLine2 = new CircleLineIntersect.StaticLine(float11, float13, float10, float12);
 CircleLineIntersect.StaticLine staticLine3;
 arrayList0.add(staticLine3 = new CircleLineIntersect.StaticLine(float10, float12, float8, float14);
 IsoPlayer player = IsoPlayer.getInstance();
 std::vector arrayList1 = new ArrayList();
 uint8_t byte0 = 8;
 CircleLineIntersect.ForceCircle forceCircle = new CircleLineIntersect.ForceCircle(player.x, player.y, player.nx - player.x, player.ny - player.y, 0.295);
 if (carController != nullptr) {
 carController.drawCircle((float)forceCircle.getX2(), (float)forceCircle.getY2(), 0.3F);
 }

 arrayList1.add(forceCircle);
 CircleLineIntersect.Collideresult collideresult = checkforcecirclescollide(arrayList1, arrayList0);
 if (carController != nullptr) {
 carController.drawCircle((float)forceCircle.getX(), (float)forceCircle.getY(), (float)forceCircle.getRadius());
 }

 if (collideresult.collidelist.empty()) {
 return false;
 } else {
 int int0 = collideresult.collideinto.length;
 Vector2f vector2f = new Vector2f(player.nx - player.x, player.ny - player.y);
 if (vector2f.length() > 0.0F) {
 vector2f.normalise();
 }

 for (int int1 = 0; int1 < collideresult.collideinto.length; int1++) {
 CircleLineIntersect.StaticLine staticLine4 = (CircleLineIntersect.StaticLine)collideresult.collideinto[int1]
 .getColliders()
 .get(0)
 .getCollideobj();
 if (staticLine4 == staticLine3 || staticLine4 == staticLine1) {
 LineDrawer.addLine(
 float2 + WorldSimulation.instance.offsetX,
 float4 + WorldSimulation.instance.offsetY,
 0.0F,
 float6 + WorldSimulation.instance.offsetX,
 float7 + WorldSimulation.instance.offsetY,
 0.0F,
 1.0F,
 1.0F,
 1.0F,
 nullptr,
 true
 );
 CircleLineIntersect.Point point0 = CircleLineIntersect.VectorMath.closestpointonline(
 float2 + WorldSimulation.instance.offsetX,
 float4 + WorldSimulation.instance.offsetY,
 float6 + WorldSimulation.instance.offsetX,
 float7 + WorldSimulation.instance.offsetY,
 forceCircle.getX(),
 forceCircle.getY()
 );
 vector3f1.set((float)(point0.x - player.x), (float)(point0.y - player.y), 0.0F);
 vector3f1.normalize();
 double double0 = CircleLineIntersect.VectorMath.dotproduct(vector2f.x, vector2f.y, vector3f1.x, vector3f1.y);
 if (double0 < 0.0) {
 int0--;
 }
 }

 if (staticLine4 == staticLine0 || staticLine4 == staticLine2) {
 LineDrawer.addLine(
 float3 - vector3f0.x / 2.0F + WorldSimulation.instance.offsetX,
 float5 - vector3f0.z / 2.0F + WorldSimulation.instance.offsetY,
 0.0F,
 float3 + vector3f0.x / 2.0F + WorldSimulation.instance.offsetX,
 float5 + vector3f0.z / 2.0F + WorldSimulation.instance.offsetY,
 0.0F,
 1.0F,
 1.0F,
 1.0F,
 nullptr,
 true
 );
 CircleLineIntersect.Point point1 = CircleLineIntersect.VectorMath.closestpointonline(
 float3 - vector3f0.x / 2.0F + WorldSimulation.instance.offsetX,
 float5 - vector3f0.z / 2.0F + WorldSimulation.instance.offsetY,
 float3 + vector3f0.x / 2.0F + WorldSimulation.instance.offsetX,
 float5 + vector3f0.z / 2.0F + WorldSimulation.instance.offsetY,
 forceCircle.getX(),
 forceCircle.getY()
 );
 vector3f1.set((float)(point1.x - player.x), (float)(point1.y - player.y), 0.0F);
 vector3f1.normalize();
 double double1 = CircleLineIntersect.VectorMath.dotproduct(vector2f.x, vector2f.y, vector3f1.x, vector3f1.y);
 if (double1 < 0.0) {
 int0--;
 }
 }
 }

 if (int0 == 0) {
 return false;
 } else {
 vector3f1.set((float)forceCircle.getX(), (float)forceCircle.getY(), 0.0F);
 return true;
 }
 }
 }

 static class Collideclassindex {
 private ArrayList<CircleLineIntersect.Collider> colliders = new ArrayList<>(1);
 int numforcecircles;

 public Collideclassindex() {
 this->numforcecircles = 0;
 }

 public Collideclassindex(void* object, int int0, CircleLineIntersect.Vector vector) {
 this->colliders.add(new CircleLineIntersect.Collider(object, int0, vector);
 }

 bool collided() {
 return this->size() > 0;
 }

 void reset() {
 this->colliders.trimToSize();
 this->colliders.clear();
 this->numforcecircles = 0;
 }

 void setCollided(void* object, int int0, CircleLineIntersect.Vector vector) {
 if (this->size() > 0) {
 this->reset();
 }

 if (object instanceof CircleLineIntersect.ForceCircle && !((CircleLineIntersect.ForceCircle)object).isFrozen()) {
 this->numforcecircles++;
 }

 this->colliders.add(new CircleLineIntersect.Collider(object, int0, vector);
 }

 void addCollided(void* object, int int0, CircleLineIntersect.Vector vector) {
 if (object instanceof CircleLineIntersect.ForceCircle && !((CircleLineIntersect.ForceCircle)object).isFrozen()) {
 this->numforcecircles++;
 }

 this->colliders.add(new CircleLineIntersect.Collider(object, int0, vector);
 }

 public ArrayList<CircleLineIntersect.Collider> getColliders() {
 return this->colliders;
 }

 int getNumforcecircles() {
 return this->numforcecircles;
 }

 public CircleLineIntersect.Collider contains(Object object) {
 for (CircleLineIntersect.Collider collider : this->colliders) {
 if (collider.getCollideobj() == object) {
 return collider;
 }
 }

 return nullptr;
 }

 int size() {
 return this->colliders.size();
 }

 std::string toString() {
 std::string string = "";

 for (CircleLineIntersect.Collider collider : this->colliders) {
 string = string + collider.toString() + "\n";
 }

 return string;
 }
 }

 static class Collider {
 void* collideobj;
 int collideindex;
 private CircleLineIntersect.Vector collideforce;

 public Collider(CircleLineIntersect.Vector vector, int integer) {
 this->collideobj = vector;
 this->collideindex = integer;
 this->collideforce = vector;
 }

 public Collider(void* object, int integer, CircleLineIntersect.Vector vector) {
 this->collideobj = object;
 this->collideindex = integer;
 this->collideforce = vector;
 }

 void* getCollideobj() {
 return this->collideobj;
 }

 int getCollidewith() {
 return this->collideindex;
 }

 public CircleLineIntersect.Vector getCollideforce() {
 return this->collideforce;
 }

 void setCollideforce(CircleLineIntersect.Vector vector) {
 this->collideforce = vector;
 }

 std::string toString() {
 return this->collideobj.getClass().getSimpleName() + " @ " + this->collideindex + " hit with " + this->collideforce.toString();
 }
 }

 static class Collideresult {
 protected CircleLineIntersect.PointVector[] resultants;
 protected ArrayList<Integer> collidelist;
 protected CircleLineIntersect.Collideclassindex[] collideinto;
 protected double[] timepassed;
 protected double[] collidetime;
 protected boolean[] modified;

 public Collideresult(
 CircleLineIntersect.PointVector[] pointVectors,
 CircleLineIntersect.Collideclassindex[] collideclassindexs,
 ArrayList<Integer> arrayList,
 double[] doubles0,
 double[] doubles1,
 boolean[] booleans
 ) {
 this->resultants = pointVectors;
 this->collideinto = collideclassindexs;
 this->collidelist = arrayList;
 this->timepassed = doubles0;
 this->collidetime = doubles1;
 this->modified = booleans;
 }

 std::string toString() {
 return this->collidelist.toString();
 }
 }

 static class Force extends CircleLineIntersect.PointVector {
 double length;
 double mass;

 public Force(double double0, double double1, double double2, double double3) {
 super(double0, double1, double2, double3);
 this->length = CircleLineIntersect.VectorMath.length(double2, double3);
 }

 double getLength() {
 return this->length;
 }

 double getnormvx() {
 return this->length > 0.0 ? this->vx / this->length : 0.0;
 }

 double getnormvy() {
 return this->length > 0.0 ? this->vy / this->length : 0.0;
 }

 double getRestitution(void* var1) {
 return 1.0;
 }

 void setPointVector(CircleLineIntersect.PointVector pointVector) {
 this->x = pointVector.getX();
 this->y = pointVector.getY();
 if (!this->isFrozen() && (this->vx != pointVector.getvx() || this->vy != pointVector.getvy())) {
 this->vx = pointVector.getvx();
 this->vy = pointVector.getvy();
 this->length = CircleLineIntersect.VectorMath.length(this->vx, this->vy);
 }
 }

 bool isFrozen() {
 return false;
 }
 }

 static class ForceCircle extends CircleLineIntersect.Force {
 double radius;
 double radiussq;

 public ForceCircle(double double0, double double1, double double2, double double3, double double4) {
 super(double0, double1, double2, double3);
 this->radius = double4;
 this->radiussq = double4 * double4;
 }

 double getRadius() {
 return this->radius;
 }

 double getRadiusSq() {
 return this->radiussq;
 }
 }

 static class Point {
 double x;
 double y;

 public static CircleLineIntersect.Point midpoint(double double2, double double0, double double3, double double1) {
 return new CircleLineIntersect.Point((double2 + double3) / 2.0, (double0 + double1) / 2.0);
 }

 public static CircleLineIntersect.Point midpoint(CircleLineIntersect.Point point1, CircleLineIntersect.Point point0) {
 return midpoint();
 }

 public Point(double double0, double double1) {
 if (Double.isNaN(double0) || Double.isInfinite(double0) {
 double0 = 0.0;
 }

 if (Double.isNaN(double1) || Double.isInfinite(double1) {
 double1 = 0.0;
 }

 this->x = double0;
 this->y = double1;
 }

 double getX() {
 return this->x;
 }

 double getY() {
 return this->y;
 }

 void setPoint(double double0, double double1) {
 this->x = double0;
 this->y = double1;
 }

 static double distanceSq(double double0, double double2, double double1, double double3) {
 double0 -= double1;
 double2 -= double3;
 return double0 * double0 + double2 * double2;
 }

 static double distance(double double0, double double2, double double1, double double3) {
 double0 -= double1;
 double2 -= double3;
 return Math.sqrt(double0 * double0 + double2 * double2);
 }

 double distanceSq(double double0, double double1) {
 double0 -= this->getX();
 double1 -= this->getY();
 return double0 * double0 + double1 * double1;
 }

 double distanceSq(CircleLineIntersect.Point point1) {
 double double0 = point1.getX() - this->getX();
 double double1 = point1.getY() - this->getY();
 return double0 * double0 + double1 * double1;
 }

 double distance(CircleLineIntersect.Point point1) {
 double double0 = point1.getX() - this->getX();
 double double1 = point1.getY() - this->getY();
 return Math.sqrt(double0 * double0 + double1 * double1);
 }
 }

 static class PointVector extends CircleLineIntersect.Point implements CircleLineIntersect.Vector {
 double vx = 0.0;
 double vy = 0.0;

 public PointVector(double double0, double double1) {
 this(double0, double1, 0.0, 0.0);
 }

 public PointVector(double double0, double double1, double double2, double double3) {
 super(double0, double1);
 this->vx = double2;
 this->vy = double3;
 }

 public PointVector(CircleLineIntersect.PointVector pointVector1) {
 this(pointVector1.getX(), pointVector1.getY(), pointVector1.getvx(), pointVector1.getvy());
 }

 double getLength() {
 return CircleLineIntersect.VectorMath.length(this->vx, this->vy);
 }

 public CircleLineIntersect.Vector getVector() {
 return new CircleLineIntersect.RectVector(this->vx, this->vy);
 }

 double getvx() {
 return this->vx;
 }

 double getvy() {
 return this->vy;
 }

 double getX1() {
 return this->x;
 }

 double getX2() {
 return this->x + this->vx;
 }

 double getY1() {
 return this->y;
 }

 double getY2() {
 return this->y + this->vy;
 }

 void setRect(double double0, double double1) {
 this->vx = double0;
 this->vy = double1;
 }
 }

 static class RectVector implements CircleLineIntersect.Vector {
 double vx;
 double vy;

 public RectVector(double double0, double double1) {
 this->vx = double0;
 this->vy = double1;
 }

 public RectVector(CircleLineIntersect.Vector vector) {
 this->setVector(vector);
 }

 double getLength() {
 return Math.sqrt(Math.abs(this->getvx() * this->getvx() + this->getvy() * this->getvy()));
 }

 public CircleLineIntersect.Vector getUnitVector() {
 double double0 = this->getLength();
 return new CircleLineIntersect.RectVector(this->getvx() / double0, this->getvy() / double0);
 }

 double getvx() {
 return this->vx;
 }

 double getvy() {
 return this->vy;
 }

 void setVector(CircleLineIntersect.Vector vector) {
 this->vx = vector.getvx();
 this->vy = vector.getvy();
 }
 }

 static class StaticLine extends CircleLineIntersect.Point {
 double x2;
 double y2;

 public StaticLine(double double0, double double1, double double2, double double3) {
 super(double0, double1);
 this->x2 = double2;
 this->y2 = double3;
 }

 public CircleLineIntersect.Point getP1() {
 return new CircleLineIntersect.Point(this->getX1(), this->getY1());
 }

 public CircleLineIntersect.Point getP2() {
 return new CircleLineIntersect.Point(this->getX2(), this->getY2());
 }

 double getX1() {
 return this->x;
 }

 double getX2() {
 return this->x2;
 }

 double getY1() {
 return this->y;
 }

 double getY2() {
 return this->y2;
 }
 }

 interface Vector {
 double getvx();

 double getvy();

 double getLength();
 }

 static class VectorMath {
 public static CircleLineIntersect.Vector add(CircleLineIntersect.Vector vector1, CircleLineIntersect.Vector vector0) {
 return new CircleLineIntersect.RectVector(vector1.getvx() + vector0.getvx(), vector1.getvy() + vector0.getvy());
 }

 public static CircleLineIntersect.Vector subtract(CircleLineIntersect.Vector vector1, CircleLineIntersect.Vector vector0) {
 return new CircleLineIntersect.RectVector(vector1.getvx() - vector0.getvx(), vector1.getvy() - vector0.getvy());
 }

 static double length(double double0, double double1) {
 return CircleLineIntersect.Point.distance(0.0, 0.0, double0, double1);
 }

 static double dotproduct(CircleLineIntersect.Vector vector1, CircleLineIntersect.Vector vector0) {
 return dotproduct();
 }

 static double dotproduct(double double2, double double0, double double3, double double1) {
 return double2 * double3 + double0 * double1;
 }

 static double cosproj(CircleLineIntersect.Vector vector1, CircleLineIntersect.Vector vector0) {
 return dotproduct();
 }

 static double cosproj(double double2, double double3, double double0, double double1) {
 return dotproduct();
 }

 static double anglebetween(CircleLineIntersect.Vector vector0, CircleLineIntersect.Vector vector1) {
 return Math.acos(cosproj(vector0, vector1);
 }

 static double anglebetween(double double0, double double1, double double2, double double3) {
 return Math.acos(cosproj(double0, double1, double2, double3);
 }

 static double crossproduct(CircleLineIntersect.Vector vector1, CircleLineIntersect.Vector vector0) {
 return crossproduct();
 }

 static double crossproduct(double double2, double double0, double double1, double double3) {
 return double2 * double3 - double0 * double1;
 }

 static double sinproj(CircleLineIntersect.Vector vector1, CircleLineIntersect.Vector vector0) {
 return crossproduct();
 }

 static double sinproj(double double2, double double3, double double0, double double1) {
 return crossproduct();
 }

 public static boolean equaldirection(
 double double2, double double0, double double3, double double1, double double8, double double7, double double6, double double5
 ) {
 if (double2 - double3 == 0.0 && double0 - double1 == 0.0) {
 return true;
 } else {
 double double4 = ((double2 - double3) * (double2 - double8) + (double0 - double1) * (double0 - double7)
 / (Math.abs(double6) * Math.abs(double5);
 return double4 > 0.995 && double4 <= 1.0;
 }
 }

 public static boolean equaldirection(
 double double2, double double0, double double3, double double1, double double8, double double7, double double6, double double5, double double9
 ) {
 if (double2 - double3 == 0.0 && double0 - double1 == 0.0) {
 return true;
 } else {
 double double4 = ((double2 - double3) * (double2 - double8) + (double0 - double1) * (double0 - double7)
 / (Math.abs(double6) * Math.abs(double5);
 return double4 > double9 && double4 <= 1.0;
 }
 }

 public static boolean equaldirection(
 double double1, double double0, double double6, double double5, double double4, double double3, double double7
 ) {
 if (double1 == 0.0 && double0 == 0.0) {
 return true;
 } else {
 double double2 = (double1 * double6 + double0 * double5) / (Math.abs(double4) * Math.abs(double3);
 return double2 > double7 && double2 <= 1.0;
 }
 }

 static bool equaldirection(double double0, double double1, double double2) {
 if (double0 > Math.PI * 2) {
 double0 -= Math.PI * 2;
 } else if (double0 < 0.0) {
 double0 += Math.PI * 2;
 }

 if (double1 > Math.PI * 2) {
 double1 -= Math.PI * 2;
 } else if (double1 < 0.0) {
 double1 += Math.PI * 2;
 }

 return Math.abs(double0 - double1) < double2;
 }

 static double linepointdistance(double double0, double double1, double double2, double double3, double double4, double double5) {
 CircleLineIntersect.Point point = closestpointonline(double0, double1, double2, double3, double4, double5);
 return CircleLineIntersect.Point.distance(double4, double5, point.getX(), point.getY());
 }

 static double linepointdistancesq(double double4, double double2, double double5, double double1, double double9, double double8) {
 double double0 = double1 - double2;
 double double3 = double4 - double5;
 double double6 = (double1 - double2) * double4 + (double4 - double5) * double2;
 double double7 = -double3 * double9 + double0 * double8;
 double double10 = double0 * double0 - -double3 * double3;
 double double11 = 0.0;
 double double12 = 0.0;
 if (double10 != 0.0) {
 double11 = (double0 * double6 - double3 * double7) / double10;
 double12 = (double0 * double7 - -double3 * double6) / double10;
 }

 return Math.abs((double11 - double9) * (double11 - double9) + (double12 - double8) * (double12 - double8);
 }

 public static CircleLineIntersect.Point closestpointonline(CircleLineIntersect.StaticLine staticLine, CircleLineIntersect.Point point) {
 return closestpointonline();
 }

 public static CircleLineIntersect.Point closestpointonline(
 double double4, double double2, double double5, double double1, double double9, double double8
 ) {
 double double0 = double1 - double2;
 double double3 = double4 - double5;
 double double6 = (double1 - double2) * double4 + (double4 - double5) * double2;
 double double7 = -double3 * double9 + double0 * double8;
 double double10 = double0 * double0 - -double3 * double3;
 double double11 = 0.0;
 double double12 = 0.0;
 if (double10 != 0.0) {
 double11 = (double0 * double6 - double3 * double7) / double10;
 double12 = (double0 * double7 - -double3 * double6) / double10;
 } else {
 double11 = double9;
 double12 = double8;
 }

 return new CircleLineIntersect.Point(double11, double12);
 }

 public static CircleLineIntersect.Vector getVector(CircleLineIntersect.Point point1, CircleLineIntersect.Point point0) {
 return new CircleLineIntersect.RectVector(point1.getX() - point0.getX(), point1.getY() - point0.getY());
 }

 public static CircleLineIntersect.Vector rotate(CircleLineIntersect.Vector vector, double double0) {
 return new CircleLineIntersect.RectVector(
 vector.getvx() * Math.cos(double0) - vector.getvy() * Math.sin(double0),
 vector.getvx() * Math.sin(double0) + vector.getvy() * Math.cos(double0)
 );
 }
 }
}
} // namespace vehicles
} // namespace zombie
