#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/PooledObject.h"

namespace zombie {
namespace worldMap {
namespace symbols {


class WorldMapSymbolsV1 {
public:
    WorldMapSymbolsV1 m_owner;
    WorldMapBaseSymbol m_symbol;

   protected WorldMapSymbolsV1$WorldMapBaseSymbolV1() {
   }

   WorldMapSymbolsV1$WorldMapBaseSymbolV1 init(WorldMapSymbolsV1 var1, WorldMapBaseSymbol var2) {
      this.m_owner = var1;
      this.m_symbol = var2;
    return this;
   }

    float getWorldX() {
      return this.m_symbol.m_x;
   }

    float getWorldY() {
      return this.m_symbol.m_y;
   }

    float getDisplayX() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.m_layoutX + this.m_owner.m_ui.getAPIv1().worldOriginX();
   }

    float getDisplayY() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.m_layoutY + this.m_owner.m_ui.getAPIv1().worldOriginY();
   }

    float getDisplayWidth() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.widthScaled(this.m_owner.m_ui);
   }

    float getDisplayHeight() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.heightScaled(this.m_owner.m_ui);
   }

    void setAnchor(float var1, float var2) {
      this.m_symbol.setAnchor(var1, var2);
   }

    void setPosition(float var1, float var2) {
      this.m_symbol.setPosition(var1, var2);
      this.m_owner.m_uiSymbols.invalidateLayout();
   }

    void setCollide(bool var1) {
      this.m_symbol.setCollide(var1);
   }

    void setVisible(bool var1) {
      this.m_symbol.setVisible(var1);
   }

    bool isVisible() {
      return this.m_symbol.isVisible();
   }

    void setRGBA(float var1, float var2, float var3, float var4) {
      this.m_symbol.setRGBA(var1, var2, var3, var4);
   }

    float getRed() {
      return this.m_symbol.m_r;
   }

    float getGreen() {
      return this.m_symbol.m_g;
   }

    float getBlue() {
      return this.m_symbol.m_b;
   }

    float getAlpha() {
      return this.m_symbol.m_a;
   }

    void setScale(float var1) {
      this.m_symbol.setScale(var1);
   }

    bool isText() {
    return false;
   }

    bool isTexture() {
    return false;
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
