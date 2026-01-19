package zombie.worldMap.symbols;

import zombie.util.PooledObject;

public class WorldMapSymbolsV1$WorldMapBaseSymbolV1 extends PooledObject {
   WorldMapSymbolsV1 m_owner;
   WorldMapBaseSymbol m_symbol;

   protected WorldMapSymbolsV1$WorldMapBaseSymbolV1() {
   }

   WorldMapSymbolsV1$WorldMapBaseSymbolV1 init(WorldMapSymbolsV1 var1, WorldMapBaseSymbol var2) {
      this.m_owner = var1;
      this.m_symbol = var2;
      return this;
   }

   public float getWorldX() {
      return this.m_symbol.m_x;
   }

   public float getWorldY() {
      return this.m_symbol.m_y;
   }

   public float getDisplayX() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.m_layoutX + this.m_owner.m_ui.getAPIv1().worldOriginX();
   }

   public float getDisplayY() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.m_layoutY + this.m_owner.m_ui.getAPIv1().worldOriginY();
   }

   public float getDisplayWidth() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.widthScaled(this.m_owner.m_ui);
   }

   public float getDisplayHeight() {
      this.m_owner.m_uiSymbols.checkLayout(this.m_owner.m_ui);
      return this.m_symbol.heightScaled(this.m_owner.m_ui);
   }

   public void setAnchor(float var1, float var2) {
      this.m_symbol.setAnchor(var1, var2);
   }

   public void setPosition(float var1, float var2) {
      this.m_symbol.setPosition(var1, var2);
      this.m_owner.m_uiSymbols.invalidateLayout();
   }

   public void setCollide(boolean var1) {
      this.m_symbol.setCollide(var1);
   }

   public void setVisible(boolean var1) {
      this.m_symbol.setVisible(var1);
   }

   public boolean isVisible() {
      return this.m_symbol.isVisible();
   }

   public void setRGBA(float var1, float var2, float var3, float var4) {
      this.m_symbol.setRGBA(var1, var2, var3, var4);
   }

   public float getRed() {
      return this.m_symbol.m_r;
   }

   public float getGreen() {
      return this.m_symbol.m_g;
   }

   public float getBlue() {
      return this.m_symbol.m_b;
   }

   public float getAlpha() {
      return this.m_symbol.m_a;
   }

   public void setScale(float var1) {
      this.m_symbol.setScale(var1);
   }

   public boolean isText() {
      return false;
   }

   public boolean isTexture() {
      return false;
   }
}
