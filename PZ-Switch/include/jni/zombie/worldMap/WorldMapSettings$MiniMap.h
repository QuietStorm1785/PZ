#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"

namespace zombie {
namespace worldMap {


class WorldMapSettings {
:
    DoubleConfigOption Zoom;
    BooleanConfigOption Isometric;
    BooleanConfigOption ShowSymbols;
    BooleanConfigOption StartVisible;

    WorldMapSettings$MiniMap(WorldMapSettings var1) {
      this.this$0 = var1;
      this.Zoom = this.this$0.newOption("MiniMap.Zoom", 0.0, 24.0, 19.0);
      this.Isometric = this.this$0.newOption("MiniMap.Isometric", true);
      this.ShowSymbols = this.this$0.newOption("MiniMap.ShowSymbols", false);
      this.StartVisible = this.this$0.newOption("MiniMap.StartVisible", true);
   }
}
} // namespace worldMap
} // namespace zombie
