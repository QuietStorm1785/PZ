package zombie.vehicles;

import java.util.ArrayList;
import zombie.iso.Vector2;
import zombie.popman.ObjectPool;
import zombie.vehicles.CollideWithObstaclesPoly.CCEdge;

final class CollideWithObstaclesPoly$CCNode {
   float x;
   float y;
   int z;
   final ArrayList<CCEdge> edges = new ArrayList<>();
   static final ObjectPool<CollideWithObstaclesPoly$CCNode> pool = new ObjectPool(CollideWithObstaclesPoly$CCNode::new);

   private CollideWithObstaclesPoly$CCNode() {
   }

   CollideWithObstaclesPoly$CCNode init(float var1, float var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.edges.clear();
      return this;
   }

   CollideWithObstaclesPoly$CCNode setXY(float var1, float var2) {
      this.x = var1;
      this.y = var2;
      return this;
   }

   boolean getNormalAndEdgeVectors(Vector2 var1, Vector2 var2) {
      CCEdge var3 = null;
      CCEdge var4 = null;

      for (int var5 = 0; var5 < this.edges.size(); var5++) {
         CCEdge var6 = this.edges.get(var5);
         if (var3 == null) {
            var3 = var6;
         } else if (!var3.hasNode(var6.node1) || !var3.hasNode(var6.node2)) {
            var4 = var6;
         }
      }

      if (var3 != null && var4 != null) {
         float var7 = var3.normal.x + var4.normal.x;
         float var8 = var3.normal.y + var4.normal.y;
         var1.set(var7, var8);
         var1.normalize();
         if (var3.node1 == this) {
            var2.set(var3.node2.x - var3.node1.x, var3.node2.y - var3.node1.y);
         } else {
            var2.set(var3.node1.x - var3.node2.x, var3.node1.y - var3.node2.y);
         }

         var2.normalize();
         return true;
      } else {
         return false;
      }
   }

   static CollideWithObstaclesPoly$CCNode alloc() {
      return (CollideWithObstaclesPoly$CCNode)pool.alloc();
   }

   void release() {
      pool.release(this);
   }

   static void releaseAll(ArrayList<CollideWithObstaclesPoly$CCNode> var0) {
      pool.releaseAll(var0);
   }
}
