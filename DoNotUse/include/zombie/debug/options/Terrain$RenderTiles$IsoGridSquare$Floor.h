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
    const BooleanDebugOption Lighting;
    const BooleanDebugOption LightingOld;
    const BooleanDebugOption LightingDebug;

   public Terrain$RenderTiles$IsoGridSquare$Floor(IsoGridSquare var1, IDebugOptionGroup var2) {
      super(var2, "Floor");
      this.this$2 = var1;
      this.Lighting = newDebugOnlyOption(this.Group, "Lighting", true);
      this.LightingOld = newDebugOnlyOption(this.Group, "LightingOld", false);
      this.LightingDebug = newDebugOnlyOption(this.Group, "LightingDebug", false);
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
