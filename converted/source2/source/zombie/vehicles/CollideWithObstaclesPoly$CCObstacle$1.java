package zombie.vehicles;

import zombie.popman.ObjectPool;
import zombie.popman.ObjectPool.Allocator;
import zombie.vehicles.CollideWithObstaclesPoly.CCEdge;
import zombie.vehicles.CollideWithObstaclesPoly.CCEdgeRing;
import zombie.vehicles.CollideWithObstaclesPoly.CCObstacle;

class CollideWithObstaclesPoly$CCObstacle$1 extends ObjectPool<CCObstacle> {
   CollideWithObstaclesPoly$CCObstacle$1(Allocator var1) {
      super(var1);
   }

   public void release(CCObstacle var1) {
      CCEdge.releaseAll(var1.outer);
      CCEdgeRing.releaseAll(var1.inner);
      var1.outer.clear();
      var1.inner.clear();
      var1.vehicle = null;
      super.release(var1);
   }
}
