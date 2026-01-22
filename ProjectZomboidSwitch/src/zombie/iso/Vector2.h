#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Dimension.h"
#include "java/awt/Point.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace iso {


class Vector2 {
public:
    float x;
    float y;

    public Vector2() {
      this.x = 0.0F;
      this.y = 0.0F;
   }

    public Vector2(Vector2 var1) {
      this.x = var1.x;
      this.y = var1.y;
   }

    public Vector2(float var1, float var2) {
      this.x = var1;
      this.y = var2;
   }

    static Vector2 fromAwtPoint(Point var0) {
      return std::make_shared<Vector2>(var0.x, var0.y);
   }

    static Vector2 fromLengthDirection(float var0, float var1) {
    Vector2 var2 = std::make_shared<Vector2>();
      var2.setLengthAndDirection(var1, var0);
    return var2;
   }

    static float dot(float var0, float var1, float var2, float var3) {
      return var0 * var2 + var1 * var3;
   }

    static Vector2 addScaled(Vector2 var0, Vector2 var1, float var2, Vector2 var3) {
      var3.set(var0.x + var1.x * var2, var0.y + var1.y * var2);
    return var3;
   }

    void rotate(float var1) {
    double var2 = this.x * Math.cos(var1) - this.y * Math.sin(var1);
    double var4 = this.x * Math.sin(var1) + this.y * Math.cos(var1);
      this.x = (float)var2;
      this.y = (float)var4;
   }

    Vector2 add(Vector2 var1) {
      this.x = this.x + var1.x;
      this.y = this.y + var1.y;
    return this;
   }

    Vector2 aimAt(Vector2 var1) {
      this.setLengthAndDirection(this.angleTo(var1), this.getLength());
    return this;
   }

    float angleTo(Vector2 var1) {
      return (float)Math.atan2(var1.y - this.y, var1.x - this.x);
   }

    float angleBetween(Vector2 var1) {
    float var2 = this.dot(var1) / (this.getLength() * var1.getLength());
      if (var2 < -1.0F) {
         var2 = -1.0F;
      }

      if (var2 > 1.0F) {
         var2 = 1.0F;
      }

      return (float)Math.acos(var2);
   }

    Vector2 clone() {
      return std::make_shared<Vector2>(this);
   }

    float distanceTo(Vector2 var1) {
      return (float)Math.sqrt(Math.pow(var1.x - this.x, 2.0) + Math.pow(var1.y - this.y, 2.0));
   }

    float dot(Vector2 var1) {
      return this.x * var1.x + this.y * var1.y;
   }

    bool equals(void* var1) {
      return !(dynamic_cast<Vector2*>(var1) != nullptr var2) ? false : var2.x == this.x && var2.y == this.y;
   }

    float getDirection() {
    float var1 = (float)Math.atan2(this.y, this.x);
      return PZMath.wrap(var1, (float) -Math.PI, (float) Math.PI);
   }

    static float getDirection(float var0, float var1) {
    float var2 = (float)Math.atan2(var1, var0);
      return PZMath.wrap(var2, (float) -Math.PI, (float) Math.PI);
   }

    float getDirectionNeg() {
      return (float)Math.atan2(this.x, this.y);
   }

    Vector2 setDirection(float var1) {
      this.setLengthAndDirection(var1, this.getLength());
    return this;
   }

    float getLength() {
      return (float)Math.sqrt(this.x * this.x + this.y * this.y);
   }

    float getLengthSquared() {
      return this.x * this.x + this.y * this.y;
   }

    Vector2 setLength(float var1) {
      this.normalize();
      this.x *= var1;
      this.y *= var1;
    return this;
   }

    float normalize() {
    float var1 = this.getLength();
      if (var1 == 0.0F) {
         this.x = 0.0F;
         this.y = 0.0F;
      } else {
         this.x /= var1;
         this.y /= var1;
      }

    return var1;
   }

    Vector2 set(Vector2 var1) {
      this.x = var1.x;
      this.y = var1.y;
    return this;
   }

    Vector2 set(float var1, float var2) {
      this.x = var1;
      this.y = var2;
    return this;
   }

    Vector2 setLengthAndDirection(float var1, float var2) {
      this.x = (float)(Math.cos(var1) * var2);
      this.y = (float)(Math.sin(var1) * var2);
    return this;
   }

    Dimension toAwtDimension() {
      return std::make_shared<Dimension>((int)this.x, (int)this.y);
   }

    Point toAwtPoint() {
      return std::make_shared<Point>((int)this.x, (int)this.y);
   }

    std::string toString() {
      return std::string.format("Vector2 (X: %f, Y: %f) (L: %f, D:%f)", this.x, this.y, this.getLength(), this.getDirection());
   }

    float getX() {
      return this.x;
   }

    void setX(float var1) {
      this.x = var1;
   }

    float getY() {
      return this.y;
   }

    void setY(float var1) {
      this.y = var1;
   }

    void tangent() {
    double var1 = this.x * Math.cos(Math.toRadians(90.0)) - this.y * Math.sin(Math.toRadians(90.0));
    double var3 = this.x * Math.sin(Math.toRadians(90.0)) + this.y * Math.cos(Math.toRadians(90.0));
      this.x = (float)var1;
      this.y = (float)var3;
   }

    void scale(float var1) {
      scale(this, var1);
   }

    static Vector2 scale(Vector2 var0, float var1) {
      var0.x *= var1;
      var0.y *= var1;
    return var0;
   }
}
} // namespace iso
} // namespace zombie
