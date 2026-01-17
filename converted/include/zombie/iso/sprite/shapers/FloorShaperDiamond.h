#pragma once
#include "zombie/core/textures/TextureDraw.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FloorShaperDiamond : public FloorShaper {
public:
  static const FloorShaperDiamond instance = new FloorShaperDiamond();

  void accept(TextureDraw textureDraw) {
    super.accept(textureDraw);
    DiamondShaper.instance.accept(textureDraw);
  }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
