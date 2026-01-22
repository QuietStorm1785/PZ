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


class FloorShaperDiamond : public FloorShaper {
public:
    static const FloorShaperDiamond instance = std::make_shared<FloorShaperDiamond>();

    void accept(TextureDraw var1) {
      super.accept(var1);
      DiamondShaper.instance.accept(var1);
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
