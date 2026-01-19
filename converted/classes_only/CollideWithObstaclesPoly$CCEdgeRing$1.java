package zombie.vehicles;

import zombie.popman.ObjectPool;
import zombie.popman.ObjectPool.Allocator;
import zombie.vehicles.CollideWithObstaclesPoly.CCEdge;
import zombie.vehicles.CollideWithObstaclesPoly.CCEdgeRing;

class CollideWithObstaclesPoly$CCEdgeRing$1 extends ObjectPool<CCEdgeRing> {
   CollideWithObstaclesPoly$CCEdgeRing$1(Allocator var1) {
      super(var1);
   }

   public void release(CCEdgeRing var1) {
      CCEdge.releaseAll(var1);
      this.clear();
      super.release(var1);
   }
}
