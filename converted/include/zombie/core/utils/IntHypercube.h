#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IntHypercube {
public:
 static const long serialVersionUID = 1L;
 const int width;
 const int height;
 const int depth;
 const int quanta;
 const int wxh;
 const int wxhxd;
 private int[] value;

 public IntHypercube(int int0, int int1, int int2, int int3) {
 this->width = int0;
 this->height = int1;
 this->depth = int2;
 this->quanta = int3;
 this->wxh = int0 * int1;
 this->wxhxd = this->wxh * int2;
 this->value = new int[this->wxhxd * int3];
 }

 IntHypercube clone() {
 IntHypercube intHypercube0 = new IntHypercube(this->width, this->height, this->depth, this->quanta);
 System.arraycopy(this->value, 0, intHypercube0.value, 0, this->value.length);
 return intHypercube0;
 }

 void clear() {
 Arrays.fill(this->value, 0);
 }

 void fill(int int0) {
 Arrays.fill(this->value, int0);
 }

 int getIndex(int int2, int int3, int int1, int int0) {
 return int2 >= 0 && int3 >= 0 && int1 >= 0 && int0 >= 0 && int2 < this->width && int3 < this->height && int1 < this->depth && int0 < this->quanta
 ? int2 + int3 * this->width + int1 * this->wxh + int0 * this->wxhxd
 : -1;
 }

 int getValue(int int1, int int2, int int3, int int4) {
 int int0 = this->getIndex(int1, int2, int3, int4);
 return int0 = = -1 ? 0 : this->value[int0];
 }

 void setValue(int int1, int int2, int int3, int int4, int int5) {
 int int0 = this->getIndex(int1, int2, int3, int4);
 if (int0 != -1) {
 this->value[int0] = int5;
 }
 }

 int getWidth() {
 return this->width;
 }

 int getHeight() {
 return this->height;
 }

 int getDepth() {
 return this->depth;
 }

 int getQuanta() {
 return this->quanta;
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
