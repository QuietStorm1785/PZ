#pragma once
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
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AlphaColorIndex {
public:
  uint8_t alpha;
  uint8_t blue;
  uint8_t green;
  uint8_t red;

  AlphaColorIndex(int int0, int int1, int int2, int int3) {
    this.red = (byte)int0;
    this.green = (byte)int1;
    this.blue = (byte)int2;
    this.alpha = (byte)int3;
  }
}
} // namespace textures
} // namespace core
} // namespace zombie
