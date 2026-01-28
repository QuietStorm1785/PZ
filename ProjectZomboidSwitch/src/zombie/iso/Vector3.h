#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace iso {


class Vector3 {
public:
    float x;
    float y;
    float z;

    public Vector3() {
      this.x = 0.0F;
      this.y = 0.0F;
      this.z = 0.0F;
   }

    public Vector3(Vector3 var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
   }

    public Vector3(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

    static Vector2 fromPoint(const Vector2& var0) {
      return Vector2(var0.x, var0.y);
   }

    static Vector2 fromLengthDirection(float var0, float var1) {
    Vector2 var2 = std::make_shared<Vector2>();
      var2.setLengthAndDirection(var1, var0);
    return var2;
   }

    static float dot(float var0, float var1, float var2, float var3) {
      return var0 * var2 + var1 * var3;
   }

    void rotate(float var1) {
    double var2 = this.x * Math.cos(var1) - this.y * Math.sin(var1);
    double var4 = this.x * Math.sin(var1) + this.y * Math.cos(var1);
      this.x = (float)var2;
      this.y = (float)var4;
   }

    void rotatey(float var1) {
    double var2 = this.x * Math.cos(var1) - this.z * Math.sin(var1);
    double var4 = this.x * Math.sin(var1) + this.z * Math.cos(var1);
      this.x = (float)var2;
      this.z = (float)var4;
   }

    Vector2 add(Vector2 var1) {
      return std::make_shared<Vector2>(this.x + var1.x, this.y + var1.y);
   }

    Vector3 addToThis(Vector2 var1) {
      this.x = this.x + var1.x;
      this.y = this.y + var1.y;
    return this;
   }

    Vector3 addToThis(Vector3 var1) {
      this.x = this.x + var1.x;
      this.y = this.y + var1.y;
      this.z = this.z + var1.z;
    return this;
   }

    Vector3 div(float var1) {
      this.x /= var1;
      this.y /= var1;
      this.z /= var1;
    return this;
   }

    Vector3 aimAt(Vector2 var1) {
      this.setLengthAndDirection(this.angleTo(var1), this.getLength());
    return this;
   }

    float angleTo(Vector2 var1) {
      return (float)Math.atan2(var1.y - this.y, var1.x - this.x);
   }

    Vector3 clone() {
      return std::make_shared<Vector3>(this);
   }

    float distanceTo(Vector2 var1) {
      return (float)Math.sqrt(Math.pow(var1.x - this.x, 2.0) + Math.pow(var1.y - this.y, 2.0));
   }

    float dot(Vector2 var1) {
      return this.x * var1.x + this.y * var1.y;
   }

    float dot3d(Vector3 var1) {
      return this.x * var1.x + this.y * var1.y + this.z * var1.z;
   }

    bool equals(void* var1) {
      return !(dynamic_cast<Vector2*>(var1) != nullptr var2) ? false : var2.x == this.x && var2.y == this.y;
   }

    float getDirection() {
      return (float)Math.atan2(this.x, this.y);
   }

    Vector3 setDirection(float var1) {
      this.setLengthAndDirection(var1, this.getLength());
    return this;
   }

    float getLength() {
    float var1 = this.getLengthSq();
      return (float)Math.sqrt(var1);
   }

    float getLengthSq() {
      return this.x * this.x + this.y * this.y + this.z * this.z;
   }

    Vector3 setLength(float var1) {
      this.normalize();
      this.x *= var1;
      this.y *= var1;
      this.z *= var1;
    return this;
   }

    void normalize() {
    float var1 = this.getLength();
      if (var1 == 0.0F) {
         this.x = 0.0F;
         this.y = 0.0F;
         this.z = 0.0F;
      } else {
         this.x /= var1;
         this.y /= var1;
         this.z /= var1;
      }

      var1 = this.getLength();
   }

    Vector3 set(Vector3 var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
    return this;
   }

    Vector3 set(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
    return this;
   }

    Vector3 setLengthAndDirection(float var1, float var2) {
      this.x = (float)(Math.cos(var1) * var2);
      this.y = (float)(Math.sin(var1) * var2);
    return this;
   }

    Dimension toAwtDimension() {
      return std::make_shared<Dimension>((int)this.x, (int)this.y);
   }
      zombie::iso::Vector2 toSize() const {
        return zombie::iso::Vector2(x, y);
      }

    zombie::iso::Vector2 toPoint() const {
      return zombie::iso::Vector2(x, y);
   }

    std::string toString() {
      return std::string.format("Vector2 (X: %f, Y: %f) (L: %f, D:%f)", this.x, this.y, this.getLength(), this.getDirection());
   }

    Vector3 sub(Vector3 var1, Vector3 var2) {
    return sub();
   }

    static Vector3 sub(Vector3 var0, Vector3 var1, Vector3 var2) {
      var2.set(var0.x - var1.x, var0.y - var1.y, var0.z - var1.z);
    return var2;
   }
}
} // namespace iso
} // namespace zombie
