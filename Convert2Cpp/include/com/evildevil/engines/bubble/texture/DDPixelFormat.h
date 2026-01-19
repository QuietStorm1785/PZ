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

    void setSize(long var1) {
      if (var1 != 32L) {
         throw new TextureFormatException("Wrong DDPixelFormat size. DDPixelFormat size must be 32!");
      } else {
         this.size = var1;
      }
   }

    void setFlags(long var1) {
      this.flags = var1;
      if ((var1 & 64L) == 64L) {
         this.isCompressed = false;
      } else if ((var1 & 4L) == 4L) {
         this.isCompressed = true;
      }
   }

    void setFourCC(long var1) {
      this.fourCC = var1;
      if (this.isCompressed) {
         this.createFourCCString();
      }
   }

    void createFourCCString() {
      std::vector<byte> var1 = std::make_shared<std::vector<byte>>(){(byte)this.fourCC, (byte)(this.fourCC >> 8), (byte)(this.fourCC >> 16), (byte)(this.fourCC >> 24)};
      this.fourCCString = new String(var1);
   }

    std::string getFourCCString() {
      return this.fourCCString;
   }

    void setRGBBitCount(long var1) {
      this.rgbAlphaBitMask = var1;
   }

    void setRBitMask(long var1) {
      this.rBitMask = var1;
   }

    void setGBitMask(long var1) {
      this.gBitMask = var1;
   }

    void setBBitMask(long var1) {
      this.bBitMask = var1;
   }

    void setRGBAlphaBitMask(long var1) {
      this.rgbAlphaBitMask = var1;
   }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
