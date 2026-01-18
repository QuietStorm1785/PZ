#pragma once
#include <algorithm>
#include <cstdint>
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

class IntGrid {
public:
 static const long serialVersionUID = 1L;
 const int width;
 const int height;
private
 int[] value;

 /**
 * C'tor
 */
public
 IntGrid(int _width, int _height) {
 this->width = _width;
 this->height = _height;
 this->value = new int[_width * _height];
 }

 IntGrid clone() {
 IntGrid intGrid0 = new IntGrid(this->width, this->height);
 System.arraycopy(this->value, 0, intGrid0.value, 0, this->value.length);
 return intGrid0;
 }

 void clear() { Arrays.fill(this->value, 0); }

 void fill(int newValue) { Arrays.fill(this->value, newValue); }

 int getIndex(int int0, int int1) {
 return int0 >= 0 && int1 >= 0 && int0 < this->width && int1 < this->height
 ? int0 + int1 * this->width
 : -1;
 }

 int getValue(int x, int y) {
 int int0 = this->getIndex(x, y);
 return int0 = = -1 ? 0 : this->value[int0];
 }

 void setValue(int x, int y, int newValue) {
 int int0 = this->getIndex(x, y);
 if (int0 != -1) {
 this->value[int0] = newValue;
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
}
} // namespace utils
} // namespace core
} // namespace zombie
