#pragma once
#include "zombie/core/textures/TextureDraw.h"
#include <algorithm>
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

class WallPaddingShaper {
public:
 static const WallPaddingShaper instance = new WallPaddingShaper();

 void accept(TextureDraw textureDraw) {
 SpritePadding.applyIsoPadding(
 textureDraw, SpritePaddingSettings.getSettings().IsoPadding);
 }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
