#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/ColorStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FloatStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/TextureStop.h"
#include "zombie/worldMap/styles/WorldMapStyleV1/WorldMapStyleLayerV1.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleV1 {
public:
    WorldMapPolygonStyleLayer m_polygonStyle = (WorldMapPolygonStyleLayer)this.m_layer;

   WorldMapStyleV1$WorldMapPolygonStyleLayerV1(WorldMapStyleV1 var1, std::string var2) {
      super(var1, std::make_shared<WorldMapPolygonStyleLayer>(var2));
   }

    void setFilter(const std::string& var1, const std::string& var2) {
      this.m_polygonStyle.m_filterKey = var1;
      this.m_polygonStyle.m_filterValue = var2;
      this.m_polygonStyle.m_filter = (var2x, var3) -> var2x.hasPolygon() && var2 == var2x.m_properties.get(var1));
   }

    std::string getFilterKey() {
      return this.m_polygonStyle.m_filterKey;
   }

    std::string getFilterValue() {
      return this.m_polygonStyle.m_filterValue;
   }

    void addFill(float var1, int var2, int var3, int var4, int var5) {
      this.m_polygonStyle.m_fill.push_back(std::make_shared<ColorStop>(var1, var2, var3, var4, var5));
   }

    void addScale(float var1, float var2) {
      this.m_polygonStyle.m_scale.push_back(std::make_shared<FloatStop>(var1, var2));
   }

    void addTexture(float var1, const std::string& var2) {
      this.m_polygonStyle.m_texture.push_back(std::make_shared<TextureStop>(var1, var2));
   }

    void removeFill(int var1) {
      this.m_polygonStyle.m_fill.remove(var1);
   }

    void removeTexture(int var1) {
      this.m_polygonStyle.m_texture.remove(var1);
   }

    void moveFill(int var1, int var2) {
    ColorStop var3 = (ColorStop)this.m_polygonStyle.m_fill.remove(var1);
      this.m_polygonStyle.m_fill.push_back(var2, var3);
   }

    void moveTexture(int var1, int var2) {
    TextureStop var3 = (TextureStop)this.m_polygonStyle.m_texture.remove(var1);
      this.m_polygonStyle.m_texture.push_back(var2, var3);
   }

    int getFillStops() {
      return this.m_polygonStyle.m_fill.size();
   }

    void setFillRGBA(int var1, int var2, int var3, int var4, int var5) {
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).r = var2;
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).g = var3;
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).b = var4;
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).a = var5;
   }

    void setFillZoom(int var1, float var2) {
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

    float getFillZoom(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).m_zoom;
   }

    int getFillRed(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).r;
   }

    int getFillGreen(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).g;
   }

    int getFillBlue(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).b;
   }

    int getFillAlpha(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).a;
   }

    int getTextureStops() {
      return this.m_polygonStyle.m_texture.size();
   }

    void setTextureZoom(int var1, float var2) {
      ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

    float getTextureZoom(int var1) {
      return ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).m_zoom;
   }

    void setTexturePath(int var1, const std::string& var2) {
      ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texturePath = var2;
      ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texture = Texture.getTexture(var2);
   }

    std::string getTexturePath(int var1) {
      return ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texturePath;
   }

    Texture getTexture(int var1) {
      return ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texture;
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
