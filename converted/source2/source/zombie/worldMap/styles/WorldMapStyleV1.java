package zombie.worldMap.styles;

import java.util.ArrayList;
import java.util.Objects;
import zombie.Lua.LuaManager.Exposer;
import zombie.worldMap.UIWorldMap;
import zombie.worldMap.UIWorldMapV1;
import zombie.worldMap.styles.WorldMapStyleV1.WorldMapLineStyleLayerV1;
import zombie.worldMap.styles.WorldMapStyleV1.WorldMapPolygonStyleLayerV1;
import zombie.worldMap.styles.WorldMapStyleV1.WorldMapStyleLayerV1;
import zombie.worldMap.styles.WorldMapStyleV1.WorldMapTextureStyleLayerV1;

public class WorldMapStyleV1 {
   public UIWorldMap m_ui;
   public UIWorldMapV1 m_api;
   public WorldMapStyle m_style;
   public final ArrayList<WorldMapStyleLayerV1> m_layers = new ArrayList<>();

   public WorldMapStyleV1(UIWorldMap var1) {
      Objects.requireNonNull(var1);
      this.m_ui = var1;
      this.m_api = var1.getAPIv1();
      this.m_style = this.m_api.getStyle();
   }

   public WorldMapStyleLayerV1 newLineLayer(String var1) throws IllegalArgumentException {
      WorldMapLineStyleLayerV1 var2 = new WorldMapLineStyleLayerV1(this, var1);
      this.m_layers.add(var2);
      return var2;
   }

   public WorldMapStyleLayerV1 newPolygonLayer(String var1) throws IllegalArgumentException {
      WorldMapPolygonStyleLayerV1 var2 = new WorldMapPolygonStyleLayerV1(this, var1);
      this.m_layers.add(var2);
      return var2;
   }

   public WorldMapStyleLayerV1 newTextureLayer(String var1) throws IllegalArgumentException {
      WorldMapTextureStyleLayerV1 var2 = new WorldMapTextureStyleLayerV1(this, var1);
      this.m_layers.add(var2);
      return var2;
   }

   public int getLayerCount() {
      return this.m_layers.size();
   }

   public WorldMapStyleLayerV1 getLayerByIndex(int var1) {
      return this.m_layers.get(var1);
   }

   public WorldMapStyleLayerV1 getLayerByName(String var1) {
      int var2 = this.indexOfLayer(var1);
      return var2 == -1 ? null : this.m_layers.get(var2);
   }

   public int indexOfLayer(String var1) {
      for (int var2 = 0; var2 < this.m_layers.size(); var2++) {
         WorldMapStyleLayerV1 var3 = this.m_layers.get(var2);
         if (var3.m_layer.m_id.equals(var1)) {
            return var2;
         }
      }

      return -1;
   }

   public void moveLayer(int var1, int var2) {
      WorldMapStyleLayer var3 = (WorldMapStyleLayer)this.m_style.m_layers.remove(var1);
      this.m_style.m_layers.add(var2, var3);
      WorldMapStyleLayerV1 var4 = this.m_layers.remove(var1);
      this.m_layers.add(var2, var4);
   }

   public void removeLayerById(String var1) {
      int var2 = this.indexOfLayer(var1);
      if (var2 != -1) {
         this.removeLayerByIndex(var2);
      }
   }

   public void removeLayerByIndex(int var1) {
      this.m_style.m_layers.remove(var1);
      this.m_layers.remove(var1);
   }

   public void clear() {
      this.m_style.m_layers.clear();
      this.m_layers.clear();
   }

   public static void setExposed(Exposer var0) {
      var0.setExposed(WorldMapStyleV1.class);
      var0.setExposed(WorldMapStyleLayerV1.class);
      var0.setExposed(WorldMapLineStyleLayerV1.class);
      var0.setExposed(WorldMapPolygonStyleLayerV1.class);
      var0.setExposed(WorldMapTextureStyleLayerV1.class);
   }
}
