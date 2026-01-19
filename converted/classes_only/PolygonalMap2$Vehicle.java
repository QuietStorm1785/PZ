package zombie.vehicles;

import gnu.trove.list.array.TFloatArrayList;
import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.VehiclePoly;

final class PolygonalMap2$Vehicle {
   final VehiclePoly poly = new VehiclePoly();
   final VehiclePoly polyPlusRadius = new VehiclePoly();
   final TFloatArrayList crawlOffsets = new TFloatArrayList();
   float upVectorDot;
   static final ArrayDeque<PolygonalMap2$Vehicle> pool = new ArrayDeque<>();

   private PolygonalMap2$Vehicle() {
   }

   static PolygonalMap2$Vehicle alloc() {
      return pool.isEmpty() ? new PolygonalMap2$Vehicle() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
