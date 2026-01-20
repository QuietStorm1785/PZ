#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {

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
