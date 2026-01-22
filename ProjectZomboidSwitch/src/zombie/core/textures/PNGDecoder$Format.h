#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {

enum class PNGDecoder {
   ALPHA(1, true),
   LUMINANCE(1, false),
   LUMINANCE_ALPHA(2, true),
   RGB(3, false),
   RGBA(4, true),
   BGRA(4, true),
   ABGR(4, true);

    const int numComponents;
    const bool hasAlpha;

   private PNGDecoder$Format(int var3, boolean var4) {
      this.numComponents = var3;
      this.hasAlpha = var4;
   }

    int getNumComponents() {
      return this.numComponents;
   }

    bool isHasAlpha() {
      return this.hasAlpha;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
