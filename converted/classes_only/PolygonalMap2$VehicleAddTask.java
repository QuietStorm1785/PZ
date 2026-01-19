package zombie.vehicles;

import gnu.trove.list.array.TFloatArrayList;
import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.IVehicleTask;
import zombie.vehicles.PolygonalMap2.Vehicle;
import zombie.vehicles.PolygonalMap2.VehiclePoly;

final class PolygonalMap2$VehicleAddTask implements IVehicleTask {
   PolygonalMap2 map;
   BaseVehicle vehicle;
   final VehiclePoly poly = new VehiclePoly();
   final VehiclePoly polyPlusRadius = new VehiclePoly();
   final TFloatArrayList crawlOffsets = new TFloatArrayList();
   float upVectorDot;
   static final ArrayDeque<PolygonalMap2$VehicleAddTask> pool = new ArrayDeque<>();

   private PolygonalMap2$VehicleAddTask() {
   }

   public void init(PolygonalMap2 var1, BaseVehicle var2) {
      this.map = var1;
      this.vehicle = var2;
      this.poly.init(var2.getPoly());
      this.polyPlusRadius.init(var2.getPolyPlusRadius());
      this.crawlOffsets.resetQuick();
      this.crawlOffsets.addAll(var2.getScript().getCrawlOffsets());
      this.upVectorDot = var2.getUpVectorDot();
   }

   public void execute() {
      Vehicle var1 = Vehicle.alloc();
      var1.poly.init(this.poly);
      var1.polyPlusRadius.init(this.polyPlusRadius);
      var1.crawlOffsets.resetQuick();
      var1.crawlOffsets.addAll(this.crawlOffsets);
      var1.upVectorDot = this.upVectorDot;
      this.map.vehicles.add(var1);
      this.map.vehicleMap.put(this.vehicle, var1);
      this.vehicle = null;
   }

   static PolygonalMap2$VehicleAddTask alloc() {
      synchronized (pool) {
         return pool.isEmpty() ? new PolygonalMap2$VehicleAddTask() : pool.pop();
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
