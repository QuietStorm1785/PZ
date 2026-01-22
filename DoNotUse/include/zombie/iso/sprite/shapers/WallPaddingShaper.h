#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TextureDraw.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class WallPaddingShaper {
public:
    static const WallPaddingShaper instance = std::make_shared<WallPaddingShaper>();

    void accept(TextureDraw var1) {
      SpritePadding.applyIsoPadding(var1, SpritePaddingSettings.getSettings().IsoPadding);
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
