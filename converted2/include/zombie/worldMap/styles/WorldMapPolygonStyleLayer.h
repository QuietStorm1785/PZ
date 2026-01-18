#pragma once
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/WorldMapFeature.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapPolygonStyleLayer : public WorldMapStyleLayer {
public:
public
  final ArrayList<WorldMapStyleLayer.ColorStop> m_fill =
      std::make_unique<ArrayList<>>();
public
  final ArrayList<WorldMapStyleLayer.TextureStop> m_texture =
      std::make_unique<ArrayList<>>();
public
  final ArrayList<WorldMapStyleLayer.FloatStop> m_scale =
      std::make_unique<ArrayList<>>();

public
  WorldMapPolygonStyleLayer(const std::string &string) { super(string); }

  std::string getTypeString() { return "Polygon"; }

  void render(WorldMapFeature worldMapFeature,
              WorldMapStyleLayer.RenderArgs renderArgs) {
    WorldMapStyleLayer.RGBAf rGBAf = this.evalColor(renderArgs, this.m_fill);
    if (rGBAf.a < 0.01F) {
      WorldMapStyleLayer.RGBAf.s_pool.release(rGBAf);
    } else {
      float float0 = this.evalFloat(renderArgs, this.m_scale);
      Texture texture = this.evalTexture(renderArgs, this.m_texture);
      if (texture != nullptr && texture.isReady()) {
        renderArgs.drawer.fillPolygon(renderArgs, worldMapFeature, rGBAf,
                                      texture, float0);
      } else {
        renderArgs.drawer.fillPolygon(renderArgs, worldMapFeature, rGBAf);
      }

      WorldMapStyleLayer.RGBAf.s_pool.release(rGBAf);
    }
  }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
