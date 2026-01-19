package zombie.worldMap.styles;

import java.util.ArrayList;
import zombie.core.math.PZMath;
import zombie.core.textures.Texture;
import zombie.worldMap.WorldMapFeature;
import zombie.worldMap.styles.WorldMapStyleLayer.ColorStop;
import zombie.worldMap.styles.WorldMapStyleLayer.FilterArgs;
import zombie.worldMap.styles.WorldMapStyleLayer.FloatStop;
import zombie.worldMap.styles.WorldMapStyleLayer.IWorldMapStyleFilter;
import zombie.worldMap.styles.WorldMapStyleLayer.RGBAf;
import zombie.worldMap.styles.WorldMapStyleLayer.RenderArgs;
import zombie.worldMap.styles.WorldMapStyleLayer.Stop;
import zombie.worldMap.styles.WorldMapStyleLayer.TextureStop;

public abstract class WorldMapStyleLayer {
   public String m_id;
   public float m_minZoom = 0.0F;
   public IWorldMapStyleFilter m_filter;
   public String m_filterKey;
   public String m_filterValue;

   public WorldMapStyleLayer(String var1) {
      this.m_id = var1;
   }

   public abstract String getTypeString();

   static <S extends Stop> int findStop(float var0, ArrayList<S> var1) {
      if (var1.isEmpty()) {
         return -2;
      } else if (var0 <= ((Stop)var1.get(0)).m_zoom) {
         return -1;
      } else {
         for (int var2 = 0; var2 < var1.size() - 1; var2++) {
            if (var0 <= ((Stop)var1.get(var2 + 1)).m_zoom) {
               return var2;
            }
         }

         return var1.size() - 1;
      }
   }

   protected RGBAf evalColor(RenderArgs var1, ArrayList<ColorStop> var2) {
      if (var2.isEmpty()) {
         return ((RGBAf)RGBAf.s_pool.alloc()).init(1.0F, 1.0F, 1.0F, 1.0F);
      } else {
         float var3 = var1.drawer.m_zoomF;
         int var4 = findStop(var3, var2);
         int var5 = var4 == -1 ? 0 : var4;
         int var6 = PZMath.min(var4 + 1, var2.size() - 1);
         ColorStop var7 = (ColorStop)var2.get(var5);
         ColorStop var8 = (ColorStop)var2.get(var6);
         float var9 = var5 == var6 ? 1.0F : (PZMath.clamp(var3, var7.m_zoom, var8.m_zoom) - var7.m_zoom) / (var8.m_zoom - var7.m_zoom);
         float var10 = PZMath.lerp(var7.r, var8.r, var9) / 255.0F;
         float var11 = PZMath.lerp(var7.g, var8.g, var9) / 255.0F;
         float var12 = PZMath.lerp(var7.b, var8.b, var9) / 255.0F;
         float var13 = PZMath.lerp(var7.a, var8.a, var9) / 255.0F;
         return ((RGBAf)RGBAf.s_pool.alloc()).init(var10, var11, var12, var13);
      }
   }

   protected float evalFloat(RenderArgs var1, ArrayList<FloatStop> var2) {
      if (var2.isEmpty()) {
         return 1.0F;
      } else {
         float var3 = var1.drawer.m_zoomF;
         int var4 = findStop(var3, var2);
         int var5 = var4 == -1 ? 0 : var4;
         int var6 = PZMath.min(var4 + 1, var2.size() - 1);
         FloatStop var7 = (FloatStop)var2.get(var5);
         FloatStop var8 = (FloatStop)var2.get(var6);
         float var9 = var5 == var6 ? 1.0F : (PZMath.clamp(var3, var7.m_zoom, var8.m_zoom) - var7.m_zoom) / (var8.m_zoom - var7.m_zoom);
         return PZMath.lerp(var7.f, var8.f, var9);
      }
   }

   protected Texture evalTexture(RenderArgs var1, ArrayList<TextureStop> var2) {
      if (var2.isEmpty()) {
         return null;
      } else {
         float var3 = var1.drawer.m_zoomF;
         int var4 = findStop(var3, var2);
         int var5 = var4 == -1 ? 0 : var4;
         int var6 = PZMath.min(var4 + 1, var2.size() - 1);
         TextureStop var7 = (TextureStop)var2.get(var5);
         TextureStop var8 = (TextureStop)var2.get(var6);
         if (var7 == var8) {
            return var3 < var7.m_zoom ? null : var7.texture;
         } else if (!(var3 < var7.m_zoom) && !(var3 > var8.m_zoom)) {
            float var9 = var5 == var6 ? 1.0F : (PZMath.clamp(var3, var7.m_zoom, var8.m_zoom) - var7.m_zoom) / (var8.m_zoom - var7.m_zoom);
            return var9 < 0.5F ? var7.texture : var8.texture;
         } else {
            return null;
         }
      }
   }

   public boolean filter(WorldMapFeature var1, FilterArgs var2) {
      return this.m_filter == null ? false : this.m_filter.filter(var1, var2);
   }

   public abstract void render(WorldMapFeature var1, RenderArgs var2);

   public void renderCell(RenderArgs var1) {
   }
}
