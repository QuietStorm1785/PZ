#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/UIWorldMap.h"
#include "zombie/worldMap/UIWorldMapV1.h"
#include <algorithm>
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

class WorldMapStyleV1 {
public:
 UIWorldMap m_ui;
 UIWorldMapV1 m_api;
 WorldMapStyle m_style;
public
 ArrayList<WorldMapStyleV1.WorldMapStyleLayerV1> m_layers =
 std::make_unique<ArrayList<>>();

public
 WorldMapStyleV1(UIWorldMap ui) {
 Objects.requireNonNull(ui);
 this->m_ui = ui;
 this->m_api = ui.getAPIv1();
 this->m_style = this->m_api.getStyle();
 }

public
 WorldMapStyleV1.WorldMapStyleLayerV1
 newLineLayer(String id) throws IllegalArgumentException {
 WorldMapStyleV1.WorldMapLineStyleLayerV1 worldMapLineStyleLayerV1 =
 new WorldMapStyleV1.WorldMapLineStyleLayerV1(this, id);
 this->m_layers.add(worldMapLineStyleLayerV1);
 return worldMapLineStyleLayerV1;
 }

public
 WorldMapStyleV1.WorldMapStyleLayerV1
 newPolygonLayer(String id) throws IllegalArgumentException {
 WorldMapStyleV1.WorldMapPolygonStyleLayerV1 worldMapPolygonStyleLayerV1 =
 new WorldMapStyleV1.WorldMapPolygonStyleLayerV1(this, id);
 this->m_layers.add(worldMapPolygonStyleLayerV1);
 return worldMapPolygonStyleLayerV1;
 }

public
 WorldMapStyleV1.WorldMapStyleLayerV1
 newTextureLayer(String id) throws IllegalArgumentException {
 WorldMapStyleV1.WorldMapTextureStyleLayerV1 worldMapTextureStyleLayerV1 =
 new WorldMapStyleV1.WorldMapTextureStyleLayerV1(this, id);
 this->m_layers.add(worldMapTextureStyleLayerV1);
 return worldMapTextureStyleLayerV1;
 }

 int getLayerCount() { return this->m_layers.size(); }

public
 WorldMapStyleV1.WorldMapStyleLayerV1 getLayerByIndex(int index) {
 return this->m_layers.get(index);
 }

public
 WorldMapStyleV1.WorldMapStyleLayerV1 getLayerByName(String id) {
 int int0 = this->indexOfLayer(id);
 return int0 = = -1 ? nullptr : this->m_layers.get(int0);
 }

 int indexOfLayer(const std::string &id) {
 for (int int0 = 0; int0 < this->m_layers.size(); int0++) {
 WorldMapStyleV1.WorldMapStyleLayerV1 worldMapStyleLayerV1 =
 this->m_layers.get(int0);
 if (worldMapStyleLayerV1.m_layer.m_id == id) {
 return int0;
 }
 }

 return -1;
 }

 void moveLayer(int indexFrom, int indexTo) {
 WorldMapStyleLayer worldMapStyleLayer =
 this->m_style.m_layers.remove(indexFrom);
 this->m_style.m_layers.add(indexTo, worldMapStyleLayer);
 WorldMapStyleV1.WorldMapStyleLayerV1 worldMapStyleLayerV1 =
 this->m_layers.remove(indexFrom);
 this->m_layers.add(indexTo, worldMapStyleLayerV1);
 }

 void removeLayerById(const std::string &id) {
 int int0 = this->indexOfLayer(id);
 if (int0 != -1) {
 this->removeLayerByIndex(int0);
 }
 }

 void removeLayerByIndex(int index) {
 this->m_style.m_layers.remove(index);
 this->m_layers.remove(index);
 }

 void clear() {
 this->m_style.m_layers.clear();
 this->m_layers.clear();
 }

 static void setExposed(LuaManager.Exposer exposer) {
 exposer.setExposed(WorldMapStyleV1.class);
 exposer.setExposed(WorldMapStyleV1.WorldMapStyleLayerV1.class);
 exposer.setExposed(WorldMapStyleV1.WorldMapLineStyleLayerV1.class);
 exposer.setExposed(WorldMapStyleV1.WorldMapPolygonStyleLayerV1.class);
 exposer.setExposed(WorldMapStyleV1.WorldMapTextureStyleLayerV1.class);
 }

public
 static class WorldMapLineStyleLayerV1 extends
 WorldMapStyleV1.WorldMapStyleLayerV1 {
 WorldMapLineStyleLayer m_lineStyle = (WorldMapLineStyleLayer)this->m_layer;

 WorldMapLineStyleLayerV1(WorldMapStyleV1 worldMapStyleV1, String string) {
 super(worldMapStyleV1, new WorldMapLineStyleLayer(string);
 }

 void setFilter(const std::string &string0, const std::string &string1) {
 this->m_lineStyle.m_filterKey = string0;
 this->m_lineStyle.m_filterValue = string1;
 this->m_lineStyle.m_filter = (worldMapFeature, var3) -> worldMapFeature.hasLineString() && string1 == worldMapFeature.m_properties.get(string0);
 }

 void addFill(float float0, int int0, int int1, int int2, int int3) {
 this->m_lineStyle.m_fill.add(
 new WorldMapStyleLayer.ColorStop(float0, int0, int1, int2, int3);
 }

 void addLineWidth(float float0, float float1) {
 this->m_lineStyle.m_lineWidth.add(
 new WorldMapStyleLayer.FloatStop(float0, float1);
 }
 }

public
 static class WorldMapPolygonStyleLayerV1 extends
 WorldMapStyleV1.WorldMapStyleLayerV1 {
 WorldMapPolygonStyleLayer m_polygonStyle =
 (WorldMapPolygonStyleLayer)this->m_layer;

 WorldMapPolygonStyleLayerV1(WorldMapStyleV1 worldMapStyleV1,
 String string) {
 super(worldMapStyleV1, new WorldMapPolygonStyleLayer(string);
 }

 void setFilter(const std::string &string0, const std::string &string1) {
 this->m_polygonStyle.m_filterKey = string0;
 this->m_polygonStyle.m_filterValue = string1;
 this->m_polygonStyle.m_filter = (worldMapFeature, var3) -> worldMapFeature.hasPolygon() && string1 == worldMapFeature.m_properties.get(string0);
 }

 std::string getFilterKey() { return this->m_polygonStyle.m_filterKey; }

 std::string getFilterValue() { return this->m_polygonStyle.m_filterValue; }

 void addFill(float float0, int int0, int int1, int int2, int int3) {
 this->m_polygonStyle.m_fill.add(
 new WorldMapStyleLayer.ColorStop(float0, int0, int1, int2, int3);
 }

 void addScale(float float0, float float1) {
 this->m_polygonStyle.m_scale.add(
 new WorldMapStyleLayer.FloatStop(float0, float1);
 }

 void addTexture(float float0, const std::string &string) {
 this->m_polygonStyle.m_texture.add(
 new WorldMapStyleLayer.TextureStop(float0, string);
 }

 void removeFill(int int0) { this->m_polygonStyle.m_fill.remove(int0); }

 void removeTexture(int int0) { this->m_polygonStyle.m_texture.remove(int0); }

 void moveFill(int int0, int int1) {
 WorldMapStyleLayer.ColorStop colorStop =
 this->m_polygonStyle.m_fill.remove(int0);
 this->m_polygonStyle.m_fill.add(int1, colorStop);
 }

 void moveTexture(int int0, int int1) {
 WorldMapStyleLayer.TextureStop textureStop =
 this->m_polygonStyle.m_texture.remove(int0);
 this->m_polygonStyle.m_texture.add(int1, textureStop);
 }

 int getFillStops() { return this->m_polygonStyle.m_fill.size(); }

 void setFillRGBA(int int1, int int0, int int2, int int3, int int4) {
 this->m_polygonStyle.m_fill.get(int1).r = int0;
 this->m_polygonStyle.m_fill.get(int1).g = int2;
 this->m_polygonStyle.m_fill.get(int1).b = int3;
 this->m_polygonStyle.m_fill.get(int1).a = int4;
 }

 void setFillZoom(int int0, float float0) {
 this->m_polygonStyle.m_fill.get(int0).m_zoom =
 PZMath.clamp(float0, 0.0F, 24.0F);
 }

 float getFillZoom(int int0) {
 return this->m_polygonStyle.m_fill.get(int0).m_zoom;
 }

 int getFillRed(int int0) { return this->m_polygonStyle.m_fill.get(int0).r; }

 int getFillGreen(int int0) {
 return this->m_polygonStyle.m_fill.get(int0).g;
 }

 int getFillBlue(int int0) { return this->m_polygonStyle.m_fill.get(int0).b; }

 int getFillAlpha(int int0) {
 return this->m_polygonStyle.m_fill.get(int0).a;
 }

 int getTextureStops() { return this->m_polygonStyle.m_texture.size(); }

 void setTextureZoom(int int0, float float0) {
 this->m_polygonStyle.m_texture.get(int0).m_zoom =
 PZMath.clamp(float0, 0.0F, 24.0F);
 }

 float getTextureZoom(int int0) {
 return this->m_polygonStyle.m_texture.get(int0).m_zoom;
 }

 void setTexturePath(int int0, const std::string &string) {
 this->m_polygonStyle.m_texture.get(int0).texturePath = string;
 this->m_polygonStyle.m_texture.get(int0).texture =
 Texture.getTexture(string);
 }

 std::string getTexturePath(int int0) {
 return this->m_polygonStyle.m_texture.get(int0).texturePath;
 }

 Texture getTexture(int int0) {
 return this->m_polygonStyle.m_texture.get(int0).texture;
 }
 }

public
 static class WorldMapStyleLayerV1 {
 WorldMapStyleV1 m_owner;
 WorldMapStyleLayer m_layer;

 WorldMapStyleLayerV1(WorldMapStyleV1 worldMapStyleV1,
 WorldMapStyleLayer worldMapStyleLayer) {
 this->m_owner = worldMapStyleV1;
 this->m_layer = worldMapStyleLayer;
 worldMapStyleV1.m_style.m_layers.add(this->m_layer);
 }

 std::string getTypeString() { return this->m_layer.getTypeString(); }

 void setId(const std::string &id) { this->m_layer.m_id = id; }

 std::string getId() { return this->m_layer.m_id; }

 void setMinZoom(float minZoom) { this->m_layer.m_minZoom = minZoom; }

 float getMinZoom() { return this->m_layer.m_minZoom; }
 }

 public static class WorldMapTextureStyleLayerV1 extends
 WorldMapStyleV1.WorldMapStyleLayerV1 {
 WorldMapTextureStyleLayer m_textureStyle =
 (WorldMapTextureStyleLayer)this->m_layer;

 WorldMapTextureStyleLayerV1(WorldMapStyleV1 worldMapStyleV1,
 String string) {
 super(worldMapStyleV1, new WorldMapTextureStyleLayer(string);
 }

 void addFill(float float0, int int0, int int1, int int2, int int3) {
 this->m_textureStyle.m_fill.add(
 new WorldMapStyleLayer.ColorStop(float0, int0, int1, int2, int3);
 }

 void addTexture(float float0, const std::string &string) {
 this->m_textureStyle.m_texture.add(
 new WorldMapStyleLayer.TextureStop(float0, string);
 }

 void removeFill(int int0) { this->m_textureStyle.m_fill.remove(int0); }

 void removeAllFill() { this->m_textureStyle.m_fill.clear(); }

 void removeTexture(int int0) { this->m_textureStyle.m_texture.remove(int0); }

 void removeAllTexture() { this->m_textureStyle.m_texture.clear(); }

 void moveFill(int int0, int int1) {
 WorldMapStyleLayer.ColorStop colorStop =
 this->m_textureStyle.m_fill.remove(int0);
 this->m_textureStyle.m_fill.add(int1, colorStop);
 }

 void moveTexture(int int0, int int1) {
 WorldMapStyleLayer.TextureStop textureStop =
 this->m_textureStyle.m_texture.remove(int0);
 this->m_textureStyle.m_texture.add(int1, textureStop);
 }

 void setBoundsInSquares(int int0, int int1, int int2, int int3) {
 this->m_textureStyle.m_worldX1 = int0;
 this->m_textureStyle.m_worldY1 = int1;
 this->m_textureStyle.m_worldX2 = int2;
 this->m_textureStyle.m_worldY2 = int3;
 }

 int getMinXInSquares() { return this->m_textureStyle.m_worldX1; }

 int getMinYInSquares() { return this->m_textureStyle.m_worldY1; }

 int getMaxXInSquares() { return this->m_textureStyle.m_worldX2; }

 int getMaxYInSquares() { return this->m_textureStyle.m_worldY2; }

 int getWidthInSquares() {
 return this->m_textureStyle.m_worldX2 - this->m_textureStyle.m_worldX1;
 }

 int getHeightInSquares() {
 return this->m_textureStyle.m_worldY2 - this->m_textureStyle.m_worldY1;
 }

 void setTile(bool boolean0) { this->m_textureStyle.m_tile = boolean0; }

 bool isTile() { return this->m_textureStyle.m_tile; }

 void setUseWorldBounds(bool boolean0) {
 this->m_textureStyle.m_useWorldBounds = boolean0;
 }

 bool isUseWorldBounds() { return this->m_textureStyle.m_useWorldBounds; }

 int getFillStops() { return this->m_textureStyle.m_fill.size(); }

 void setFillRGBA(int int1, int int0, int int2, int int3, int int4) {
 this->m_textureStyle.m_fill.get(int1).r = int0;
 this->m_textureStyle.m_fill.get(int1).g = int2;
 this->m_textureStyle.m_fill.get(int1).b = int3;
 this->m_textureStyle.m_fill.get(int1).a = int4;
 }

 void setFillZoom(int int0, float float0) {
 this->m_textureStyle.m_fill.get(int0).m_zoom =
 PZMath.clamp(float0, 0.0F, 24.0F);
 }

 float getFillZoom(int int0) {
 return this->m_textureStyle.m_fill.get(int0).m_zoom;
 }

 int getFillRed(int int0) { return this->m_textureStyle.m_fill.get(int0).r; }

 int getFillGreen(int int0) {
 return this->m_textureStyle.m_fill.get(int0).g;
 }

 int getFillBlue(int int0) { return this->m_textureStyle.m_fill.get(int0).b; }

 int getFillAlpha(int int0) {
 return this->m_textureStyle.m_fill.get(int0).a;
 }

 int getTextureStops() { return this->m_textureStyle.m_texture.size(); }

 void setTextureZoom(int int0, float float0) {
 this->m_textureStyle.m_texture.get(int0).m_zoom =
 PZMath.clamp(float0, 0.0F, 24.0F);
 }

 float getTextureZoom(int int0) {
 return this->m_textureStyle.m_texture.get(int0).m_zoom;
 }

 void setTexturePath(int int0, const std::string &string) {
 this->m_textureStyle.m_texture.get(int0).texturePath = string;
 this->m_textureStyle.m_texture.get(int0).texture =
 Texture.getTexture(string);
 }

 std::string getTexturePath(int int0) {
 return this->m_textureStyle.m_texture.get(int0).texturePath;
 }

 Texture getTexture(int int0) {
 return this->m_textureStyle.m_texture.get(int0).texture;
 }
 }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
