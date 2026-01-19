package zombie.vehicles;

import zombie.popman.ObjectPool;
import zombie.vehicles.UI3DScene.Plane;

public final class UI3DScene$PlaneObjectPool extends ObjectPool<Plane> {
   int allocated = 0;

   public UI3DScene$PlaneObjectPool() {
      super(Plane::new);
   }

   protected Plane makeObject() {
      this.allocated++;
      return (Plane)super.makeObject();
   }
}
