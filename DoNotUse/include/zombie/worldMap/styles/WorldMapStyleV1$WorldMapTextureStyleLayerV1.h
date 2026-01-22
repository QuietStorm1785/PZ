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
#include "zombie/worldMap/styles/WorldMapStyleLayer/TextureStop.h"
#include "zombie/worldMap/styles/WorldMapStyleV1/WorldMapStyleLayerV1.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleV1 {
public:
    WorldMapTextureStyleLayer m_textureStyle = (WorldMapTextureStyleLayer)this.m_layer;

   WorldMapStyleV1$WorldMapTextureStyleLayerV1(WorldMapStyleV1 var1, std::string var2) {
      super(var1, std::make_shared<WorldMapTextureStyleLayer>(var2));
   }

    void addFill(float var1, int var2, int var3, int var4, int var5) {
      this.m_textureStyle.m_fill.push_back(std::make_shared<ColorStop>(var1, var2, var3, var4, var5));
   }

    void addTexture(float var1, const std::string& var2) {
      this.m_textureStyle.m_texture.push_back(std::make_shared<TextureStop>(var1, var2));
   }

    void removeFill(int var1) {
      this.m_textureStyle.m_fill.remove(var1);
   }

    void removeAllFill() {
      this.m_textureStyle.m_fill.clear();
   }

    void removeTexture(int var1) {
      this.m_textureStyle.m_texture.remove(var1);
   }

    void removeAllTexture() {
      this.m_textureStyle.m_texture.clear();
   }

    void moveFill(int var1, int var2) {
    ColorStop var3 = (ColorStop)this.m_textureStyle.m_fill.remove(var1);
      this.m_textureStyle.m_fill.push_back(var2, var3);
   }

    void moveTexture(int var1, int var2) {
    TextureStop var3 = (TextureStop)this.m_textureStyle.m_texture.remove(var1);
      this.m_textureStyle.m_texture.push_back(var2, var3);
   }

    void setBoundsInSquares(int var1, int var2, int var3, int var4) {
      this.m_textureStyle.m_worldX1 = var1;
      this.m_textureStyle.m_worldY1 = var2;
      this.m_textureStyle.m_worldX2 = var3;
      this.m_textureStyle.m_worldY2 = var4;
   }

    int getMinXInSquares() {
      return this.m_textureStyle.m_worldX1;
   }

    int getMinYInSquares() {
      return this.m_textureStyle.m_worldY1;
   }

    int getMaxXInSquares() {
      return this.m_textureStyle.m_worldX2;
   }

    int getMaxYInSquares() {
      return this.m_textureStyle.m_worldY2;
   }

    int getWidthInSquares() {
      return this.m_textureStyle.m_worldX2 - this.m_textureStyle.m_worldX1;
   }

    int getHeightInSquares() {
      return this.m_textureStyle.m_worldY2 - this.m_textureStyle.m_worldY1;
   }

    void setTile(bool var1) {
      this.m_textureStyle.m_tile = var1;
   }

    bool isTile() {
      return this.m_textureStyle.m_tile;
   }

    void setUseWorldBounds(bool var1) {
      this.m_textureStyle.m_useWorldBounds = var1;
   }

    bool isUseWorldBounds() {
      return this.m_textureStyle.m_useWorldBounds;
   }

    int getFillStops() {
      return this.m_textureStyle.m_fill.size();
   }

    void setFillRGBA(int var1, int var2, int var3, int var4, int var5) {
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).r = var2;
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).g = var3;
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).b = var4;
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).a = var5;
   }

    void setFillZoom(int var1, float var2) {
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

    float getFillZoom(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).m_zoom;
   }

    int getFillRed(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).r;
   }

    int getFillGreen(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).g;
   }

    int getFillBlue(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).b;
   }

    int getFillAlpha(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).a;
   }

    int getTextureStops() {
      return this.m_textureStyle.m_texture.size();
   }

    void setTextureZoom(int var1, float var2) {
      ((TextureStop)this.m_textureStyle.m_texture.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

    float getTextureZoom(int var1) {
      return ((TextureStop)this.m_textureStyle.m_texture.get(var1)).m_zoom;
   }

    void setTexturePath(int var1, const std::string& var2) {
      ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texturePath = var2;
      ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texture = Texture.getTexture(var2);
   }

    std::string getTexturePath(int var1) {
      return ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texturePath;
   }

    Texture getTexture(int var1) {
      return ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texture;
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
