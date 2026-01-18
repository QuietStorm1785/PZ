#pragma once
#include "zombie/core/Color.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugOptions.h"
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

class WallShaper {
public:
public
 int[] col = new int[4];
 int colTint = 0;

 void setTintColor(int tintABGR) { this->colTint = tintABGR; }

 void accept(TextureDraw texd) {
 if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.Lighting
 .getValue()) {
 texd.col0 = Color.blendBGR(texd.col0, this->col[0]);
 texd.col1 = Color.blendBGR(texd.col1, this->col[1]);
 texd.col2 = Color.blendBGR(texd.col2, this->col[2]);
 texd.col3 = Color.blendBGR(texd.col3, this->col[3]);
 }

 if (this->colTint != 0) {
 texd.col0 = Color.tintABGR(texd.col0, this->colTint);
 texd.col1 = Color.tintABGR(texd.col1, this->colTint);
 texd.col2 = Color.tintABGR(texd.col2, this->colTint);
 texd.col3 = Color.tintABGR(texd.col3, this->colTint);
 }
 }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
