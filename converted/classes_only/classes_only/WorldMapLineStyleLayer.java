package zombie.worldMap.styles;

import java.util.ArrayList;
import zombie.core.math.PZMath;
import zombie.worldMap.WorldMapFeature;
import zombie.worldMap.styles.WorldMapStyleLayer.ColorStop;
import zombie.worldMap.styles.WorldMapStyleLayer.FloatStop;
import zombie.worldMap.styles.WorldMapStyleLayer.RGBAf;
import zombie.worldMap.styles.WorldMapStyleLayer.RenderArgs;

public class WorldMapLineStyleLayer extends WorldMapStyleLayer {
   public final ArrayList<ColorStop> m_fill = new ArrayList<>();
   public final ArrayList<FloatStop> m_lineWidth = new ArrayList<>();

   public WorldMapLineStyleLayer(String var1) {
      super(var1);
   }

   public String getTypeString() {
      return "Line";
   }

   public void render(WorldMapFeature var1, RenderArgs var2) {
      RGBAf var3 = this.evalColor(var2, this.m_fill);
      if (!(var3.a < 0.01F)) {
         float var4;
         if (var1.m_properties.containsKey("width")) {
            var4 = PZMath.tryParseFloat((String)var1.m_properties.get("width"), 1.0F) * var2.drawer.getWorldScale();
         } else {
            var4 = this.evalFloat(var2, this.m_lineWidth);
         }

         var2.drawer.drawLineString(var2, var1, var3, var4);
         RGBAf.s_pool.release(var3);
      }
   }
}
