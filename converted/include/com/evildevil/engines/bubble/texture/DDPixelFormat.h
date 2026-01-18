#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class DDPixelFormat {
public:
 long size = 0L;
 long flags = 0L;
 long fourCC = 0L;
 std::string fourCCString = "";
 long rgbBitCount = 0L;
 long rBitMask = 0L;
 long gBitMask = 0L;
 long bBitMask = 0L;
 long rgbAlphaBitMask = 0L;
 bool isCompressed = true;

 public DDPixelFormat() {
 }

 void setSize(long long0) {
 if (long0 != 32L) {
 throw TextureFormatException("Wrong DDPixelFormat size. DDPixelFormat size must be 32!");
 } else {
 this->size = long0;
 }
 }

 void setFlags(long long0) {
 this->flags = long0;
 if ((long0 & 64L) == 64L) {
 this->isCompressed = false;
 } else if ((long0 & 4L) == 4L) {
 this->isCompressed = true;
 }
 }

 void setFourCC(long long0) {
 this->fourCC = long0;
 if (this->isCompressed) {
 this->createFourCCString();
 }
 }

 void createFourCCString() {
 byte[] bytes = new byte[]{(byte)this->fourCC, (byte)(this->fourCC >> 8), (byte)(this->fourCC >> 16), (byte)(this->fourCC >> 24)};
 this->fourCCString = new String(bytes);
 }

 std::string getFourCCString() {
 return this->fourCCString;
 }

 void setRGBBitCount(long long0) {
 this->rgbAlphaBitMask = long0;
 }

 void setRBitMask(long long0) {
 this->rBitMask = long0;
 }

 void setGBitMask(long long0) {
 this->gBitMask = long0;
 }

 void setBBitMask(long long0) {
 this->bBitMask = long0;
 }

 void setRGBAlphaBitMask(long long0) {
 this->rgbAlphaBitMask = long0;
 }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
