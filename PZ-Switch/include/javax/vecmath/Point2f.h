#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Point2f : public Tuple2f {
public:
 static const long serialVersionUID = -4801347926528714435L;

public
 Point2f(float float0, float float1) { super(float0, float1); }

public
 Point2f(float[] floats) { super(floats); }

public
 Point2f(Point2f point2f1) { super(point2f1); }

public
 Point2f(Point2d point2d) { super(point2d); }

public
 Point2f(Tuple2d tuple2d) { super(tuple2d); }

public
 Point2f(Tuple2f tuple2f) { super(tuple2f); }

public
 Point2f() {}

 float distanceSquared(Point2f point2f0) {
 float float0 = this->x - point2f0.x;
 float float1 = this->y - point2f0.y;
 return float0 * float0 + float1 * float1;
 }

 float distance(Point2f point2f0) {
 float float0 = this->x - point2f0.x;
 float float1 = this->y - point2f0.y;
 return (float)Math.sqrt(float0 * float0 + float1 * float1);
 }

 float distanceL1(Point2f point2f0) {
 return Math.abs(this->x - point2f0.x) + Math.abs(this->y - point2f0.y);
 }

 float distanceLinf(Point2f point2f0) {
 return Math.max(Math.abs(this->x - point2f0.x),
 Math.abs(this->y - point2f0.y);
 }
}
} // namespace vecmath
} // namespace javax
