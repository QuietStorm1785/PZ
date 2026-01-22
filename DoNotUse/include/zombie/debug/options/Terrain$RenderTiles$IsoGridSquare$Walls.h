#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/options/Terrain/RenderTiles/IsoGridSquare.h"

namespace zombie {
namespace debug {
namespace options {


class Terrain {
public:
    const BooleanDebugOption NW;
    const BooleanDebugOption W;
    const BooleanDebugOption N;
    const BooleanDebugOption Render;
    const BooleanDebugOption Lighting;
    const BooleanDebugOption LightingDebug;
    const BooleanDebugOption LightingOldDebug;
    const BooleanDebugOption AttachedSprites;

   public Terrain$RenderTiles$IsoGridSquare$Walls(IsoGridSquare var1, IDebugOptionGroup var2) {
      super(var2, "Walls");
      this.this$2 = var1;
      this.NW = newDebugOnlyOption(this.Group, "NW", true);
      this.W = newDebugOnlyOption(this.Group, "W", true);
      this.N = newDebugOnlyOption(this.Group, "N", true);
      this.Render = newDebugOnlyOption(this.Group, "Render", true);
      this.Lighting = newDebugOnlyOption(this.Group, "Lighting", true);
      this.LightingDebug = newDebugOnlyOption(this.Group, "LightingDebug", false);
      this.LightingOldDebug = newDebugOnlyOption(this.Group, "LightingOldDebug", false);
      this.AttachedSprites = newDebugOnlyOption(this.Group, "AttachedSprites", true);
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
