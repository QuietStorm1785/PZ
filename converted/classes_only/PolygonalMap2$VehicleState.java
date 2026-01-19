package zombie.vehicles;

import java.util.ArrayDeque;
import org.joml.Vector3f;
import zombie.vehicles.BaseVehicle.Vector3fObjectPool;
import zombie.vehicles.PolygonalMap2.VehiclePoly;

final class PolygonalMap2$VehicleState {
   BaseVehicle vehicle;
   float x;
   float y;
   float z;
   final Vector3f forward = new Vector3f();
   final VehiclePoly polyPlusRadius = new VehiclePoly();
   static final ArrayDeque<PolygonalMap2$VehicleState> pool = new ArrayDeque<>();

   private PolygonalMap2$VehicleState() {
   }

   PolygonalMap2$VehicleState init(BaseVehicle var1) {
      this.vehicle = var1;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      var1.getForwardVector(this.forward);
      this.polyPlusRadius.init(var1.getPolyPlusRadius());
      return this;
   }

   boolean check() {
      boolean var1 = this.x != this.vehicle.x || this.y != this.vehicle.y || (int)this.z != (int)this.vehicle.z;
      if (!var1) {
         Vector3fObjectPool var2 = (Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get();
         Vector3f var3 = this.vehicle.getForwardVector((Vector3f)var2.alloc());
         var1 = this.forward.dot(var3) < 0.999F;
         if (var1) {
            this.forward.set(var3);
         }

         var2.release(var3);
      }

      if (var1) {
         this.x = this.vehicle.x;
         this.y = this.vehicle.y;
         this.z = this.vehicle.z;
      }

      return var1;
   }

   static PolygonalMap2$VehicleState alloc() {
      return pool.isEmpty() ? new PolygonalMap2$VehicleState() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
