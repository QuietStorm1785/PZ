package zombie.worldMap.styles;

import zombie.worldMap.styles.WorldMapStyleLayer.ColorStop;
import zombie.worldMap.styles.WorldMapStyleLayer.FloatStop;
import zombie.worldMap.styles.WorldMapStyleV1.WorldMapStyleLayerV1;

public class WorldMapStyleV1$WorldMapLineStyleLayerV1 extends WorldMapStyleLayerV1 {
   WorldMapLineStyleLayer m_lineStyle = (WorldMapLineStyleLayer)this.m_layer;

   WorldMapStyleV1$WorldMapLineStyleLayerV1(WorldMapStyleV1 var1, String var2) {
      super(var1, new WorldMapLineStyleLayer(var2));
   }

   public void setFilter(String var1, String var2) {
      this.m_lineStyle.m_filterKey = var1;
      this.m_lineStyle.m_filterValue = var2;
      this.m_lineStyle.m_filter = (var2x, var3) -> var2x.hasLineString() && var2.equals(var2x.m_properties.get(var1));
   }

   public void addFill(float var1, int var2, int var3, int var4, int var5) {
      this.m_lineStyle.m_fill.add(new ColorStop(var1, var2, var3, var4, var5));
   }

   public void addLineWidth(float var1, float var2) {
      this.m_lineStyle.m_lineWidth.add(new FloatStop(var1, var2));
   }
}
