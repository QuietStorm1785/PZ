#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/worldMap/WorldMapFeature.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/ColorStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FloatStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RGBAf.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RenderArgs.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapLineStyleLayer : public WorldMapStyleLayer {
public:
   public const std::vector<ColorStop> m_fill = std::make_unique<std::vector<>>();
   public const std::vector<FloatStop> m_lineWidth = std::make_unique<std::vector<>>();

    public WorldMapLineStyleLayer(const std::string& var1) {
      super(var1);
   }

    std::string getTypeString() {
      return "Line";
   }

    void render(WorldMapFeature var1, RenderArgs var2) {
    RGBAf var3 = this.evalColor(var2, this.m_fill);
      if (!(var3.a < 0.01F)) {
    float var4;
         if (var1.m_properties.containsKey("width")) {
            var4 = PZMath.tryParseFloat((std::string)var1.m_properties.get("width"), 1.0F) * var2.drawer.getWorldScale();
         } else {
            var4 = this.evalFloat(var2, this.m_lineWidth);
         }

         var2.drawer.drawLineString(var2, var1, var3, var4);
         RGBAf.s_pool.release(var3);
      }
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
