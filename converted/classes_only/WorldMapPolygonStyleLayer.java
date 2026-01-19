package zombie.worldMap.styles;

import java.util.ArrayList;
import zombie.core.textures.Texture;
import zombie.worldMap.WorldMapFeature;
import zombie.worldMap.styles.WorldMapStyleLayer.ColorStop;
import zombie.worldMap.styles.WorldMapStyleLayer.FloatStop;
import zombie.worldMap.styles.WorldMapStyleLayer.RGBAf;
import zombie.worldMap.styles.WorldMapStyleLayer.RenderArgs;
import zombie.worldMap.styles.WorldMapStyleLayer.TextureStop;

public class WorldMapPolygonStyleLayer extends WorldMapStyleLayer {
   public final ArrayList<ColorStop> m_fill = new ArrayList<>();
   public final ArrayList<TextureStop> m_texture = new ArrayList<>();
   public final ArrayList<FloatStop> m_scale = new ArrayList<>();

   public WorldMapPolygonStyleLayer(String var1) {
      super(var1);
   }

   public String getTypeString() {
      return "Polygon";
   }

   public void render(WorldMapFeature var1, RenderArgs var2) {
      RGBAf var3 = this.evalColor(var2, this.m_fill);
      if (var3.a < 0.01F) {
         RGBAf.s_pool.release(var3);
      } else {
         float var4 = this.evalFloat(var2, this.m_scale);
         Texture var5 = this.evalTexture(var2, this.m_texture);
         if (var5 != null && var5.isReady()) {
            var2.drawer.fillPolygon(var2, var1, var3, var5, var4);
         } else {
            var2.drawer.fillPolygon(var2, var1, var3);
         }

         RGBAf.s_pool.release(var3);
      }
   }
}
