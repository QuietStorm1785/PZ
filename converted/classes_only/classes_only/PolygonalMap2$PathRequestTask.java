package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.vehicles.PolygonalMap2.PathFindRequest;

final class PolygonalMap2$PathRequestTask {
   PolygonalMap2 map;
   PathFindRequest request;
   static final ArrayDeque<PolygonalMap2$PathRequestTask> pool = new ArrayDeque<>();

   private PolygonalMap2$PathRequestTask() {
   }

   PolygonalMap2$PathRequestTask init(PolygonalMap2 var1, PathFindRequest var2) {
      this.map = var1;
      this.request = var2;
      return this;
   }

   void execute() {
      if (this.request.mover instanceof IsoPlayer) {
         this.map.requests.playerQ.add(this.request);
      } else if (this.request.mover instanceof IsoZombie && ((IsoZombie)this.request.mover).target != null) {
         this.map.requests.aggroZombieQ.add(this.request);
      } else {
         this.map.requests.otherQ.add(this.request);
      }
   }

   static PolygonalMap2$PathRequestTask alloc() {
      synchronized (pool) {
         return pool.isEmpty() ? new PolygonalMap2$PathRequestTask() : pool.pop();
      }
   }

   public void release() {
      synchronized (pool) {
         if (!$assertionsDisabled && pool.contains(this)) {
            throw new AssertionError();
         } else {
            pool.push(this);
         }
      }
   }
}
