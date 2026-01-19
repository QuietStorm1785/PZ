package zombie.vehicles;

import org.joml.Matrix4f;
import zombie.popman.ObjectPool;

public final class BaseVehicle$Matrix4fObjectPool extends ObjectPool<Matrix4f> {
   int allocated = 0;

   BaseVehicle$Matrix4fObjectPool() {
      super(Matrix4f::new);
   }

   protected Matrix4f makeObject() {
      this.allocated++;
      return (Matrix4f)super.makeObject();
   }
}
