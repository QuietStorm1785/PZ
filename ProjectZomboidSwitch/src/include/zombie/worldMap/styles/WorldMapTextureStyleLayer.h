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
#include "zombie/worldMap/styles/WorldMapStyleLayer/FilterArgs.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RGBAf.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RenderArgs.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/TextureStop.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapTextureStyleLayer : public WorldMapStyleLayer {
public:
    int m_worldX1;
    int m_worldY1;
    int m_worldX2;
    int m_worldY2;
    bool m_useWorldBounds = false;
   public const std::vector<ColorStop> m_fill = std::make_unique<std::vector<>>();
   public const std::vector<TextureStop> m_texture = std::make_unique<std::vector<>>();
    bool m_tile = false;

    public WorldMapTextureStyleLayer(const std::string& var1) {
      super(var1);
   }

    std::string getTypeString() {
      return "Texture";
   }

    bool filter(WorldMapFeature var1, FilterArgs var2) {
    return false;
   }

    void render(WorldMapFeature var1, RenderArgs var2) {
   }

    void renderCell(RenderArgs var1) {
      if (this.m_useWorldBounds) {
         this.m_worldX1 = var1.renderer.getWorldMap().getMinXInSquares();
         this.m_worldY1 = var1.renderer.getWorldMap().getMinYInSquares();
         this.m_worldX2 = var1.renderer.getWorldMap().getMaxXInSquares() + 1;
         this.m_worldY2 = var1.renderer.getWorldMap().getMaxYInSquares() + 1;
      }

    RGBAf var2 = this.evalColor(var1, this.m_fill);
      if (var2.a < 0.01F) {
         RGBAf.s_pool.release(var2);
      } else {
    Texture var3 = this.evalTexture(var1, this.m_texture);
         if (var3 == nullptr) {
            RGBAf.s_pool.release(var2);
         } else {
            if (this.m_tile) {
               var1.drawer.drawTextureTiled(var3, var2, this.m_worldX1, this.m_worldY1, this.m_worldX2, this.m_worldY2, var1.cellX, var1.cellY);
            } else {
               var1.drawer.drawTexture(var3, var2, this.m_worldX1, this.m_worldY1, this.m_worldX2, this.m_worldY2);
            }

            RGBAf.s_pool.release(var2);
         }
      }
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
