#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/fileSystem/FileSystem/SubTexture.h"

namespace zombie {
namespace core {
namespace textures {


class TextureID {
public:
    SubTexture subTexture;
    int flags = 0;
}
} // namespace textures
} // namespace core
} // namespace zombie
