package zombie.vehicles;

import java.util.ArrayDeque;
import org.joml.Vector3f;

final class BaseVehicle$VehicleImpulse {
   static final ArrayDeque<BaseVehicle$VehicleImpulse> pool = new ArrayDeque<>();
   final Vector3f impulse = new Vector3f();
   final Vector3f rel_pos = new Vector3f();
   boolean enable = false;

   private BaseVehicle$VehicleImpulse() {
   }

   static BaseVehicle$VehicleImpulse alloc() {
      return pool.isEmpty() ? new BaseVehicle$VehicleImpulse() : pool.pop();
   }

   void release() {
      pool.push(this);
   }
}
