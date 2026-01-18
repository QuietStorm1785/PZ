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

class DDSCaps2 {
public:
 long caps1 = 0L;
 long caps2 = 0L;
 long reserved = 0L;
 bool isVolumeTexture = false;

 public DDSCaps2() {
 }

 void setCaps1(long long0) {
 this->caps1 = long0;
 if ((long0 & 4096L) != 4096L) {
 throw TextureFormatException("DDS file does not contain DDSCAPS_TEXTURE, but it must!");
 }
 }

 void setCaps2(long long0) {
 this->caps2 = long0;
 if ((long0 & 2097152L) == 2097152L) {
 this->isVolumeTexture = true;
 }
 }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
