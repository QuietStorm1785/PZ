#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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

namespace zombie {
namespace worldMap {


class UIWorldMapV1 {
:
    const UIWorldMap m_ui;
    const WorldMap m_worldMap;
    const WorldMapStyle m_style;
    const WorldMapRenderer m_renderer;
    const WorldMapMarkers m_markers;
    WorldMapSymbols m_symbols;
    WorldMapMarkersV1 m_markersV1 = nullptr;
    WorldMapStyleV1 m_styleV1 = nullptr;
    WorldMapSymbolsV1 m_symbolsV1 = nullptr;

     UIWorldMapV1(UIWorldMap var1) {
      this.m_ui = var1;
      this.m_worldMap = this.m_ui.m_worldMap;
      this.m_style = this.m_ui.m_style;
      this.m_renderer = this.m_ui.m_renderer;
      this.m_markers = this.m_ui.m_markers;
      this.m_symbols = this.m_ui.m_symbols;
   }

    void setMapItem(MapItem var1) {
      this.m_ui.setMapItem(var1);
      this.m_symbols = this.m_ui.m_symbols;
   }

    WorldMapRenderer getRenderer() const {
      return this.m_renderer;
   }

    WorldMapMarkers getMarkers() const {
      return this.m_markers;
   }

    WorldMapStyle getStyle() const {
      return this.m_style;
   }

    WorldMapMarkersV1 getMarkersAPI() const {
      if (this.m_markersV1 == nullptr) {
         this.m_markersV1 = new WorldMapMarkersV1(this.m_ui);
      }

      return this.m_markersV1;
   }

    WorldMapStyleV1 getStyleAPI() const {
      if (this.m_styleV1 == nullptr) {
         this.m_styleV1 = new WorldMapStyleV1(this.m_ui);
      }

      return this.m_styleV1;
   }

    WorldMapSymbolsV1 getSymbolsAPI() const {
      if (this.m_symbolsV1 == nullptr) {
         this.m_symbolsV1 = new WorldMapSymbolsV1(this.m_ui, this.m_symbols);
      }

      return this.m_symbolsV1;
   }

    void addData(std::string_view var1) {
    bool var2 = this.m_worldMap.hasData();
      this.m_worldMap.addData(var1);
      if (!var2) {
         this.m_renderer
            .setMap(
               this.m_worldMap,
               this.m_ui.getAbsoluteX().intValue(),
               this.m_ui.getAbsoluteY().intValue(),
               this.m_ui.getWidth().intValue(),
               this.m_ui.getHeight().intValue()
            );
         this.resetView();
      }
   }

    int getDataCount() const noexcept {
      return this.m_worldMap.getDataCount();
   }

    std::string getDataFileByIndex(int var1) {
    WorldMapData var2 = this.m_worldMap.getDataByIndex(var1);
      return var2.m_relativeFileName;
   }

    void clearData() {
      this.m_worldMap.clearData();
   }

    void endDirectoryData() {
      this.m_worldMap.endDirectoryData();
   }

    void addImages(std::string_view var1) {
    bool var2 = this.m_worldMap.hasImages();
      this.m_worldMap.addImages(var1);
      if (!var2) {
         this.m_renderer
            .setMap(
               this.m_worldMap,
               this.m_ui.getAbsoluteX().intValue(),
               this.m_ui.getAbsoluteY().intValue(),
               this.m_ui.getWidth().intValue(),
               this.m_ui.getHeight().intValue()
            );
         this.resetView();
      }
   }

    int getImagesCount() const noexcept {
      return this.m_worldMap.getImagesCount();
   }

    void setBoundsInCells(int var1, int var2, int var3, int var4) {
      boolean var5 = var1 * 300 != this.m_worldMap.m_minX
         || var2 * 300 != this.m_worldMap.m_minY
         || var3 * 300 + 299 != this.m_worldMap.m_maxX
         || var4 + 300 + 299 != this.m_worldMap.m_maxY;
      this.m_worldMap.setBoundsInCells(var1, var2, var3, var4);
      if (var5 && this.m_worldMap.hasData()) {
         this.resetView();
      }
   }

    void setBoundsInSquares(int var1, int var2, int var3, int var4) {
    bool var5 = var1 != this.m_worldMap.m_minX || var2 != this.m_worldMap.m_minY || var3 != this.m_worldMap.m_maxX || var4 != this.m_worldMap.m_maxY;
      this.m_worldMap.setBoundsInSquares(var1, var2, var3, var4);
      if (var5 && this.m_worldMap.hasData()) {
         this.resetView();
      }
   }

    void setBoundsFromWorld() {
      this.m_worldMap.setBoundsFromWorld();
   }

    void setBoundsFromData() {
      this.m_worldMap.setBoundsFromData();
   }

    int getMinXInCells() const {
      return this.m_worldMap.getMinXInCells();
   }

    int getMinYInCells() const {
      return this.m_worldMap.getMinYInCells();
   }

    int getMaxXInCells() const {
      return this.m_worldMap.getMaxXInCells();
   }

    int getMaxYInCells() const {
      return this.m_worldMap.getMaxYInCells();
   }

    int getWidthInCells() const {
      return this.m_worldMap.getWidthInCells();
   }

    int getHeightInCells() const {
      return this.m_worldMap.getHeightInCells();
   }

    int getMinXInSquares() const {
      return this.m_worldMap.getMinXInSquares();
   }

    int getMinYInSquares() const {
      return this.m_worldMap.getMinYInSquares();
   }

    int getMaxXInSquares() const {
      return this.m_worldMap.getMaxXInSquares();
   }

    int getMaxYInSquares() const {
      return this.m_worldMap.getMaxYInSquares();
   }

    int getWidthInSquares() const {
      return this.m_worldMap.getWidthInSquares();
   }

    int getHeightInSquares() const {
      return this.m_worldMap.getHeightInSquares();
   }

    float uiToWorldX(float var1, float var2, float var3, float var4, float var5) {
      return this.m_renderer.uiToWorldX(var1, var2, var3, var4, var5, this.m_renderer.getProjectionMatrix(), this.m_renderer.getModelViewMatrix());
   }

    float uiToWorldY(float var1, float var2, float var3, float var4, float var5) {
      return this.m_renderer.uiToWorldY(var1, var2, var3, var4, var5, this.m_renderer.getProjectionMatrix(), this.m_renderer.getModelViewMatrix());
   }

    float worldToUIX(float var1, float var2, float var3, float var4, float var5, Matrix4f var6, Matrix4f var7) {
      return this.m_renderer.worldToUIX(var1, var2, var3, var4, var5, var6, var7);
   }

    float worldToUIY(float var1, float var2, float var3, float var4, float var5, Matrix4f var6, Matrix4f var7) {
      return this.m_renderer.worldToUIY(var1, var2, var3, var4, var5, var6, var7);
   }

    float worldOriginUIX(float var1, float var2) {
      return this.m_renderer.worldOriginUIX(var1, var2);
   }

    float worldOriginUIY(float var1, float var2) {
      return this.m_renderer.worldOriginUIY(var1, var2);
   }

    float zoomMult() {
      return this.m_renderer.zoomMult();
   }

    float getWorldScale(float var1) {
      return this.m_renderer.getWorldScale(var1);
   }

    float worldOriginX() {
      return this.m_renderer.worldOriginUIX(this.m_renderer.getDisplayZoomF(), this.m_renderer.getCenterWorldX());
   }

    float worldOriginY() {
      return this.m_renderer.worldOriginUIY(this.m_renderer.getDisplayZoomF(), this.m_renderer.getCenterWorldY());
   }

    float getBaseZoom() const {
      return this.m_renderer.getBaseZoom();
   }

    float getZoomF() const {
      return this.m_renderer.getDisplayZoomF();
   }

    float getWorldScale() const {
      return this.m_renderer.getWorldScale(this.m_renderer.getDisplayZoomF());
   }

    float getCenterWorldX() const {
      return this.m_renderer.getCenterWorldX();
   }

    float getCenterWorldY() const {
      return this.m_renderer.getCenterWorldY();
   }

    float uiToWorldX(float var1, float var2) {
      return !this.m_worldMap.hasData() && !this.m_worldMap.hasImages()
         ? 0.0F
         : this.uiToWorldX(var1, var2, this.m_renderer.getDisplayZoomF(), this.m_renderer.getCenterWorldX(), this.m_renderer.getCenterWorldY());
   }

    float uiToWorldY(float var1, float var2) {
      return !this.m_worldMap.hasData() && !this.m_worldMap.hasImages()
         ? 0.0F
         : this.uiToWorldY(var1, var2, this.m_renderer.getDisplayZoomF(), this.m_renderer.getCenterWorldY(), this.m_renderer.getCenterWorldY());
   }

    float worldToUIX(float var1, float var2) {
      return !this.m_worldMap.hasData() && !this.m_worldMap.hasImages()
         ? 0.0F
         : this.worldToUIX(
            var1,
            var2,
            this.m_renderer.getDisplayZoomF(),
            this.m_renderer.getCenterWorldX(),
            this.m_renderer.getCenterWorldY(),
            this.m_renderer.getProjectionMatrix(),
            this.m_renderer.getModelViewMatrix()
         );
   }

    float worldToUIY(float var1, float var2) {
      return !this.m_worldMap.hasData() && !this.m_worldMap.hasImages()
         ? 0.0F
         : this.worldToUIY(
            var1,
            var2,
            this.m_renderer.getDisplayZoomF(),
            this.m_renderer.getCenterWorldX(),
            this.m_renderer.getCenterWorldY(),
            this.m_renderer.getProjectionMatrix(),
            this.m_renderer.getModelViewMatrix()
         );
   }

    void centerOn(float var1, float var2) {
      if (this.m_worldMap.hasData() || this.m_worldMap.hasImages()) {
         this.m_renderer.centerOn(var1, var2);
      }
   }

    void moveView(float var1, float var2) {
      if (this.m_worldMap.hasData() || this.m_worldMap.hasImages()) {
         this.m_renderer.moveView((int)var1, (int)var2);
      }
   }

    void zoomAt(float var1, float var2, float var3) {
      if (this.m_worldMap.hasData() || this.m_worldMap.hasImages()) {
         this.m_renderer.zoomAt((int)var1, (int)var2, -((int)var3));
      }
   }

    void setZoom(float var1) {
      this.m_renderer.setZoom(var1);
   }

    void resetView() {
      if (this.m_worldMap.hasData() || this.m_worldMap.hasImages()) {
         this.m_renderer.resetView();
      }
   }

    float mouseToWorldX() {
    float var1 = Mouse.getXA() - this.m_ui.getAbsoluteX().intValue();
    float var2 = Mouse.getYA() - this.m_ui.getAbsoluteY().intValue();
      return this.uiToWorldX(var1, var2);
   }

    float mouseToWorldY() {
    float var1 = Mouse.getXA() - this.m_ui.getAbsoluteX().intValue();
    float var2 = Mouse.getYA() - this.m_ui.getAbsoluteY().intValue();
      return this.uiToWorldY(var1, var2);
   }

    void setBackgroundRGBA(float var1, float var2, float var3, float var4) {
      this.m_ui.m_color.init(var1, var2, var3, var4);
   }

    void setDropShadowWidth(int var1) {
      this.m_ui.m_renderer.setDropShadowWidth(var1);
   }

    void setUnvisitedRGBA(float var1, float var2, float var3, float var4) {
      WorldMapVisited.getInstance().setUnvisitedRGBA(var1, var2, var3, var4);
   }

    void setUnvisitedGridRGBA(float var1, float var2, float var3, float var4) {
      WorldMapVisited.getInstance().setUnvisitedGridRGBA(var1, var2, var3, var4);
   }

    int getOptionCount() const noexcept {
      return this.m_renderer.getOptionCount();
   }

    ConfigOption getOptionByIndex(int var1) {
      return this.m_renderer.getOptionByIndex(var1);
   }

    void setBoolean(std::string_view var1, bool var2) {
      this.m_renderer.setBoolean(var1, var2);
   }

    bool getBoolean(std::string_view var1) {
      return this.m_renderer.getBoolean(var1);
   }

    void setDouble(std::string_view var1, double var2) {
      this.m_renderer.setDouble(var1, var2);
   }

    double getDouble(std::string_view var1, double var2) {
      return this.m_renderer.getDouble(var1, var2);
   }
}
} // namespace worldMap
} // namespace zombie
