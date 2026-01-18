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


class ObjectGrid {
public:
 static const long serialVersionUID = 1L;
 const int width;
 const int height;
 private Object[] value;

 public ObjectGrid(int int0, int int1) {
 this->width = int0;
 this->height = int1;
 this->value = new Object[int0 * int1];
 }

 public ObjectGrid<T> clone() throws CloneNotSupportedException {
 ObjectGrid objectGrid0 = new ObjectGrid(this->width, this->height);
 System.arraycopy(this->value, 0, objectGrid0.value, 0, this->value.length);
 return objectGrid0;
 }

 void clear() {
 Arrays.fill(this->value, Integer.valueOf(0);
 }

 void fill(T object) {
 Arrays.fill(this->value, object);
 }

 int getIndex(int int0, int int1) {
 return int0 >= 0 && int1 >= 0 && int0 < this->width && int1 < this->height ? int0 + int1 * this->width : -1;
 }

 T getValue(int int1, int int2) {
 int int0 = this->getIndex(int1, int2);
 return (T)(int0 == -1 ? nullptr : this->value[int0]);
 }

 void setValue(int int1, int int2, T object) {
 int int0 = this->getIndex(int1, int2);
 if (int0 != -1) {
 this->value[int0] = object;
 }
 }

 int getWidth() {
 return this->width;
 }

 int getHeight() {
 return this->height;
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
