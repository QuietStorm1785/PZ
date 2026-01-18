#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureFlags {
public:
 static const int NONE = 0;
 static const int FILTER_MIN_NEAREST = 1;
 static const int FILTER_MAG_NEAREST = 2;
 static const int COMPRESS = 4;
 static const int CREATE_MASK = 8;
 static const int FBO = 16;
 static const int CLAMP_TO_EDGE = 32;
 static const int MIPMAPS = 64;
 static const int LIMIT_TEXTURE_SIZE_1 = 128;
 static const int LIMIT_TEXTURE_SIZE_2 = 256;
}
} // namespace textures
} // namespace core
} // namespace zombie
