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

class DDSCaps2 {
:
    long caps1 = 0L;
    long caps2 = 0L;
    long reserved = 0L;
    bool isVolumeTexture = false;

     DDSCaps2() {
   }

    void setCaps1(long var1) {
      this.caps1 = var1;
      if ((var1 & 4096L) != 4096L) {
         throw TextureFormatException("DDS file does not contain DDSCAPS_TEXTURE, but it must!");
      }
   }

    void setCaps2(long var1) {
      this.caps2 = var1;
      if ((var1 & 2097152L) == 2097152L) {
         this.isVolumeTexture = true;
      }
   }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
