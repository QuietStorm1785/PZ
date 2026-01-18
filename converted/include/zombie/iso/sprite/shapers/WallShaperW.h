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


class WallShaperW : public WallShaper {
public:
 static const WallShaperW instance = new WallShaperW();

 void accept(TextureDraw textureDraw) {
 super.accept(textureDraw);
 textureDraw.x1 = textureDraw.x0 * 0.5F + textureDraw.x1 * 0.5F;
 textureDraw.x2 = textureDraw.x2 * 0.5F + textureDraw.x3 * 0.5F;
 textureDraw.u1 = textureDraw.u0 * 0.5F + textureDraw.u1 * 0.5F;
 textureDraw.u2 = textureDraw.u2 * 0.5F + textureDraw.u3 * 0.5F;
 WallPaddingShaper.instance.accept(textureDraw);
 }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
