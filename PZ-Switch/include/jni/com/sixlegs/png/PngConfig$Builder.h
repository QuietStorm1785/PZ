#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Rectangle.h"

namespace com {
namespace sixlegs {
namespace png {


class PngConfig {
:
   private static int[] DEFAULT_SUBSAMPLING = new int[]{1, 1, 0, 0};
    int readLimit = 0;
    float defaultGamma = 0.45455F;
    float displayExponent = 2.2F;
    bool warningsFatal;
    bool progressive;
    bool reduce16 = true;
    bool gammaCorrect = true;
    Rectangle sourceRegion;
   int[] subsampling = DEFAULT_SUBSAMPLING;
    bool convertIndexed;

    PngConfig$Builder() {
   }

    PngConfig$Builder(PngConfig var1) {
      this.readLimit = var1.readLimit;
      this.defaultGamma = var1.defaultGamma;
      this.displayExponent = var1.displayExponent;
      this.warningsFatal = var1.warningsFatal;
      this.progressive = var1.progressive;
      this.reduce16 = var1.reduce16;
      this.gammaCorrect = var1.gammaCorrect;
      this.subsampling = var1.subsampling;
   }

    PngConfig build() {
      return new PngConfig(this);
   }

    PngConfig$Builder reduce16(boolean var1) {
      this.reduce16 = var1;
    return this;
   }

    PngConfig$Builder defaultGamma(float var1) {
      this.defaultGamma = var1;
    return this;
   }

    PngConfig$Builder displayExponent(float var1) {
      this.displayExponent = var1;
    return this;
   }

    PngConfig$Builder gammaCorrect(boolean var1) {
      this.gammaCorrect = var1;
    return this;
   }

    PngConfig$Builder progressive(boolean var1) {
      this.progressive = var1;
    return this;
   }

    PngConfig$Builder readLimit(int var1) {
      this.readLimit = var1;
    return this;
   }

    PngConfig$Builder warningsFatal(boolean var1) {
      this.warningsFatal = var1;
    return this;
   }

    PngConfig$Builder sourceRegion(Rectangle var1) {
      if (var1 != nullptr) {
         if (var1.x < 0 || var1.y < 0 || var1.width <= 0 || var1.height <= 0) {
            throw IllegalArgumentException("invalid source region: " + var1);
         }

         this.sourceRegion = new Rectangle(var1);
      } else {
         this.sourceRegion = nullptr;
      }

    return this;
   }

    PngConfig$Builder sourceSubsampling(int var1, int var2, int var3, int var4) {
      if (var1 > 0 && var2 > 0 && var3 >= 0 && var3 < var1 && var4 >= 0 && var4 < var2) {
         this.subsampling = new int[]{var1, var2, var3, var4};
    return this;
      } else {
         throw IllegalArgumentException("invalid subsampling values");
      }
   }

    PngConfig$Builder convertIndexed(boolean var1) {
      this.convertIndexed = var1;
    return this;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
