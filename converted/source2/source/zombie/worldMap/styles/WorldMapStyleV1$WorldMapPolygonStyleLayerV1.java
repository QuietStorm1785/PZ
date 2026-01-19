package zombie.worldMap.styles;

import zombie.core.math.PZMath;
import zombie.core.textures.Texture;
import zombie.worldMap.styles.WorldMapStyleLayer.ColorStop;
import zombie.worldMap.styles.WorldMapStyleLayer.FloatStop;
import zombie.worldMap.styles.WorldMapStyleLayer.TextureStop;
import zombie.worldMap.styles.WorldMapStyleV1.WorldMapStyleLayerV1;

public class WorldMapStyleV1$WorldMapPolygonStyleLayerV1 extends WorldMapStyleLayerV1 {
   WorldMapPolygonStyleLayer m_polygonStyle = (WorldMapPolygonStyleLayer)this.m_layer;

   WorldMapStyleV1$WorldMapPolygonStyleLayerV1(WorldMapStyleV1 var1, String var2) {
      super(var1, new WorldMapPolygonStyleLayer(var2));
   }

   public void setFilter(String var1, String var2) {
      this.m_polygonStyle.m_filterKey = var1;
      this.m_polygonStyle.m_filterValue = var2;
      this.m_polygonStyle.m_filter = (var2x, var3) -> var2x.hasPolygon() && var2.equals(var2x.m_properties.get(var1));
   }

   public String getFilterKey() {
      return this.m_polygonStyle.m_filterKey;
   }

   public String getFilterValue() {
      return this.m_polygonStyle.m_filterValue;
   }

   public void addFill(float var1, int var2, int var3, int var4, int var5) {
      this.m_polygonStyle.m_fill.add(new ColorStop(var1, var2, var3, var4, var5));
   }

   public void addScale(float var1, float var2) {
      this.m_polygonStyle.m_scale.add(new FloatStop(var1, var2));
   }

   public void addTexture(float var1, String var2) {
      this.m_polygonStyle.m_texture.add(new TextureStop(var1, var2));
   }

   public void removeFill(int var1) {
      this.m_polygonStyle.m_fill.remove(var1);
   }

   public void removeTexture(int var1) {
      this.m_polygonStyle.m_texture.remove(var1);
   }

   public void moveFill(int var1, int var2) {
      ColorStop var3 = (ColorStop)this.m_polygonStyle.m_fill.remove(var1);
      this.m_polygonStyle.m_fill.add(var2, var3);
   }

   public void moveTexture(int var1, int var2) {
      TextureStop var3 = (TextureStop)this.m_polygonStyle.m_texture.remove(var1);
      this.m_polygonStyle.m_texture.add(var2, var3);
   }

   public int getFillStops() {
      return this.m_polygonStyle.m_fill.size();
   }

   public void setFillRGBA(int var1, int var2, int var3, int var4, int var5) {
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).r = var2;
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).g = var3;
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).b = var4;
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).a = var5;
   }

   public void setFillZoom(int var1, float var2) {
      ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

   public float getFillZoom(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).m_zoom;
   }

   public int getFillRed(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).r;
   }

   public int getFillGreen(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).g;
   }

   public int getFillBlue(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).b;
   }

   public int getFillAlpha(int var1) {
      return ((ColorStop)this.m_polygonStyle.m_fill.get(var1)).a;
   }

   public int getTextureStops() {
      return this.m_polygonStyle.m_texture.size();
   }

   public void setTextureZoom(int var1, float var2) {
      ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).m_zoom = PZMath.clamp(var2, 0.0F, 24.0F);
   }

   public float getTextureZoom(int var1) {
      return ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).m_zoom;
   }

   public void setTexturePath(int var1, String var2) {
      ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texturePath = var2;
      ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texture = Texture.getTexture(var2);
   }

   public String getTexturePath(int var1) {
      return ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texturePath;
   }

   public Texture getTexture(int var1) {
      return ((TextureStop)this.m_polygonStyle.m_texture.get(var1)).texture;
   }
}
