#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {

class Vector3 {
public:
    float x;
    float y;
    float z;

    public Vector3() {
      this(0.0F, 0.0F, 0.0F);
   }

    public Vector3(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

    public Vector3(Vector3 var1) {
      this.set(var1);
   }

    float x() {
      return this.x;
   }

    Vector3 x(float var1) {
      this.x = var1;
    return this;
   }

    float y() {
      return this.y;
   }

    Vector3 y(float var1) {
      this.y = var1;
    return this;
   }

    float z() {
      return this.z;
   }

    Vector3 z(float var1) {
      this.z = var1;
    return this;
   }

    Vector3 set(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
    return this;
   }

    Vector3 set(Vector3 var1) {
      return this.set(var1.x(), var1.y(), var1.z());
   }

    Vector3 reset() {
      this.x = this.y = this.z = 0.0F;
    return this;
   }

    float length() {
      return (float)Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
   }

    Vector3 normalize() {
    float var1 = this.length();
      this.x /= var1;
      this.y /= var1;
      this.z /= var1;
    return this;
   }

    float dot(Vector3 var1) {
      return this.x * var1.x + this.y * var1.y + this.z * var1.z;
   }

    Vector3 cross(Vector3 var1) {
      return std::make_shared<Vector3>(this.y() * var1.z() - var1.y() * this.z(), var1.z() * this.x() - this.z() * var1.x(), this.x() * var1.y() - var1.x() * this.y());
   }

    Vector3 add(float var1, float var2, float var3) {
      this.x += var1;
      this.y += var2;
      this.z += var3;
    return this;
   }

    Vector3 add(Vector3 var1) {
      return this.push_back(var1.x(), var1.y(), var1.z());
   }

    Vector3 sub(float var1, float var2, float var3) {
      this.x -= var1;
      this.y -= var2;
      this.z -= var3;
    return this;
   }

    Vector3 sub(Vector3 var1) {
      return this.sub(var1.x(), var1.y(), var1.z());
   }

    Vector3 mul(float var1) {
      return this.mul(var1, var1, var1);
   }

    Vector3 mul(float var1, float var2, float var3) {
      this.x *= var1;
      this.y *= var2;
      this.z *= var3;
    return this;
   }

    Vector3 mul(Vector3 var1) {
      return this.mul(var1.x(), var1.y(), var1.z());
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
