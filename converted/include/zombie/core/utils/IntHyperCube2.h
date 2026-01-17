#pragma once
#include <algorithm>
#include <cstdint>
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

class IntHyperCube2 {
public:
  static const long serialVersionUID = 1L;
  const int width;
  const int height;
  const int depth;
  const int quanta;
  const int wxh;
  const int wxhxd;
private
  final int[][][][] value;

public
  IntHyperCube2(int int0, int int1, int int2, int int3) {
    this.width = int0;
    this.height = int1;
    this.depth = int2;
    this.quanta = int3;
    this.wxh = int0 * int1;
    this.wxhxd = this.wxh * int2;
    this.value = new int[int0][int1][int2][int3];
  }

  void clear() { Arrays.fill(this.value, Integer.valueOf(0)); }

  void fill(int int0) { Arrays.fill(this.value, Integer.valueOf(int0)); }

  int getIndex(int int2, int int3, int int1, int int0) {
    return int2 >= 0 && int3 >= 0 && int1 >= 0 && int0 >= 0 &&
                   int2 < this.width && int3 < this.height &&
                   int1 < this.depth && int0 < this.quanta
               ? int2 + int3 * this.width + int1 * this.wxh + int0 * this.wxhxd
               : -1;
  }

  int getValue(int int3, int int2, int int1, int int0) {
    return int3 >= 0 && int2 >= 0 && int1 >= 0 && int0 >= 0 &&
                   int3 < this.width && int2 < this.height &&
                   int1 < this.depth && int0 < this.quanta
               ? this.value[int3][int2][int1][int0]
               : 0;
  }

  void setValue(int int4, int int3, int int2, int int1, int int0) {
    this.value[int4][int3][int2][int1] = int0;
  }

  int getWidth() { return this.width; }

  int getHeight() { return this.height; }

  int getDepth() { return this.depth; }

  int getQuanta() { return this.quanta; }
}
} // namespace utils
} // namespace core
} // namespace zombie
