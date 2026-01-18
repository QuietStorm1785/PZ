#pragma once
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Boolean grid
 */
class BooleanGrid {
public:
 static const long serialVersionUID = 1L;
 const int width;
 const int height;
 const int bitWidth;
private
 int[] value;

 /**
 * C'tor
 */
public
 BooleanGrid(int _width, int _height) {
 this->bitWidth = _width;
 this->width = _width / 32 + (_width % 32 != 0 ? 1 : 0);
 this->height = _height;
 this->value = new int[this->width * this->height];
 }

 BooleanGrid clone() {
 BooleanGrid booleanGrid0 = new BooleanGrid(this->bitWidth, this->height);
 System.arraycopy(this->value, 0, booleanGrid0.value, 0, this->value.length);
 return booleanGrid0;
 }

 void copy(BooleanGrid src) {
 if (src.bitWidth == this->bitWidth && src.height == this->height) {
 System.arraycopy(src.value, 0, this->value, 0, src.value.length);
 } else {
 throw IllegalArgumentException(
 "src must be same size as this: " + src + " cannot be copied into " +
 this);
 }
 }

 void clear() { Arrays.fill(this->value, 0); }

 void fill() { Arrays.fill(this->value, -1); }

 int getIndex(int int0, int int1) {
 return int0 >= 0 && int1 >= 0 && int0 < this->width && int1 < this->height
 ? int0 + int1 * this->width
 : -1;
 }

 bool getValue(int x, int y) {
 if (x < this->bitWidth && x >= 0 && y < this->height && y >= 0) {
 int int0 = x / 32;
 int int1 = 1 << (x & 31);
 int int2 = this->getIndex(int0, y);
 if (int2 == -1) {
 return false;
 } else {
 int int3 = this->value[int2];
 return (int3 & int1) != 0;
 }
 } else {
 return false;
 }
 }

 void setValue(int x, int y, bool newValue) {
 if (x < this->bitWidth && x >= 0 && y < this->height && y >= 0) {
 int int0 = x / 32;
 int int1 = 1 << (x & 31);
 int int2 = this->getIndex(int0, y);
 if (int2 != -1) {
 if (newValue) {
 this->value[int2] = this->value[int2] | int1;
 } else {
 this->value[int2] = this->value[int2] & ~int1;
 }
 }
 }
 }

 /**
 * @return the width
 */
 int getWidth() { return this->width; }

 /**
 * @return the height
 */
 int getHeight() { return this->height; }

 std::string toString() {
 return "BooleanGrid [width=" + this->width + ", height=" + this->height +
 ", bitWidth=" + this->bitWidth + "]";
 }

 void LoadFromByteBuffer(ByteBuffer cache) {
 int int0 = this->width * this->height;

 for (int int1 = 0; int1 < int0; int1++) {
 this->value[int1] = cache.getInt();
 }
 }

 void PutToByteBuffer(ByteBuffer cache) {
 int int0 = this->width * this->height;

 for (int int1 = 0; int1 < int0; int1++) {
 cache.putInt(this->value[int1]);
 }
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
