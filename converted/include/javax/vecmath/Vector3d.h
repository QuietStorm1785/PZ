#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Vector3d : public Tuple3d {
public:
 static const long serialVersionUID = 3761969948420550442L;

 public Vector3d(double double0, double double1, double double2) {
 super(double0, double1, double2);
 }

 public Vector3d(double[] doubles) {
 super(doubles);
 }

 public Vector3d(Vector3d vector3d1) {
 super(vector3d1);
 }

 public Vector3d(Vector3f vector3f) {
 super(vector3f);
 }

 public Vector3d(Tuple3f tuple3f) {
 super(tuple3f);
 }

 public Vector3d(Tuple3d tuple3d) {
 super(tuple3d);
 }

 public Vector3d() {
 }

 void cross(Vector3d vector3d1, Vector3d vector3d0) {
 double double0 = vector3d1.y * vector3d0.z - vector3d1.z * vector3d0.y;
 double double1 = vector3d0.x * vector3d1.z - vector3d0.z * vector3d1.x;
 this->z = vector3d1.x * vector3d0.y - vector3d1.y * vector3d0.x;
 this->x = double0;
 this->y = double1;
 }

 void normalize(Vector3d vector3d0) {
 double double0 = 1.0 / Math.sqrt(vector3d0.x * vector3d0.x + vector3d0.y * vector3d0.y + vector3d0.z * vector3d0.z);
 this->x = vector3d0.x * double0;
 this->y = vector3d0.y * double0;
 this->z = vector3d0.z * double0;
 }

 void normalize() {
 double double0 = 1.0 / Math.sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
 this->x *= double0;
 this->y *= double0;
 this->z *= double0;
 }

 double dot(Vector3d vector3d0) {
 return this->x * vector3d0.x + this->y * vector3d0.y + this->z * vector3d0.z;
 }

 double lengthSquared() {
 return this->x * this->x + this->y * this->y + this->z * this->z;
 }

 double length() {
 return Math.sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
 }

 double angle(Vector3d vector3d0) {
 double double0 = this->dot(vector3d0) / (this->length() * vector3d0.length());
 if (double0 < -1.0) {
 double0 = -1.0;
 }

 if (double0 > 1.0) {
 double0 = 1.0;
 }

 return Math.acos(double0);
 }
}
} // namespace vecmath
} // namespace javax
