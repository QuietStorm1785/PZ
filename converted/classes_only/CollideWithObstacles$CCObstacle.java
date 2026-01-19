package zombie.vehicles;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.iso.Vector2;
import zombie.vehicles.CollideWithObstacles.CCEdge;
import zombie.vehicles.CollideWithObstacles.CCNode;
import zombie.vehicles.CollideWithObstacles.EdgeRingHit;
import zombie.vehicles.CollideWithObstacles.ImmutableRectF;

final class CollideWithObstacles$CCObstacle {
   final ArrayList<CCEdge> edges = new ArrayList<>();
   ImmutableRectF bounds;
   static ArrayDeque<CollideWithObstacles$CCObstacle> pool = new ArrayDeque<>();

   private CollideWithObstacles$CCObstacle() {
   }

   CollideWithObstacles$CCObstacle init() {
      this.edges.clear();
      return this;
   }

   boolean hasNode(CCNode var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
         CCEdge var3 = this.edges.get(var2);
         if (var3.hasNode(var1)) {
            return true;
         }
      }

      return false;
   }

   boolean hasAdjacentNodes(CCNode var1, CCNode var2) {
      for (int var3 = 0; var3 < this.edges.size(); var3++) {
         CCEdge var4 = this.edges.get(var3);
         if (var4.hasNode(var1) && var4.hasNode(var2)) {
            return true;
         }
      }

      return false;
   }

   boolean isPointInPolygon_CrossingNumber(float var1, float var2) {
      int var3 = 0;

      for (int var4 = 0; var4 < this.edges.size(); var4++) {
         CCEdge var5 = this.edges.get(var4);
         if (var5.node1.y <= var2 && var5.node2.y > var2 || var5.node1.y > var2 && var5.node2.y <= var2) {
            float var6 = (var2 - var5.node1.y) / (var5.node2.y - var5.node1.y);
            if (var1 < var5.node1.x + var6 * (var5.node2.x - var5.node1.x)) {
               var3++;
            }
         }
      }

      return var3 % 2 == 1;
   }

   float isLeft(float var1, float var2, float var3, float var4, float var5, float var6) {
      return (var3 - var1) * (var6 - var2) - (var5 - var1) * (var4 - var2);
   }

   EdgeRingHit isPointInPolygon_WindingNumber(float var1, float var2, int var3) {
      int var4 = 0;

      for (int var5 = 0; var5 < this.edges.size(); var5++) {
         CCEdge var6 = this.edges.get(var5);
         if ((var3 & 16) != 0 && var6.isPointOn(var1, var2)) {
            return EdgeRingHit.OnEdge;
         }

         if (var6.node1.y <= var2) {
            if (var6.node2.y > var2 && this.isLeft(var6.node1.x, var6.node1.y, var6.node2.x, var6.node2.y, var1, var2) > 0.0F) {
               var4++;
            }
         } else if (var6.node2.y <= var2 && this.isLeft(var6.node1.x, var6.node1.y, var6.node2.x, var6.node2.y, var1, var2) < 0.0F) {
            var4--;
         }
      }

      return var4 == 0 ? EdgeRingHit.Outside : EdgeRingHit.Inside;
   }

   boolean isPointInside(float var1, float var2, int var3) {
      return this.isPointInPolygon_WindingNumber(var1, var2, var3) == EdgeRingHit.Inside;
   }

   boolean isNodeInsideOf(CCNode var1) {
      if (this.hasNode(var1)) {
         return false;
      } else if (!this.bounds.containsPoint(var1.x, var1.y)) {
         return false;
      } else {
         byte var2 = 0;
         return this.isPointInside(var1.x, var1.y, var2);
      }
   }

   CCNode getClosestPointOnEdge(float var1, float var2, Vector2 var3) {
      double var4 = Double.MAX_VALUE;
      CCNode var6 = null;
      float var7 = Float.MAX_VALUE;
      float var8 = Float.MAX_VALUE;

      for (int var9 = 0; var9 < this.edges.size(); var9++) {
         CCEdge var10 = this.edges.get(var9);
         if (var10.node1.visible.contains(var10.node2)) {
            CCNode var11 = var10.closestPoint(var1, var2, var3);
            double var12 = (var1 - var3.x) * (var1 - var3.x) + (var2 - var3.y) * (var2 - var3.y);
            if (var12 < var4) {
               var7 = var3.x;
               var8 = var3.y;
               var6 = var11;
               var4 = var12;
            }
         }
      }

      var3.set(var7, var8);
      return var6;
   }

   void calcBounds() {
      float var1 = Float.MAX_VALUE;
      float var2 = Float.MAX_VALUE;
      float var3 = Float.MIN_VALUE;
      float var4 = Float.MIN_VALUE;

      for (int var5 = 0; var5 < this.edges.size(); var5++) {
         CCEdge var6 = this.edges.get(var5);
         var1 = Math.min(var1, var6.node1.x);
         var2 = Math.min(var2, var6.node1.y);
         var3 = Math.max(var3, var6.node1.x);
         var4 = Math.max(var4, var6.node1.y);
      }

      if (this.bounds != null) {
         this.bounds.release();
      }

      float var7 = 0.01F;
      this.bounds = ImmutableRectF.alloc().init(var1 - var7, var2 - var7, var3 - var1 + var7 * 2.0F, var4 - var2 + var7 * 2.0F);
   }

   static CollideWithObstacles$CCObstacle alloc() {
      return pool.isEmpty() ? new CollideWithObstacles$CCObstacle() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
