package zombie.vehicles;

import zombie.iso.Vector2;
import zombie.popman.ObjectPool;

public final class BaseVehicle$Vector2ObjectPool extends ObjectPool<Vector2> {
   int allocated = 0;

   BaseVehicle$Vector2ObjectPool() {
      super(Vector2::new);
   }

   protected Vector2 makeObject() {
      this.allocated++;
      return (Vector2)super.makeObject();
   }
}
