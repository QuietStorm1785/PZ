package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.CollideWithObstacles.CCEdge;
import zombie.vehicles.CollideWithObstacles.CCNode;

final class CollideWithObstacles$CCIntersection {
   CCEdge edge1;
   CCEdge edge2;
   float dist1;
   float dist2;
   CCNode nodeSplit;
   static ArrayDeque<CollideWithObstacles$CCIntersection> pool = new ArrayDeque<>();

   private CollideWithObstacles$CCIntersection() {
   }

   CollideWithObstacles$CCIntersection init(CCEdge var1, CCEdge var2, float var3, float var4, float var5, float var6) {
      this.edge1 = var1;
      this.edge2 = var2;
      this.dist1 = var3;
      this.dist2 = var4;
      this.nodeSplit = CCNode.alloc().init(var5, var6, var1.node1.z);
      return this;
   }

   CollideWithObstacles$CCIntersection init(CCEdge var1, CCEdge var2, float var3, float var4, CCNode var5) {
      this.edge1 = var1;
      this.edge2 = var2;
      this.dist1 = var3;
      this.dist2 = var4;
      this.nodeSplit = var5;
      return this;
   }

   CCEdge split(CCEdge var1) {
      if (var1.hasNode(this.nodeSplit)) {
         return null;
      } else if (var1.node1.x == this.nodeSplit.x && var1.node1.y == this.nodeSplit.y) {
         return null;
      } else {
         return var1.node2.x == this.nodeSplit.x && var1.node2.y == this.nodeSplit.y ? null : var1.split(this.nodeSplit);
      }
   }

   static CollideWithObstacles$CCIntersection alloc() {
      return pool.isEmpty() ? new CollideWithObstacles$CCIntersection() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
