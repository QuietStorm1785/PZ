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


class Tuple4b {
public:
    static const long serialVersionUID = -8226727741811898211L;
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t w;

    public Tuple4b(uint8_t var1, uint8_t var2, uint8_t var3, uint8_t var4) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.w = var4;
   }

    public Tuple4b(byte[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
      this.w = var1[3];
   }

    public Tuple4b(Tuple4b var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.w = var1.w;
   }

    public Tuple4b() {
      this.x = 0;
      this.y = 0;
      this.z = 0;
      this.w = 0;
   }

    std::string toString() {
      return "(" + (this.x & 0xFF) + ", " + (this.y & 0xFF) + ", " + (this.z & 0xFF) + ", " + (this.w & 0xFF) + ")";
   }

    void get(byte[] var1) {
      var1[0] = this.x;
      var1[1] = this.y;
      var1[2] = this.z;
      var1[3] = this.w;
   }

    void get(Tuple4b var1) {
      var1.x = this.x;
      var1.y = this.y;
      var1.z = this.z;
      var1.w = this.w;
   }

    void set(Tuple4b var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.w = var1.w;
   }

    void set(byte[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
      this.w = var1[3];
   }

    bool equals(Tuple4b var1) {
      try {
         return this.x == var1.x && this.y == var1.y && this.z == var1.z && this.w == var1.w;
      } catch (NullPointerException var3) {
    return false;
      }
   }

    bool equals(void* var1) {
      try {
    Tuple4b var2 = (Tuple4b)var1;
         return this.x == var2.x && this.y == var2.y && this.z == var2.z && this.w == var2.w;
      } catch (NullPointerException var3) {
    return false;
      } catch (ClassCastException var4) {
    return false;
      }
   }

    int hashCode() {
      return (this.x & 0xFF) << 0 | (this.y & 0xFF) << 8 | (this.z & 0xFF) << 16 | (this.w & 0xFF) << 24;
   }

    void* clone() {
      try {
         return super.clone();
      } catch (CloneNotSupportedException var2) {
         throw std::make_unique<InternalError>();
      }
   }

    uint8_t getX() {
      return this.x;
   }

    void setX(uint8_t var1) {
      this.x = var1;
   }

    uint8_t getY() {
      return this.y;
   }

    void setY(uint8_t var1) {
      this.y = var1;
   }

    uint8_t getZ() {
      return this.z;
   }

    void setZ(uint8_t var1) {
      this.z = var1;
   }

    uint8_t getW() {
      return this.w;
   }

    void setW(uint8_t var1) {
      this.w = var1;
   }
}
} // namespace vecmath
} // namespace javax
