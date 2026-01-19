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
public:
    DoubleConfigOption CenterX;
    DoubleConfigOption CenterY;
    DoubleConfigOption Zoom;
    BooleanConfigOption Isometric;
    BooleanConfigOption ShowSymbolsUI;

   public WorldMapSettings$WorldMap(WorldMapSettings var1) {
      this.this$0 = var1;
      this.CenterX = this.this$0.newOption("WorldMap.CenterX", -Double.MAX_VALUE, Double.MAX_VALUE, 0.0);
      this.CenterY = this.this$0.newOption("WorldMap.CenterY", -Double.MAX_VALUE, Double.MAX_VALUE, 0.0);
      this.Zoom = this.this$0.newOption("WorldMap.Zoom", 0.0, 24.0, 0.0);
      this.Isometric = this.this$0.newOption("WorldMap.Isometric", true);
      this.ShowSymbolsUI = this.this$0.newOption("WorldMap.ShowSymbolsUI", true);
   }
}
} // namespace worldMap
} // namespace zombie
