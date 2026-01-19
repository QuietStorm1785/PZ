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

class DDSurfaceDesc2 {
:
    const std::string DDS_IDENTIFIER = "DDS ";
    long identifier = 0L;
    std::string identifierString = "";
    long size = 0L;
    long flags = 0L;
    long height = 0L;
    long width = 0L;
    long pitchOrLinearSize = 0L;
    long depth = 0L;
    long mipMapCount = 0L;
    long reserved = 0L;
    DDPixelFormat pixelFormat = nullptr;
    DDSCaps2 caps2 = nullptr;
    int reserved2 = 0;

     DDSurfaceDesc2() {
      this.pixelFormat = std::make_unique<DDPixelFormat>();
      this.caps2 = std::make_unique<DDSCaps2>();
   }

    void setIdentifier(long var1) {
      this.identifier = var1;
      this.createIdentifierString();
   }

    void createIdentifierString() {
      byte[] var1 = new byte[]{(byte)this.identifier, (byte)(this.identifier >> 8), (byte)(this.identifier >> 16), (byte)(this.identifier >> 24)};
      this.identifierString = new String(var1);
      if (!this.identifierString.equalsIgnoreCase("DDS ")) {
         throw TextureFormatException("The DDS Identifier is wrong. Have to be \"DDS \"!");
      }
   }

    void setSize(long var1) {
      if (var1 != 124L) {
         throw TextureFormatException("Wrong DDSurfaceDesc2 size. DDSurfaceDesc2 size must be 124!");
      } else {
         this.size = var1;
      }
   }

    void setFlags(long var1) {
      this.flags = var1;
      if ((var1 & 1L) != 1L || (var1 & 4096L) != 4096L || (var1 & 4L) != 4L || (var1 & 2L) != 2L) {
         throw TextureFormatException(
            "One or more required flag bits are set wrong\nflags have to include \"DDSD_CAPS, DDSD_PIXELFORMAT, DDSD_WIDTH, DDSD_HEIGHT\""
         );
      }
   }

    void setHeight(long var1) {
      this.height = Math.abs(var1);
   }

    void setWidth(long var1) {
      this.width = var1;
   }

    void setPitchOrLinearSize(long var1) {
      this.pitchOrLinearSize = var1;
      this.pitchOrLinearSize = (this.width + 3L) / 4L * ((this.height + 3L) / 4L) * 16L;
      if (this.pitchOrLinearSize > 1000000L) {
         this.pitchOrLinearSize = (this.width + 3L) / 4L * ((this.height + 3L) / 4L) * 16L;
      }
   }

    void setDepth(long var1) {
      this.depth = var1;
   }

    void setMipMapCount(long var1) {
      this.mipMapCount = var1;
   }

    void setDDPixelFormat(DDPixelFormat var1) {
      if (var1 == nullptr) {
         throw NullPointerException("DDPixelFormat can't be nullptr. DDSurfaceDesc2 needs a valid DDPixelFormat.");
      } else {
         this.pixelFormat = var1;
      }
   }

    DDPixelFormat getDDPixelformat() const {
      return this.pixelFormat;
   }

    void setDDSCaps2(DDSCaps2 var1) {
      if (var1 == nullptr) {
         throw NullPointerException("DDSCaps can't be nullptr. DDSurfaceDesc2 needs a valid DDSCaps2.");
      } else {
         this.caps2 = var1;
      }
   }

    DDSCaps2 getDDSCaps2() const {
      return this.caps2;
   }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
