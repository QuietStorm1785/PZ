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

class Tuple3b {
public:
  static const long serialVersionUID = -483782685323607044L;
  uint8_t x;
  uint8_t y;
  uint8_t z;

public
  Tuple3b(uint8_t byte0, uint8_t byte1, uint8_t byte2) {
    this.x = byte0;
    this.y = byte1;
    this.z = byte2;
  }

public
  Tuple3b(byte[] bytes) {
    this.x = bytes[0];
    this.y = bytes[1];
    this.z = bytes[2];
  }

public
  Tuple3b(Tuple3b tuple3b1) {
    this.x = tuple3b1.x;
    this.y = tuple3b1.y;
    this.z = tuple3b1.z;
  }

public
  Tuple3b() {
    this.x = 0;
    this.y = 0;
    this.z = 0;
  }

  std::string toString() {
    return "(" + (this.x & 0xFF) + ", " + (this.y & 0xFF) + ", " +
           (this.z & 0xFF) + ")";
  }

  void get(byte[] bytes) {
    bytes[0] = this.x;
    bytes[1] = this.y;
    bytes[2] = this.z;
  }

  void get(Tuple3b tuple3b1) {
    tuple3b1.x = this.x;
    tuple3b1.y = this.y;
    tuple3b1.z = this.z;
  }

  void set(Tuple3b tuple3b0) {
    this.x = tuple3b0.x;
    this.y = tuple3b0.y;
    this.z = tuple3b0.z;
  }

  void set(byte[] bytes) {
    this.x = bytes[0];
    this.y = bytes[1];
    this.z = bytes[2];
  }

  bool equals(Tuple3b tuple3b0) {
    try {
      return this.x == tuple3b0.x && this.y == tuple3b0.y &&
             this.z == tuple3b0.z;
    } catch (NullPointerException nullPointerException) {
      return false;
    }
  }

  bool equals(void *object) {
    try {
      Tuple3b tuple3b0 = (Tuple3b)object;
      return this.x == tuple3b0.x && this.y == tuple3b0.y &&
             this.z == tuple3b0.z;
    } catch (NullPointerException nullPointerException) {
      return false;
    } catch (ClassCastException classCastException) {
      return false;
    }
  }

  int hashCode() {
    return (this.x & 0xFF) << 0 | (this.y & 0xFF) << 8 | (this.z & 0xFF) << 16;
  }

  void *clone() {
    try {
      return super.clone();
    } catch (CloneNotSupportedException cloneNotSupportedException) {
      throw std::make_unique<InternalError>();
    }
  }

  uint8_t getX() { return this.x; }

  void setX(uint8_t byte0) { this.x = byte0; }

  uint8_t getY() { return this.y; }

  void setY(uint8_t byte0) { this.y = byte0; }

  uint8_t getZ() { return this.z; }

  void setZ(uint8_t byte0) { this.z = byte0; }
}
} // namespace vecmath
} // namespace javax
