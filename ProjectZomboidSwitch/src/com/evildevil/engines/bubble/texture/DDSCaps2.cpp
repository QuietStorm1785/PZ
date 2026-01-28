#include "com/evildevil/engines/bubble/texture/DDSCaps2.h"
#include "com/evildevil/engines/bubble/texture/TextureFormatException.h"

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

DDSCaps2::DDSCaps2() : caps1(0L), caps2(0L), reserved(0L), isVolumeTexture(false) {}

void DDSCaps2::setCaps1(long var1) {
    caps1 = var1;
    if ((var1 & 4096L) != 4096L) {
        throw TextureFormatException("DDS file does not contain DDSCAPS_TEXTURE, but it must!");
    }
}

void DDSCaps2::setCaps2(long var1) {
    caps2 = var1;
    if ((var1 & 2097152L) == 2097152L) {
        isVolumeTexture = true;
    }
}

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
