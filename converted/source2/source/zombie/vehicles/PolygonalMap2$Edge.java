package zombie.vehicles;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.iso.Vector2;
import zombie.vehicles.PolygonalMap2.ClosestPointOnEdge;
import zombie.vehicles.PolygonalMap2.EdgeRing;
import zombie.vehicles.PolygonalMap2.Intersection;
import zombie.vehicles.PolygonalMap2.Node;
import zombie.vehicles.PolygonalMap2.Obstacle;

final class PolygonalMap2$Edge {
   Node node1;
   Node node2;
   Obstacle obstacle;
   EdgeRing edgeRing;
   final ArrayList<Intersection> intersections = new ArrayList<>();
   final Vector2 normal = new Vector2();
   static final ArrayDeque<PolygonalMap2$Edge> pool = new ArrayDeque<>();

   private PolygonalMap2$Edge() {
   }

   PolygonalMap2$Edge init(Node var1, Node var2, Obstacle var3, EdgeRing var4) {
      if (var1 == null) {
         boolean var5 = true;
      }

      this.node1 = var1;
      this.node2 = var2;
      var1.edges.add(this);
      var2.edges.add(this);
      this.obstacle = var3;
      this.edgeRing = var4;
      this.intersections.clear();
      this.normal.set(var2.x - var1.x, var2.y - var1.y);
      this.normal.normalize();
      this.normal.rotate((float) (Math.PI / 2));
      return this;
   }

   boolean hasNode(Node var1) {
      return var1 == this.node1 || var1 == this.node2;
   }

   void getClosestPointOnEdge(float var1, float var2, ClosestPointOnEdge var3) {
      if (this.node1.isConnectedTo(this.node2)) {
         float var4 = this.node1.x;
         float var5 = this.node1.y;
         float var6 = this.node2.x;
         float var7 = this.node2.y;
         double var8 = ((var1 - var4) * (var6 - var4) + (var2 - var5) * (var7 - var5)) / (Math.pow(var6 - var4, 2.0) + Math.pow(var7 - var5, 2.0));
         double var10 = var4 + var8 * (var6 - var4);
         double var12 = var5 + var8 * (var7 - var5);
         Node var14 = null;
         if (var8 <= 0.0) {
            var10 = var4;
            var12 = var5;
            var14 = this.node1;
         } else if (var8 >= 1.0) {
            var10 = var6;
            var12 = var7;
            var14 = this.node2;
         }

         double var15 = (var1 - var10) * (var1 - var10) + (var2 - var12) * (var2 - var12);
         if (var15 < var3.distSq) {
            var3.point.set((float)var10, (float)var12);
            var3.distSq = var15;
            var3.edge = this;
            var3.node = var14;
         }
      }
   }

   boolean isPointOn(float var1, float var2) {
      if (!this.node1.isConnectedTo(this.node2)) {
         return false;
      } else {
         float var3 = this.node1.x;
         float var4 = this.node1.y;
         float var5 = this.node2.x;
         float var6 = this.node2.y;
         double var7 = ((var1 - var3) * (var5 - var3) + (var2 - var4) * (var6 - var4)) / (Math.pow(var5 - var3, 2.0) + Math.pow(var6 - var4, 2.0));
         double var9 = var3 + var7 * (var5 - var3);
         double var11 = var4 + var7 * (var6 - var4);
         if (var7 <= 0.0) {
            var9 = var3;
            var11 = var4;
         } else if (var7 >= 1.0) {
            var9 = var5;
            var11 = var6;
         }

         double var13 = (var1 - var9) * (var1 - var9) + (var2 - var11) * (var2 - var11);
         return var13 < 1.0E-6;
      }
   }

   PolygonalMap2$Edge split(Node var1) {
      PolygonalMap2$Edge var2 = alloc().init(var1, this.node2, this.obstacle, this.edgeRing);
      this.edgeRing.add(this.edgeRing.indexOf(this) + 1, var2);
      PolygonalMap2.instance.breakConnection(this.node1, this.node2);
      this.node2.edges.remove(this);
      this.node2 = var1;
      this.node2.edges.add(this);
      return var2;
   }

   static PolygonalMap2$Edge alloc() {
      return pool.isEmpty() ? new PolygonalMap2$Edge() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         this.node1 = null;
         this.node2 = null;
         this.obstacle = null;
         this.edgeRing = null;
         this.intersections.clear();
         pool.push(this);
      }
   }

   static void releaseAll(ArrayList<PolygonalMap2$Edge> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         ((PolygonalMap2$Edge)var0.get(var1)).release();
      }
   }
}
