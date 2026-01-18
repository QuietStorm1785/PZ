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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
