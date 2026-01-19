package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.PathFindRequest;

final class PolygonalMap2$RequestQueue {
   final ArrayDeque<PathFindRequest> playerQ = new ArrayDeque<>();
   final ArrayDeque<PathFindRequest> aggroZombieQ = new ArrayDeque<>();
   final ArrayDeque<PathFindRequest> otherQ = new ArrayDeque<>();

   private PolygonalMap2$RequestQueue() {
   }

   boolean isEmpty() {
      return this.playerQ.isEmpty() && this.aggroZombieQ.isEmpty() && this.otherQ.isEmpty();
   }

   PathFindRequest removeFirst() {
      if (!this.playerQ.isEmpty()) {
         return this.playerQ.removeFirst();
      } else {
         return !this.aggroZombieQ.isEmpty() ? this.aggroZombieQ.removeFirst() : this.otherQ.removeFirst();
      }
   }

   PathFindRequest removeLast() {
      if (!this.otherQ.isEmpty()) {
         return this.otherQ.removeLast();
      } else {
         return !this.aggroZombieQ.isEmpty() ? this.aggroZombieQ.removeLast() : this.playerQ.removeLast();
      }
   }
}
