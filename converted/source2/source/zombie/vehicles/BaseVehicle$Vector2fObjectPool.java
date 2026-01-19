package zombie.vehicles;

import org.joml.Vector2f;
import zombie.popman.ObjectPool;

public final class BaseVehicle$Vector2fObjectPool extends ObjectPool<Vector2f> {
   int allocated = 0;

   BaseVehicle$Vector2fObjectPool() {
      super(Vector2f::new);
   }

   protected Vector2f makeObject() {
      this.allocated++;
      return (Vector2f)super.makeObject();
   }
}
