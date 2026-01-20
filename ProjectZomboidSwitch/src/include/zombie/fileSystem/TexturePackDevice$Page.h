#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TexturePackPage/SubTextureInfo.h"

namespace zombie {
namespace fileSystem {


class TexturePackDevice {
public:
    std::string m_name;
    bool m_has_alpha = false;
    long m_png_start = -1L;
   const std::vector<SubTextureInfo> m_sub = std::make_unique<std::vector<>>();
}
} // namespace fileSystem
} // namespace zombie
