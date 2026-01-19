package zombie.vehicles;

import zombie.popman.ObjectPool;
import zombie.vehicles.UI3DScene.Ray;

public final class UI3DScene$RayObjectPool extends ObjectPool<Ray> {
   int allocated = 0;

   public UI3DScene$RayObjectPool() {
      super(Ray::new);
   }

   protected Ray makeObject() {
      this.allocated++;
      return (Ray)super.makeObject();
   }
}
