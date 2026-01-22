#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class HaloTextHelper {
public:
    int r;
    int g;
    int b;
    int a = 255;

   public HaloTextHelper$ColorRGB(int var1, int var2, int var3) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
   }
}
} // namespace characters
} // namespace zombie
