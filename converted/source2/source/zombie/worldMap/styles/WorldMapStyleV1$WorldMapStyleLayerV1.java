package zombie.worldMap.styles;

public class WorldMapStyleV1$WorldMapStyleLayerV1 {
   WorldMapStyleV1 m_owner;
   WorldMapStyleLayer m_layer;

   WorldMapStyleV1$WorldMapStyleLayerV1(WorldMapStyleV1 var1, WorldMapStyleLayer var2) {
      this.m_owner = var1;
      this.m_layer = var2;
      var1.m_style.m_layers.add(this.m_layer);
   }

   public String getTypeString() {
      return this.m_layer.getTypeString();
   }

   public void setId(String var1) {
      this.m_layer.m_id = var1;
   }

   public String getId() {
      return this.m_layer.m_id;
   }

   public void setMinZoom(float var1) {
      this.m_layer.m_minZoom = var1;
   }

   public float getMinZoom() {
      return this.m_layer.m_minZoom;
   }
}
