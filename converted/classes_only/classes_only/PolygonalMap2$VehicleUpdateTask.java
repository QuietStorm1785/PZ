package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.IVehicleTask;
import zombie.vehicles.PolygonalMap2.Vehicle;
import zombie.vehicles.PolygonalMap2.VehiclePoly;

final class PolygonalMap2$VehicleUpdateTask implements IVehicleTask {
   PolygonalMap2 map;
   BaseVehicle vehicle;
   final VehiclePoly poly = new VehiclePoly();
   final VehiclePoly polyPlusRadius = new VehiclePoly();
   float upVectorDot;
   static final ArrayDeque<PolygonalMap2$VehicleUpdateTask> pool = new ArrayDeque<>();

   private PolygonalMap2$VehicleUpdateTask() {
   }

   public void init(PolygonalMap2 var1, BaseVehicle var2) {
      this.map = var1;
      this.vehicle = var2;
      this.poly.init(var2.getPoly());
      this.polyPlusRadius.init(var2.getPolyPlusRadius());
      this.upVectorDot = var2.getUpVectorDot();
   }

   public void execute() {
      Vehicle var1 = (Vehicle)this.map.vehicleMap.get(this.vehicle);
      var1.poly.init(this.poly);
      var1.polyPlusRadius.init(this.polyPlusRadius);
      var1.upVectorDot = this.upVectorDot;
      this.vehicle = null;
   }

   static PolygonalMap2$VehicleUpdateTask alloc() {
      synchronized (pool) {
         return pool.isEmpty() ? new PolygonalMap2$VehicleUpdateTask() : pool.pop();
      }
   }

   public void release() {
      synchronized (pool) {
         if (!$assertionsDisabled && pool.contains(this)) {
            throw new AssertionError();
         } else {
            pool.push(this);
         }
      }
   }
}
