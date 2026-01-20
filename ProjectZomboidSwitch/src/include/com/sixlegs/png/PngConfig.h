#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sixlegs/png/PngConfig/Builder.h"
#include "java/awt/Rectangle.h"

namespace com {
namespace sixlegs {
namespace png {


class PngConfig {
public:
    static const int READ_ALL = 0;
    static const int READ_HEADER = 1;
    static const int READ_UNTIL_DATA = 2;
    static const int READ_EXCEPT_DATA = 3;
    static const int READ_EXCEPT_METADATA = 4;
    const int readLimit;
    const float defaultGamma;
    const float displayExponent;
    const bool warningsFatal;
    const bool progressive;
    const bool reduce16;
    const bool gammaCorrect;
    const Rectangle sourceRegion;
   const int[] subsampling;
    const bool convertIndexed;

   PngConfig(Builder var1) {
      this.readLimit = var1.readLimit;
      this.defaultGamma = var1.defaultGamma;
      this.displayExponent = var1.displayExponent;
      this.warningsFatal = var1.warningsFatal;
      this.progressive = var1.progressive;
      this.reduce16 = var1.reduce16;
      this.gammaCorrect = var1.gammaCorrect;
      this.sourceRegion = var1.sourceRegion;
      this.subsampling = var1.subsampling;
      this.convertIndexed = var1.convertIndexed;
    bool var2 = this.getSourceXSubsampling() != 1 || this.getSourceYSubsampling() != 1;
      if (this.progressive && (var2 || this.getSourceRegion() != nullptr)) {
         throw IllegalStateException("Progressive rendering cannot be used with source regions or subsampling");
      }
   }

    bool getConvertIndexed() {
      return this.convertIndexed;
   }

    bool getReduce16() {
      return this.reduce16;
   }

    float getDefaultGamma() {
      return this.defaultGamma;
   }

    bool getGammaCorrect() {
      return this.gammaCorrect;
   }

    bool getProgressive() {
      return this.progressive;
   }

    float getDisplayExponent() {
      return this.displayExponent;
   }

    int getReadLimit() {
      return this.readLimit;
   }

    bool getWarningsFatal() {
      return this.warningsFatal;
   }

    Rectangle getSourceRegion() {
      return this.sourceRegion != nullptr ? std::make_shared<Rectangle>(this.sourceRegion) : nullptr;
   }

    int getSourceXSubsampling() {
      return this.subsampling[0];
   }

    int getSourceYSubsampling() {
      return this.subsampling[1];
   }

    int getSubsamplingXOffset() {
      return this.subsampling[2];
   }

    int getSubsamplingYOffset() {
      return this.subsampling[3];
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
