#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ObjectCube {
public:
 const int width;
 const int height;
 const int depth;
 private Object[] value;

 public ObjectCube(int int1, int int2, int int0) {
 DebugLog.log("Created object cube of size " + int1 + "x" + int2 + "x" + int0 + " (" + int1 * int2 * int0 * 4 + " bytes)");
 this->width = int1;
 this->height = int2;
 this->depth = int0;
 this->value = new Object[int1 * int2 * int0];
 }

 public ObjectCube<T> clone() throws CloneNotSupportedException {
 ObjectCube objectCube0 = new ObjectCube(this->width, this->height, this->depth);
 System.arraycopy(this->value, 0, objectCube0.value, 0, this->value.length);
 return objectCube0;
 }

 void clear() {
 Arrays.fill(this->value, nullptr);
 }

 void fill(T object) {
 Arrays.fill(this->value, object);
 }

 int getIndex(int int1, int int2, int int0) {
 return int1 >= 0 && int2 >= 0 && int0 >= 0 && int1 < this->width && int2 < this->height && int0 < this->depth
 ? int1 + int2 * this->width + int0 * this->width * this->height
 : -1;
 }

 T getValue(int int1, int int2, int int3) {
 int int0 = this->getIndex(int1, int2, int3);
 return (T)(int0 == -1 ? nullptr : this->value[int0]);
 }

 void setValue(int int1, int int2, int int3, T object) {
 int int0 = this->getIndex(int1, int2, int3);
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

 int getDepth() {
 return this->depth;
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
