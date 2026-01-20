#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TextureDraw.h"

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class WallShaperWhole : public WallShaper {
public:
    static const WallShaperWhole instance = std::make_shared<WallShaperWhole>();

    void accept(TextureDraw var1) {
      super.accept(var1);
      WallPaddingShaper.instance.accept(var1);
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
