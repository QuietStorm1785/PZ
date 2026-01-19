package zombie.vehicles;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.vehicles.PolygonalMap2.VehicleRect;

final class PolygonalMap2$VehicleCluster {
   int z;
   final ArrayList<VehicleRect> rects = new ArrayList<>();
   static final ArrayDeque<PolygonalMap2$VehicleCluster> pool = new ArrayDeque<>();

   private PolygonalMap2$VehicleCluster() {
   }

   PolygonalMap2$VehicleCluster init() {
      this.rects.clear();
      return this;
   }

   void merge(PolygonalMap2$VehicleCluster var1) {
      for (int var2 = 0; var2 < var1.rects.size(); var2++) {
         VehicleRect var3 = var1.rects.get(var2);
         var3.cluster = this;
      }

      this.rects.addAll(var1.rects);
      var1.rects.clear();
   }

   VehicleRect bounds() {
      int var1 = Integer.MAX_VALUE;
      int var2 = Integer.MAX_VALUE;
      int var3 = Integer.MIN_VALUE;
      int var4 = Integer.MIN_VALUE;

      for (int var5 = 0; var5 < this.rects.size(); var5++) {
         VehicleRect var6 = this.rects.get(var5);
         var1 = Math.min(var1, var6.left());
         var2 = Math.min(var2, var6.top());
         var3 = Math.max(var3, var6.right());
         var4 = Math.max(var4, var6.bottom());
      }

      return VehicleRect.alloc().init(var1, var2, var3 - var1, var4 - var2, this.z);
   }

   static PolygonalMap2$VehicleCluster alloc() {
      return pool.isEmpty() ? new PolygonalMap2$VehicleCluster() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
