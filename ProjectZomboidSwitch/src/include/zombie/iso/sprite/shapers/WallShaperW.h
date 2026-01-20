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


class WallShaperW : public WallShaper {
public:
    static const WallShaperW instance = std::make_shared<WallShaperW>();

    void accept(TextureDraw var1) {
      super.accept(var1);
      var1.x1 = var1.x0 * 0.5F + var1.x1 * 0.5F;
      var1.x2 = var1.x2 * 0.5F + var1.x3 * 0.5F;
      var1.u1 = var1.u0 * 0.5F + var1.u1 * 0.5F;
      var1.u2 = var1.u2 * 0.5F + var1.u3 * 0.5F;
      WallPaddingShaper.instance.accept(var1);
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
