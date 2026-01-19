package zombie.worldMap.styles;

import java.util.ArrayList;
import zombie.core.textures.Texture;
import zombie.worldMap.WorldMapFeature;
import zombie.worldMap.styles.WorldMapStyleLayer.ColorStop;
import zombie.worldMap.styles.WorldMapStyleLayer.FilterArgs;
import zombie.worldMap.styles.WorldMapStyleLayer.RGBAf;
import zombie.worldMap.styles.WorldMapStyleLayer.RenderArgs;
import zombie.worldMap.styles.WorldMapStyleLayer.TextureStop;

public class WorldMapTextureStyleLayer extends WorldMapStyleLayer {
   public int m_worldX1;
   public int m_worldY1;
   public int m_worldX2;
   public int m_worldY2;
   public boolean m_useWorldBounds = false;
   public final ArrayList<ColorStop> m_fill = new ArrayList<>();
   public final ArrayList<TextureStop> m_texture = new ArrayList<>();
   public boolean m_tile = false;

   public WorldMapTextureStyleLayer(String var1) {
      super(var1);
   }

   public String getTypeString() {
      return "Texture";
   }

   public boolean filter(WorldMapFeature var1, FilterArgs var2) {
      return false;
   }

   public void render(WorldMapFeature var1, RenderArgs var2) {
   }

   public void renderCell(RenderArgs var1) {
      if (this.m_useWorldBounds) {
         this.m_worldX1 = var1.renderer.getWorldMap().getMinXInSquares();
         this.m_worldY1 = var1.renderer.getWorldMap().getMinYInSquares();
         this.m_worldX2 = var1.renderer.getWorldMap().getMaxXInSquares() + 1;
         this.m_worldY2 = var1.renderer.getWorldMap().getMaxYInSquares() + 1;
      }

      RGBAf var2 = this.evalColor(var1, this.m_fill);
      if (var2.a < 0.01F) {
         RGBAf.s_pool.release(var2);
      } else {
         Texture var3 = this.evalTexture(var1, this.m_texture);
         if (var3 == null) {
            RGBAf.s_pool.release(var2);
         } else {
            if (this.m_tile) {
               var1.drawer.drawTextureTiled(var3, var2, this.m_worldX1, this.m_worldY1, this.m_worldX2, this.m_worldY2, var1.cellX, var1.cellY);
            } else {
               var1.drawer.drawTexture(var3, var2, this.m_worldX1, this.m_worldY1, this.m_worldX2, this.m_worldY2);
            }

            RGBAf.s_pool.release(var2);
         }
      }
   }
}
