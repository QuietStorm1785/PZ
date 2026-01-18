#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYATI on 03/01/14.
 */
class Vector3 {
public:
 float x;
 float y;
 float z;

public
 Vector3() { this(0.0F, 0.0F, 0.0F); }

public
 Vector3(float _x, float _y, float _z) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 }

public
 Vector3(Vector3 vec) { this->set(vec); }

 float x() { return this->x; }

 Vector3 x(float _x) {
 this->x = _x;
 return this;
 }

 float y() { return this->y; }

 Vector3 y(float _y) {
 this->y = _y;
 return this;
 }

 float z() { return this->z; }

 Vector3 z(float _z) {
 this->z = _z;
 return this;
 }

 Vector3 set(float _x, float _y, float _z) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 return this;
 }

 Vector3 set(Vector3 vec) { return this->set(vec.x(), vec.y(), vec.z()); }

 Vector3 reset() {
 this->x = this->y = this->z = 0.0F;
 return this;
 }

 float length() {
 return (float)Math.sqrt(this->x * this->x + this->y * this->y +
 this->z * this->z);
 }

 Vector3 normalize() {
 float float0 = this->length();
 this->x /= float0;
 this->y /= float0;
 this->z /= float0;
 return this;
 }

 float dot(Vector3 vec) {
 return this->x * vec.x + this->y * vec.y + this->z * vec.z;
 }

 Vector3 cross(Vector3 vec) {
 return new Vector3(this->y() * vec.z() - vec.y() * this->z(),
 vec.z() * this->x() - this->z() * vec.x(),
 this->x() * vec.y() - vec.x() * this->y());
 }

 Vector3 add(float _x, float _y, float _z) {
 this->x += _x;
 this->y += _y;
 this->z += _z;
 return this;
 }

 Vector3 add(Vector3 vec) { return this->add(vec.x(), vec.y(), vec.z()); }

 Vector3 sub(float _x, float _y, float _z) {
 this->x -= _x;
 this->y -= _y;
 this->z -= _z;
 return this;
 }

 Vector3 sub(Vector3 vec) { return this->sub(vec.x(), vec.y(), vec.z()); }

 Vector3 mul(float f) { return this->mul(f, f, f); }

 Vector3 mul(float _x, float _y, float _z) {
 this->x *= _x;
 this->y *= _y;
 this->z *= _z;
 return this;
 }

 Vector3 mul(Vector3 vec) { return this->mul(vec.x(), vec.y(), vec.z()); }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
