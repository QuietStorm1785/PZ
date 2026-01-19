package zombie.worldMap;

import java.util.ArrayList;
import zombie.worldMap.WorldMapGeometry.Type;

public final class WorldMapFeature {
   public final WorldMapCell m_cell;
   public final ArrayList<WorldMapGeometry> m_geometries = new ArrayList<>();
   public WorldMapProperties m_properties = null;

   WorldMapFeature(WorldMapCell var1) {
      this.m_cell = var1;
   }

   public boolean hasLineString() {
      for (int var1 = 0; var1 < this.m_geometries.size(); var1++) {
         if (this.m_geometries.get(var1).m_type == Type.LineString) {
            return true;
         }
      }

      return false;
   }

   public boolean hasPoint() {
      for (int var1 = 0; var1 < this.m_geometries.size(); var1++) {
         if (this.m_geometries.get(var1).m_type == Type.Point) {
            return true;
         }
      }

      return false;
   }

   public boolean hasPolygon() {
      for (int var1 = 0; var1 < this.m_geometries.size(); var1++) {
         if (this.m_geometries.get(var1).m_type == Type.Polygon) {
            return true;
         }
      }

      return false;
   }

   public boolean containsPoint(float var1, float var2) {
      for (int var3 = 0; var3 < this.m_geometries.size(); var3++) {
         WorldMapGeometry var4 = this.m_geometries.get(var3);
         if (var4.containsPoint(var1, var2)) {
            return true;
         }
      }

      return false;
   }

   public void dispose() {
      for (WorldMapGeometry var2 : this.m_geometries) {
         var2.dispose();
      }

      this.m_properties.clear();
   }
}
