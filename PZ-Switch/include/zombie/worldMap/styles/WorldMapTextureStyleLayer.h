#pragma once
#include "zombie/core/textures/Texture.h"
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

class WorldMapTextureStyleLayer : public WorldMapStyleLayer {
public:
 int m_worldX1;
 int m_worldY1;
 int m_worldX2;
 int m_worldY2;
 bool m_useWorldBounds = false;
public
 ArrayList<WorldMapStyleLayer.ColorStop> m_fill =
 std::make_unique<ArrayList<>>();
public
 ArrayList<WorldMapStyleLayer.TextureStop> m_texture =
 std::make_unique<ArrayList<>>();
 bool m_tile = false;

public
 WorldMapTextureStyleLayer(std::string_view string) { super(string); }

 std::string getTypeString() { return "Texture"; }

 bool filter(WorldMapFeature var1, WorldMapStyleLayer.FilterArgs var2) {
 return false;
 }

 void render(WorldMapFeature var1, WorldMapStyleLayer.RenderArgs var2) {}

 void renderCell(WorldMapStyleLayer.RenderArgs renderArgs) {
 if (this->m_useWorldBounds) {
 this->m_worldX1 = renderArgs.renderer.getWorldMap().getMinXInSquares();
 this->m_worldY1 = renderArgs.renderer.getWorldMap().getMinYInSquares();
 this->m_worldX2 = renderArgs.renderer.getWorldMap().getMaxXInSquares() + 1;
 this->m_worldY2 = renderArgs.renderer.getWorldMap().getMaxYInSquares() + 1;
 }

 WorldMapStyleLayer.RGBAf rGBAf = this->evalColor(renderArgs, this->m_fill);
 if (rGBAf.a < 0.01F) {
 WorldMapStyleLayer.RGBAf.s_pool.release(rGBAf);
 } else {
 Texture texture = this->evalTexture(renderArgs, this->m_texture);
 if (texture.empty()) {
 WorldMapStyleLayer.RGBAf.s_pool.release(rGBAf);
 } else {
 if (this->m_tile) {
 renderArgs.drawer.drawTextureTiled(
 texture, rGBAf, this->m_worldX1, this->m_worldY1, this->m_worldX2,
 this->m_worldY2, renderArgs.cellX, renderArgs.cellY);
 } else {
 renderArgs.drawer.drawTexture(texture, rGBAf, this->m_worldX1,
 this->m_worldY1, this->m_worldX2,
 this->m_worldY2);
 }

 WorldMapStyleLayer.RGBAf.s_pool.release(rGBAf);
 }
 }
 }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
