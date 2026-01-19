package zombie.vehicles;

import org.joml.Quaternionf;
import zombie.popman.ObjectPool;

public final class BaseVehicle$QuaternionfObjectPool extends ObjectPool<Quaternionf> {
   int allocated = 0;

   BaseVehicle$QuaternionfObjectPool() {
      super(Quaternionf::new);
   }

   protected Quaternionf makeObject() {
      this.allocated++;
      return (Quaternionf)super.makeObject();
   }
}
