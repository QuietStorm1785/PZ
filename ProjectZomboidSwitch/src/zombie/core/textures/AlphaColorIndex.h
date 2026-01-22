#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class AlphaColorIndex {
public:
    uint8_t alpha;
    uint8_t blue;
    uint8_t green;
    uint8_t red;

   AlphaColorIndex(int var1, int var2, int var3, int var4) {
      this.red = (byte)var1;
      this.green = (byte)var2;
      this.blue = (byte)var3;
      this.alpha = (byte)var4;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
