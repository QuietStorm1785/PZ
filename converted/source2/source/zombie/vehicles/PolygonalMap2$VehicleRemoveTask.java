package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.IVehicleTask;
import zombie.vehicles.PolygonalMap2.Vehicle;

final class PolygonalMap2$VehicleRemoveTask implements IVehicleTask {
   PolygonalMap2 map;
   BaseVehicle vehicle;
   static final ArrayDeque<PolygonalMap2$VehicleRemoveTask> pool = new ArrayDeque<>();

   private PolygonalMap2$VehicleRemoveTask() {
   }

   public void init(PolygonalMap2 var1, BaseVehicle var2) {
      this.map = var1;
      this.vehicle = var2;
   }

   public void execute() {
      Vehicle var1 = (Vehicle)this.map.vehicleMap.remove(this.vehicle);
      if (var1 != null) {
         this.map.vehicles.remove(var1);
         var1.release();
      }

      this.vehicle = null;
   }

   static PolygonalMap2$VehicleRemoveTask alloc() {
      synchronized (pool) {
         return pool.isEmpty() ? new PolygonalMap2$VehicleRemoveTask() : pool.pop();
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
