package zombie.worldMap.styles;

import zombie.core.math.PZMath;
import zombie.core.textures.Texture;
import zombie.worldMap.styles.WorldMapStyleLayer.ColorStop;
import zombie.worldMap.styles.WorldMapStyleLayer.TextureStop;
import zombie.worldMap.styles.WorldMapStyleV1.WorldMapStyleLayerV1;

public class WorldMapStyleV1$WorldMapTextureStyleLayerV1 extends WorldMapStyleLayerV1 {
   WorldMapTextureStyleLayer m_textureStyle = (WorldMapTextureStyleLayer)this.m_layer;

   WorldMapStyleV1$WorldMapTextureStyleLayerV1(WorldMapStyleV1 var1, String var2) {
      super(var1, new WorldMapTextureStyleLayer(var2));
   }

   public void addFill(float var1, int var2, int var3, int var4, int var5) {
      this.m_textureStyle.m_fill.add(new ColorStop(var1, var2, var3, var4, var5));
   }

   public void addTexture(float var1, String var2) {
      this.m_textureStyle.m_texture.add(new TextureStop(var1, var2));
   }

   public void removeFill(int var1) {
      this.m_textureStyle.m_fill.remove(var1);
   }

   public void removeAllFill() {
      this.m_textureStyle.m_fill.clear();
   }

   public void removeTexture(int var1) {
      this.m_textureStyle.m_texture.remove(var1);
   }

   public void removeAllTexture() {
      this.m_textureStyle.m_texture.clear();
   }

   public void moveFill(int var1, int var2) {
      ColorStop var3 = (ColorStop)this.m_textureStyle.m_fill.remove(var1);
      this.m_textureStyle.m_fill.add(var2, var3);
   }

   public void moveTexture(int var1, int var2) {
      TextureStop var3 = (TextureStop)this.m_textureStyle.m_texture.remove(var1);
      this.m_textureStyle.m_texture.add(var2, var3);
   }

   public void setBoundsInSquares(int var1, int var2, int var3, int var4) {
      this.m_textureStyle.m_worldX1 = var1;
      this.m_textureStyle.m_worldY1 = var2;
      this.m_textureStyle.m_worldX2 = var3;
      this.m_textureStyle.m_worldY2 = var4;
   }

   public int getMinXInSquares() {
      return this.m_textureStyle.m_worldX1;
   }

   public int getMinYInSquares() {
      return this.m_textureStyle.m_worldY1;
   }

   public int getMaxXInSquares() {
      return this.m_textureStyle.m_worldX2;
   }

   public int getMaxYInSquares() {
      return this.m_textureStyle.m_worldY2;
   }

   public int getWidthInSquares() {
      return this.m_textureStyle.m_worldX2 - this.m_textureStyle.m_worldX1;
   }

   public int getHeightInSquares() {
      return this.m_textureStyle.m_worldY2 - this.m_textureStyle.m_worldY1;
   }

   public void setTile(boolean var1) {
      this.m_textureStyle.m_tile = var1;
   }

   public boolean isTile() {
      return this.m_textureStyle.m_tile;
   }

   public void setUseWorldBounds(boolean var1) {
      this.m_textureStyle.m_useWorldBounds = var1;
   }

   public boolean isUseWorldBounds() {
      return this.m_textureStyle.m_useWorldBounds;
   }

   public int getFillStops() {
      return this.m_textureStyle.m_fill.size();
   }

   public void setFillRGBA(int var1, int var2, int var3, int var4, int var5) {
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).r = var2;
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).g = var3;
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).b = var4;
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).a = var5;
   }

   public void setFillZoom(int var1, float var2) {
      ((ColorStop)this.m_textureStyle.m_fill.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

   public float getFillZoom(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).m_zoom;
   }

   public int getFillRed(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).r;
   }

   public int getFillGreen(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).g;
   }

   public int getFillBlue(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).b;
   }

   public int getFillAlpha(int var1) {
      return ((ColorStop)this.m_textureStyle.m_fill.get(var1)).a;
   }

   public int getTextureStops() {
      return this.m_textureStyle.m_texture.size();
   }

   public void setTextureZoom(int var1, float var2) {
      ((TextureStop)this.m_textureStyle.m_texture.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

   public float getTextureZoom(int var1) {
      return ((TextureStop)this.m_textureStyle.m_texture.get(var1)).m_zoom;
   }

   public void setTexturePath(int var1, String var2) {
      ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texturePath = var2;
      ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texture = Texture.getTexture(var2);
   }

   public String getTexturePath(int var1) {
      return ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texturePath;
   }

   public Texture getTexture(int var1) {
      return ((TextureStop)this.m_textureStyle.m_texture.get(var1)).texture;
   }
}
