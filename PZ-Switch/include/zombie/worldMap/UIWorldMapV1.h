#pragma once
#include "org/joml/Matrix4f.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/worldMap/markers/WorldMapMarkers.h"
#include "zombie/worldMap/markers/WorldMapMarkersV1.h"
#include "zombie/worldMap/styles/WorldMapStyle.h"
#include "zombie/worldMap/styles/WorldMapStyleV1.h"
#include "zombie/worldMap/symbols/WorldMapSymbols.h"
#include "zombie/worldMap/symbols/WorldMapSymbolsV1.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UIWorldMapV1 {
public:
 const UIWorldMap m_ui;
 const WorldMap m_worldMap;
 const WorldMapStyle m_style;
 const WorldMapRenderer m_renderer;
 const WorldMapMarkers m_markers;
 WorldMapSymbols m_symbols;
 WorldMapMarkersV1 m_markersV1 = nullptr;
 WorldMapStyleV1 m_styleV1 = nullptr;
 WorldMapSymbolsV1 m_symbolsV1 = nullptr;

public
 UIWorldMapV1(UIWorldMap ui) {
 this->m_ui = ui;
 this->m_worldMap = this->m_ui.m_worldMap;
 this->m_style = this->m_ui.m_style;
 this->m_renderer = this->m_ui.m_renderer;
 this->m_markers = this->m_ui.m_markers;
 this->m_symbols = this->m_ui.m_symbols;
 }

 void setMapItem(MapItem mapItem) {
 this->m_ui.setMapItem(mapItem);
 this->m_symbols = this->m_ui.m_symbols;
 }

 WorldMapRenderer getRenderer() { return this->m_renderer; }

 WorldMapMarkers getMarkers() { return this->m_markers; }

 WorldMapStyle getStyle() { return this->m_style; }

 WorldMapMarkersV1 getMarkersAPI() {
 if (this->m_markersV1.empty()) {
 this->m_markersV1 = new WorldMapMarkersV1(this->m_ui);
 }

 return this->m_markersV1;
 }

 WorldMapStyleV1 getStyleAPI() {
 if (this->m_styleV1.empty()) {
 this->m_styleV1 = new WorldMapStyleV1(this->m_ui);
 }

 return this->m_styleV1;
 }

 WorldMapSymbolsV1 getSymbolsAPI() {
 if (this->m_symbolsV1.empty()) {
 this->m_symbolsV1 = new WorldMapSymbolsV1(this->m_ui, this->m_symbols);
 }

 return this->m_symbolsV1;
 }

 void addData(std::string_view fileName) {
 bool boolean0 = this->m_worldMap.hasData();
 this->m_worldMap.addData(fileName);
 if (!boolean0) {
 this->m_renderer.setMap(
 this->m_worldMap, this->m_ui.getAbsoluteX().intValue(),
 this->m_ui.getAbsoluteY().intValue(), this->m_ui.getWidth().intValue(),
 this->m_ui.getHeight().intValue());
 this->resetView();
 }
 }

 int getDataCount() noexcept{ return this->m_worldMap.getDataCount(); }

 std::string getDataFileByIndex(int index) {
 WorldMapData worldMapData = this->m_worldMap.getDataByIndex(index);
 return worldMapData.m_relativeFileName;
 }

 void clearData() { this->m_worldMap.clearData(); }

 void endDirectoryData() { this->m_worldMap.endDirectoryData(); }

 void addImages(std::string_view directory) {
 bool boolean0 = this->m_worldMap.hasImages();
 this->m_worldMap.addImages(directory);
 if (!boolean0) {
 this->m_renderer.setMap(
 this->m_worldMap, this->m_ui.getAbsoluteX().intValue(),
 this->m_ui.getAbsoluteY().intValue(), this->m_ui.getWidth().intValue(),
 this->m_ui.getHeight().intValue());
 this->resetView();
 }
 }

 int getImagesCount() noexcept{ return this->m_worldMap.getImagesCount(); }

 void setBoundsInCells(int minX, int minY, int maxX, int maxY) {
 boolean boolean0 = minX * 300 != this->m_worldMap.m_minX ||
 minY * 300 != this->m_worldMap.m_minY ||
 maxX * 300 + 299 != this->m_worldMap.m_maxX ||
 maxY + 300 + 299 != this->m_worldMap.m_maxY;
 this->m_worldMap.setBoundsInCells(minX, minY, maxX, maxY);
 if (boolean0 && this->m_worldMap.hasData()) {
 this->resetView();
 }
 }

 void setBoundsInSquares(int minX, int minY, int maxX, int maxY) {
 bool boolean0 =
 minX != this->m_worldMap.m_minX || minY != this->m_worldMap.m_minY ||
 maxX != this->m_worldMap.m_maxX || maxY != this->m_worldMap.m_maxY;
 this->m_worldMap.setBoundsInSquares(minX, minY, maxX, maxY);
 if (boolean0 && this->m_worldMap.hasData()) {
 this->resetView();
 }
 }

 void setBoundsFromWorld() { this->m_worldMap.setBoundsFromWorld(); }

 void setBoundsFromData() { this->m_worldMap.setBoundsFromData(); }

 int getMinXInCells() { return this->m_worldMap.getMinXInCells(); }

 int getMinYInCells() { return this->m_worldMap.getMinYInCells(); }

 int getMaxXInCells() { return this->m_worldMap.getMaxXInCells(); }

 int getMaxYInCells() { return this->m_worldMap.getMaxYInCells(); }

 int getWidthInCells() { return this->m_worldMap.getWidthInCells(); }

 int getHeightInCells() { return this->m_worldMap.getHeightInCells(); }

 int getMinXInSquares() { return this->m_worldMap.getMinXInSquares(); }

 int getMinYInSquares() { return this->m_worldMap.getMinYInSquares(); }

 int getMaxXInSquares() { return this->m_worldMap.getMaxXInSquares(); }

 int getMaxYInSquares() { return this->m_worldMap.getMaxYInSquares(); }

 int getWidthInSquares() { return this->m_worldMap.getWidthInSquares(); }

 int getHeightInSquares() { return this->m_worldMap.getHeightInSquares(); }

 float uiToWorldX(float uiX, float uiY, float zoomF, float centerWorldX,
 float centerWorldY) {
 return this->m_renderer.uiToWorldX(uiX, uiY, zoomF, centerWorldX,
 centerWorldY,
 this->m_renderer.getProjectionMatrix(),
 this->m_renderer.getModelViewMatrix());
 }

 float uiToWorldY(float uiX, float uiY, float zoomF, float centerWorldX,
 float centerWorldY) {
 return this->m_renderer.uiToWorldY(uiX, uiY, zoomF, centerWorldX,
 centerWorldY,
 this->m_renderer.getProjectionMatrix(),
 this->m_renderer.getModelViewMatrix());
 }

 float worldToUIX(float float0, float float1, float float2, float float3,
 float float4, Matrix4f matrix4f0, Matrix4f matrix4f1) {
 return this->m_renderer.worldToUIX(float0, float1, float2, float3, float4,
 matrix4f0, matrix4f1);
 }

 float worldToUIY(float float0, float float1, float float2, float float3,
 float float4, Matrix4f matrix4f0, Matrix4f matrix4f1) {
 return this->m_renderer.worldToUIY(float0, float1, float2, float3, float4,
 matrix4f0, matrix4f1);
 }

 float worldOriginUIX(float float0, float float1) {
 return this->m_renderer.worldOriginUIX(float0, float1);
 }

 float worldOriginUIY(float float0, float float1) {
 return this->m_renderer.worldOriginUIY(float0, float1);
 }

 float zoomMult() { return this->m_renderer.zoomMult(); }

 float getWorldScale(float float0) {
 return this->m_renderer.getWorldScale(float0);
 }

 float worldOriginX() {
 return this->m_renderer.worldOriginUIX(this->m_renderer.getDisplayZoomF(),
 this->m_renderer.getCenterWorldX());
 }

 float worldOriginY() {
 return this->m_renderer.worldOriginUIY(this->m_renderer.getDisplayZoomF(),
 this->m_renderer.getCenterWorldY());
 }

 float getBaseZoom() { return this->m_renderer.getBaseZoom(); }

 float getZoomF() { return this->m_renderer.getDisplayZoomF(); }

 float getWorldScale() {
 return this->m_renderer.getWorldScale(this->m_renderer.getDisplayZoomF());
 }

 float getCenterWorldX() { return this->m_renderer.getCenterWorldX(); }

 float getCenterWorldY() { return this->m_renderer.getCenterWorldY(); }

 float uiToWorldX(float uiX, float uiY) {
 return !this->m_worldMap.hasData() && !this->m_worldMap.hasImages()
 ? 0.0F
 : this->uiToWorldX(uiX, uiY, this->m_renderer.getDisplayZoomF(),
 this->m_renderer.getCenterWorldX(),
 this->m_renderer.getCenterWorldY());
 }

 float uiToWorldY(float uiX, float uiY) {
 return !this->m_worldMap.hasData() && !this->m_worldMap.hasImages()
 ? 0.0F
 : this->uiToWorldY(uiX, uiY, this->m_renderer.getDisplayZoomF(),
 this->m_renderer.getCenterWorldY(),
 this->m_renderer.getCenterWorldY());
 }

 float worldToUIX(float worldX, float worldY) {
 return !this->m_worldMap.hasData() && !this->m_worldMap.hasImages()
 ? 0.0F
 : this->worldToUIX(worldX, worldY,
 this->m_renderer.getDisplayZoomF(),
 this->m_renderer.getCenterWorldX(),
 this->m_renderer.getCenterWorldY(),
 this->m_renderer.getProjectionMatrix(),
 this->m_renderer.getModelViewMatrix());
 }

 float worldToUIY(float worldX, float worldY) {
 return !this->m_worldMap.hasData() && !this->m_worldMap.hasImages()
 ? 0.0F
 : this->worldToUIY(worldX, worldY,
 this->m_renderer.getDisplayZoomF(),
 this->m_renderer.getCenterWorldX(),
 this->m_renderer.getCenterWorldY(),
 this->m_renderer.getProjectionMatrix(),
 this->m_renderer.getModelViewMatrix());
 }

 void centerOn(float worldX, float worldY) {
 if (this->m_worldMap.hasData() || this->m_worldMap.hasImages()) {
 this->m_renderer.centerOn(worldX, worldY);
 }
 }

 void moveView(float dx, float dy) {
 if (this->m_worldMap.hasData() || this->m_worldMap.hasImages()) {
 this->m_renderer.moveView((int)dx, (int)dy);
 }
 }

 void zoomAt(float uiX, float uiY, float delta) {
 if (this->m_worldMap.hasData() || this->m_worldMap.hasImages()) {
 this->m_renderer.zoomAt((int)uiX, (int)uiY, -((int)delta);
 }
 }

 void setZoom(float zoom) { this->m_renderer.setZoom(zoom); }

 void resetView() {
 if (this->m_worldMap.hasData() || this->m_worldMap.hasImages()) {
 this->m_renderer.resetView();
 }
 }

 float mouseToWorldX() {
 float float0 = Mouse.getXA() - this->m_ui.getAbsoluteX().intValue();
 float float1 = Mouse.getYA() - this->m_ui.getAbsoluteY().intValue();
 return this->uiToWorldX(float0, float1);
 }

 float mouseToWorldY() {
 float float0 = Mouse.getXA() - this->m_ui.getAbsoluteX().intValue();
 float float1 = Mouse.getYA() - this->m_ui.getAbsoluteY().intValue();
 return this->uiToWorldY(float0, float1);
 }

 void setBackgroundRGBA(float r, float g, float b, float a) {
 this->m_ui.m_color.init(r, g, b, a);
 }

 void setDropShadowWidth(int width) {
 this->m_ui.m_renderer.setDropShadowWidth(width);
 }

 void setUnvisitedRGBA(float r, float g, float b, float a) {
 WorldMapVisited.getInstance().setUnvisitedRGBA(r, g, b, a);
 }

 void setUnvisitedGridRGBA(float r, float g, float b, float a) {
 WorldMapVisited.getInstance().setUnvisitedGridRGBA(r, g, b, a);
 }

 int getOptionCount() noexcept{ return this->m_renderer.getOptionCount(); }

 ConfigOption getOptionByIndex(int index) {
 return this->m_renderer.getOptionByIndex(index);
 }

 void setBoolean(std::string_view name, bool value) {
 this->m_renderer.setBoolean(name, value);
 }

 bool getBoolean(std::string_view name) {
 return this->m_renderer.getBoolean(name);
 }

 void setDouble(std::string_view name, double value) {
 this->m_renderer.setDouble(name, value);
 }

 double getDouble(std::string_view name, double defaultValue) {
 return this->m_renderer.getDouble(name, defaultValue);
 }
}
} // namespace worldMap
} // namespace zombie
