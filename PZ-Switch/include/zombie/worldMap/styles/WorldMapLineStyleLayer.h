#pragma once
#include "zombie/core/math/PZMath.h"
#include "zombie/worldMap/WorldMapFeature.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapLineStyleLayer : public WorldMapStyleLayer {
public:
public
 ArrayList<WorldMapStyleLayer.ColorStop> m_fill =
 std::make_unique<ArrayList<>>();
public
 ArrayList<WorldMapStyleLayer.FloatStop> m_lineWidth =
 std::make_unique<ArrayList<>>();

public
 WorldMapLineStyleLayer(std::string_view string) { super(string); }

 std::string getTypeString() { return "Line"; }

 void render(WorldMapFeature worldMapFeature,
 WorldMapStyleLayer.RenderArgs renderArgs) {
 WorldMapStyleLayer.RGBAf rGBAf = this->evalColor(renderArgs, this->m_fill);
 if (!(rGBAf.a < 0.01F) {
 float float0;
 if (worldMapFeature.m_properties.containsKey("width")) {
 float0 = PZMath.tryParseFloat(worldMapFeature.m_properties.get("width"),
 1.0F) *
 renderArgs.drawer.getWorldScale();
 } else {
 float0 = this->evalFloat(renderArgs, this->m_lineWidth);
 }

 renderArgs.drawer.drawLineString(renderArgs, worldMapFeature, rGBAf,
 float0);
 WorldMapStyleLayer.RGBAf.s_pool.release(rGBAf);
 }
 }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
