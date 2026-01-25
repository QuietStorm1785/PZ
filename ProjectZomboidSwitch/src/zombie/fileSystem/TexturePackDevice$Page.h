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


class Page {
public:
    std::string m_name;
    bool m_has_alpha = false;
    int64_t m_png_start = -1;
    std::vector<std::shared_ptr<SubTextureInfo>> m_sub;

    Page() = default;
};
} // namespace fileSystem
} // namespace zombie
