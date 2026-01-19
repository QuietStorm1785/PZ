package zombie.vehicles;

import org.joml.Vector3f;
import zombie.popman.ObjectPool;

public final class BaseVehicle$Vector3fObjectPool extends ObjectPool<Vector3f> {
   int allocated = 0;

   BaseVehicle$Vector3fObjectPool() {
      super(Vector3f::new);
   }

   protected Vector3f makeObject() {
      this.allocated++;
      return (Vector3f)super.makeObject();
   }
}
