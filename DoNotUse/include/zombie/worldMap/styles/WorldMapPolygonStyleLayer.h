#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/WorldMapFeature.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/ColorStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FloatStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RGBAf.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RenderArgs.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/TextureStop.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapPolygonStyleLayer : public WorldMapStyleLayer {
public:
   public const std::vector<ColorStop> m_fill = std::make_unique<std::vector<>>();
   public const std::vector<TextureStop> m_texture = std::make_unique<std::vector<>>();
   public const std::vector<FloatStop> m_scale = std::make_unique<std::vector<>>();

    public WorldMapPolygonStyleLayer(const std::string& var1) {
      super(var1);
   }

    std::string getTypeString() {
      return "Polygon";
   }

    void render(WorldMapFeature var1, RenderArgs var2) {
    RGBAf var3 = this.evalColor(var2, this.m_fill);
      if (var3.a < 0.01F) {
         RGBAf.s_pool.release(var3);
      } else {
    float var4 = this.evalFloat(var2, this.m_scale);
    Texture var5 = this.evalTexture(var2, this.m_texture);
         if (var5 != nullptr && var5.isReady()) {
            var2.drawer.fillPolygon(var2, var1, var3, var5, var4);
         } else {
            var2.drawer.fillPolygon(var2, var1, var3);
         }

         RGBAf.s_pool.release(var3);
      }
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
