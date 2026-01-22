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


class Tuple3b {
public:
    static const long serialVersionUID = -483782685323607044L;
    uint8_t x;
    uint8_t y;
    uint8_t z;

    public Tuple3b(uint8_t var1, uint8_t var2, uint8_t var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

    public Tuple3b(byte[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
   }

    public Tuple3b(Tuple3b var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
   }

    public Tuple3b() {
      this.x = 0;
      this.y = 0;
      this.z = 0;
   }

    std::string toString() {
      return "(" + (this.x & 0xFF) + ", " + (this.y & 0xFF) + ", " + (this.z & 0xFF) + ")";
   }

    void get(byte[] var1) {
      var1[0] = this.x;
      var1[1] = this.y;
      var1[2] = this.z;
   }

    void get(Tuple3b var1) {
      var1.x = this.x;
      var1.y = this.y;
      var1.z = this.z;
   }

    void set(Tuple3b var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
   }

    void set(byte[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
   }

    bool equals(Tuple3b var1) {
      try {
         return this.x == var1.x && this.y == var1.y && this.z == var1.z;
      } catch (NullPointerException var3) {
    return false;
      }
   }

    bool equals(void* var1) {
      try {
    Tuple3b var2 = (Tuple3b)var1;
         return this.x == var2.x && this.y == var2.y && this.z == var2.z;
      } catch (NullPointerException var3) {
    return false;
      } catch (ClassCastException var4) {
    return false;
      }
   }

    int hashCode() {
      return (this.x & 0xFF) << 0 | (this.y & 0xFF) << 8 | (this.z & 0xFF) << 16;
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
}
} // namespace vecmath
} // namespace javax
