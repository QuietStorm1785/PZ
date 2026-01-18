#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"

namespace zombie {
namespace core {
namespace math {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Vector3 : public Vector3f {
public:
 public Vector3() {
 }

 public Vector3(float float0, float float1, float float2) {
 super(float0, float1, float2);
 }

 public Vector3(org.lwjgl.util.vector.Vector3f vector3f) {
 super(vector3f.x, vector3f.y, vector3f.z);
 }

 public Vector3(Vector3 vector31) {
 super(vector31.x, vector31.y, vector31.z);
 }

 public static org.lwjgl.util.vector.Vector3f addScaled(
 org.lwjgl.util.vector.Vector3f vector3f2, org.lwjgl.util.vector.Vector3f vector3f1, float float0, org.lwjgl.util.vector.Vector3f vector3f0
 ) {
 vector3f0.set(vector3f2.x + vector3f1.x * float0, vector3f2.y + vector3f1.y * float0, vector3f2.z + vector3f1.z * float0);
 return vector3f0;
 }

 public static org.lwjgl.util.vector.Vector3f setScaled(org.lwjgl.util.vector.Vector3f vector3f1, float float0, org.lwjgl.util.vector.Vector3f vector3f0) {
 vector3f0.set(vector3f1.x * float0, vector3f1.y * float0, vector3f1.z * float0);
 return vector3f0;
 }

 public org.lwjgl.util.vector.Vector3f Get() {
 org.lwjgl.util.vector.Vector3f vector3f = new org.lwjgl.util.vector.Vector3f();
 vector3f.set(this->x, this->y, this->z);
 return vector3f;
 }

 void Set(org.lwjgl.util.vector.Vector3f vector3f) {
 this->x = vector3f.x;
 this->y = vector3f.y;
 this->z = vector3f.z;
 }

 Vector3 reset() {
 this->x = this->y = this->z = 0.0F;
 return this;
 }

 float dot(Vector3 vector30) {
 return this->x * vector30.x + this->y * vector30.y + this->z * vector30.z;
 }

 Vector3 cross(Vector3 vector31) {
 return new Vector3(
 this->y() * vector31.z() - vector31.y() * this->z(),
 vector31.z() * this->x() - this->z() * vector31.x(),
 this->x() * vector31.y() - vector31.x() * this->y()
 );
 }
}
} // namespace math
} // namespace core
} // namespace zombie
