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

class Tuple4b {
public:
 static const long serialVersionUID = -8226727741811898211L;
 uint8_t x;
 uint8_t y;
 uint8_t z;
 uint8_t w;

public
 Tuple4b(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3) {
 this->x = byte0;
 this->y = byte1;
 this->z = byte2;
 this->w = byte3;
 }

public
 Tuple4b(byte[] bytes) {
 this->x = bytes[0];
 this->y = bytes[1];
 this->z = bytes[2];
 this->w = bytes[3];
 }

public
 Tuple4b(Tuple4b tuple4b1) {
 this->x = tuple4b1.x;
 this->y = tuple4b1.y;
 this->z = tuple4b1.z;
 this->w = tuple4b1.w;
 }

public
 Tuple4b() {
 this->x = 0;
 this->y = 0;
 this->z = 0;
 this->w = 0;
 }

 std::string toString() {
 return "(" + (this->x & 0xFF) + ", " + (this->y & 0xFF) + ", " +
 (this->z & 0xFF) + ", " + (this->w & 0xFF) + ")";
 }

 void get(byte[] bytes) {
 bytes[0] = this->x;
 bytes[1] = this->y;
 bytes[2] = this->z;
 bytes[3] = this->w;
 }

 void get(Tuple4b tuple4b1) {
 tuple4b1.x = this->x;
 tuple4b1.y = this->y;
 tuple4b1.z = this->z;
 tuple4b1.w = this->w;
 }

 void set(Tuple4b tuple4b0) {
 this->x = tuple4b0.x;
 this->y = tuple4b0.y;
 this->z = tuple4b0.z;
 this->w = tuple4b0.w;
 }

 void set(byte[] bytes) {
 this->x = bytes[0];
 this->y = bytes[1];
 this->z = bytes[2];
 this->w = bytes[3];
 }

 bool equals(Tuple4b tuple4b0) {
 try {
 return this->x == tuple4b0.x && this->y == tuple4b0.y &&
 this->z == tuple4b0.z && this->w == tuple4b0.w;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }

 bool equals(void *object) {
 try {
 Tuple4b tuple4b0 = (Tuple4b)object;
 return this->x == tuple4b0.x && this->y == tuple4b0.y &&
 this->z == tuple4b0.z && this->w == tuple4b0.w;
 } catch (NullPointerException nullPointerException) {
 return false;
 } catch (ClassCastException classCastException) {
 return false;
 }
 }

 int hashCode() {
 return (this->x & 0xFF) << 0 | (this->y & 0xFF) << 8 | (this->z & 0xFF) << 16 |
 (this->w & 0xFF) << 24;
 }

 void *clone() {
 try {
 return super.clone();
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<InternalError>();
 }
 }

 uint8_t getX() { return this->x; }

 void setX(uint8_t byte0) { this->x = byte0; }

 uint8_t getY() { return this->y; }

 void setY(uint8_t byte0) { this->y = byte0; }

 uint8_t getZ() { return this->z; }

 void setZ(uint8_t byte0) { this->z = byte0; }

 uint8_t getW() { return this->w; }

 void setW(uint8_t byte0) { this->w = byte0; }
}
} // namespace vecmath
} // namespace javax
