#pragma once
#include "java/awt/Rectangle.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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
 int[] subsampling;
 const bool convertIndexed;

 PngConfig(PngConfig.Builder builder) {
 this->readLimit = builder.readLimit;
 this->defaultGamma = builder.defaultGamma;
 this->displayExponent = builder.displayExponent;
 this->warningsFatal = builder.warningsFatal;
 this->progressive = builder.progressive;
 this->reduce16 = builder.reduce16;
 this->gammaCorrect = builder.gammaCorrect;
 this->sourceRegion = builder.sourceRegion;
 this->subsampling = builder.subsampling;
 this->convertIndexed = builder.convertIndexed;
 bool boolean0 =
 this->getSourceXSubsampling() != 1 || this->getSourceYSubsampling() != 1;
 if (this->progressive && (boolean0 || this->getSourceRegion() != nullptr) {
 throw IllegalStateException("Progressive rendering cannot be used "
 "with source regions or subsampling");
 }
 }

 bool getConvertIndexed() { return this->convertIndexed; }

 bool getReduce16() { return this->reduce16; }

 float getDefaultGamma() { return this->defaultGamma; }

 bool getGammaCorrect() { return this->gammaCorrect; }

 bool getProgressive() { return this->progressive; }

 float getDisplayExponent() { return this->displayExponent; }

 int getReadLimit() { return this->readLimit; }

 bool getWarningsFatal() { return this->warningsFatal; }

 Rectangle getSourceRegion() {
 return this->sourceRegion != nullptr ? new Rectangle(this->sourceRegion)
 : nullptr;
 }

 int getSourceXSubsampling() { return this->subsampling[0]; }

 int getSourceYSubsampling() { return this->subsampling[1]; }

 int getSubsamplingXOffset() { return this->subsampling[2]; }

 int getSubsamplingYOffset() { return this->subsampling[3]; }

public
 static class Builder {
 private
 static int[] DEFAULT_SUBSAMPLING = new int[]{1, 1, 0, 0};
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

 public
 Builder() {}

 public
 Builder(PngConfig pngConfig) {
 this->readLimit = pngConfig.readLimit;
 this->defaultGamma = pngConfig.defaultGamma;
 this->displayExponent = pngConfig.displayExponent;
 this->warningsFatal = pngConfig.warningsFatal;
 this->progressive = pngConfig.progressive;
 this->reduce16 = pngConfig.reduce16;
 this->gammaCorrect = pngConfig.gammaCorrect;
 this->subsampling = pngConfig.subsampling;
 }

 PngConfig build() { return new PngConfig(this); }

 public
 PngConfig.Builder reduce16(boolean boolean0) {
 this->reduce16 = boolean0;
 return this;
 }

 public
 PngConfig.Builder defaultGamma(float float0) {
 this->defaultGamma = float0;
 return this;
 }

 public
 PngConfig.Builder displayExponent(float float0) {
 this->displayExponent = float0;
 return this;
 }

 public
 PngConfig.Builder gammaCorrect(boolean boolean0) {
 this->gammaCorrect = boolean0;
 return this;
 }

 public
 PngConfig.Builder progressive(boolean boolean0) {
 this->progressive = boolean0;
 return this;
 }

 public
 PngConfig.Builder readLimit(int int0) {
 this->readLimit = int0;
 return this;
 }

 public
 PngConfig.Builder warningsFatal(boolean boolean0) {
 this->warningsFatal = boolean0;
 return this;
 }

 public
 PngConfig.Builder sourceRegion(Rectangle rectangle) {
 if (rectangle != nullptr) {
 if (rectangle.x < 0 || rectangle.y < 0 || rectangle.width <= 0 ||
 rectangle.height <= 0) {
 throw IllegalArgumentException("invalid source region: " +
 rectangle);
 }

 this->sourceRegion = new Rectangle(rectangle);
 } else {
 this->sourceRegion = nullptr;
 }

 return this;
 }

 public
 PngConfig.Builder sourceSubsampling(int int3, int int1, int int2,
 int int0) {
 if (int3 > 0 && int1 > 0 && int2 >= 0 && int2 < int3 && int0 >= 0 &&
 int0 < int1) {
 this->subsampling = new int[]{int3, int1, int2, int0};
 return this;
 } else {
 throw IllegalArgumentException("invalid subsampling values");
 }
 }

 public
 PngConfig.Builder convertIndexed(boolean boolean0) {
 this->convertIndexed = boolean0;
 return this;
 }
 }
}
} // namespace png
} // namespace sixlegs
} // namespace com
