package zombie.vehicles;

import java.util.ArrayDeque;
import java.util.ArrayList;
import org.joml.Vector3f;
import zombie.debug.LineDrawer;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoUtils;
import zombie.vehicles.PolygonalMap2.AdjustStartEndNodeData;
import zombie.vehicles.PolygonalMap2.ClosestPointOnEdge;
import zombie.vehicles.PolygonalMap2.Edge;
import zombie.vehicles.PolygonalMap2.EdgeRing;
import zombie.vehicles.PolygonalMap2.EdgeRingHit;
import zombie.vehicles.PolygonalMap2.ImmutableRectF;
import zombie.vehicles.PolygonalMap2.Node;
import zombie.vehicles.PolygonalMap2.Vehicle;
import zombie.vehicles.PolygonalMap2.VisibilityGraph;

final class PolygonalMap2$Obstacle {
   Vehicle vehicle;
   final EdgeRing outer = new EdgeRing();
   final ArrayList<EdgeRing> inner = new ArrayList<>();
   ImmutableRectF bounds;
   Node nodeCrawlFront;
   Node nodeCrawlRear;
   final ArrayList<Node> crawlNodes = new ArrayList<>();
   static final ArrayDeque<PolygonalMap2$Obstacle> pool = new ArrayDeque<>();

   private PolygonalMap2$Obstacle() {
   }

   PolygonalMap2$Obstacle init(Vehicle var1) {
      this.vehicle = var1;
      this.outer.clear();
      this.inner.clear();
      this.nodeCrawlFront = this.nodeCrawlRear = null;
      this.crawlNodes.clear();
      return this;
   }

   PolygonalMap2$Obstacle init(IsoGridSquare var1) {
      this.vehicle = null;
      this.outer.clear();
      this.inner.clear();
      this.nodeCrawlFront = this.nodeCrawlRear = null;
      this.crawlNodes.clear();
      return this;
   }

   boolean hasNode(Node var1) {
      if (this.outer.hasNode(var1)) {
         return true;
      } else {
         for (int var2 = 0; var2 < this.inner.size(); var2++) {
            EdgeRing var3 = this.inner.get(var2);
            if (var3.hasNode(var1)) {
               return true;
            }
         }

         return false;
      }
   }

   boolean hasAdjacentNodes(Node var1, Node var2) {
      if (this.outer.hasAdjacentNodes(var1, var2)) {
         return true;
      } else {
         for (int var3 = 0; var3 < this.inner.size(); var3++) {
            EdgeRing var4 = this.inner.get(var3);
            if (var4.hasAdjacentNodes(var1, var2)) {
               return true;
            }
         }

         return false;
      }
   }

   boolean isPointInside(float var1, float var2, int var3) {
      if (this.outer.isPointInPolygon_WindingNumber(var1, var2, var3) != EdgeRingHit.Inside) {
         return false;
      } else if (this.inner.isEmpty()) {
         return true;
      } else {
         for (int var4 = 0; var4 < this.inner.size(); var4++) {
            EdgeRing var5 = this.inner.get(var4);
            if (var5.isPointInPolygon_WindingNumber(var1, var2, var3) != EdgeRingHit.Outside) {
               return false;
            }
         }

         return true;
      }
   }

   boolean isPointInside(float var1, float var2) {
      byte var3 = 0;
      return this.isPointInside(var1, var2, var3);
   }

   boolean lineSegmentIntersects(float var1, float var2, float var3, float var4) {
      if (this.outer.lineSegmentIntersects(var1, var2, var3, var4)) {
         return true;
      } else {
         for (int var5 = 0; var5 < this.inner.size(); var5++) {
            EdgeRing var6 = this.inner.get(var5);
            if (var6.lineSegmentIntersects(var1, var2, var3, var4)) {
               return true;
            }
         }

         return false;
      }
   }

   boolean isNodeInsideOf(Node var1) {
      if (this.hasNode(var1)) {
         return false;
      } else {
         return !this.bounds.containsPoint(var1.x, var1.y) ? false : this.isPointInside(var1.x, var1.y);
      }
   }

   void getClosestPointOnEdge(float var1, float var2, ClosestPointOnEdge var3) {
      var3.edge = null;
      var3.node = null;
      var3.distSq = Double.MAX_VALUE;
      this.outer.getClosestPointOnEdge(var1, var2, var3);

      for (int var4 = 0; var4 < this.inner.size(); var4++) {
         EdgeRing var5 = this.inner.get(var4);
         var5.getClosestPointOnEdge(var1, var2, var3);
      }
   }

   boolean splitEdgeAtNearestPoint(ClosestPointOnEdge var1, int var2, AdjustStartEndNodeData var3) {
      if (var1.edge == null) {
         return false;
      } else {
         var3.obstacle = this;
         if (var1.node == null) {
            var3.node = Node.alloc().init(var1.point.x, var1.point.y, var2);
            var3.newEdge = var1.edge.split(var3.node);
            var3.isNodeNew = true;
         } else {
            var3.node = var1.node;
            var3.newEdge = null;
            var3.isNodeNew = false;
         }

         return true;
      }
   }

   void unsplit(Node var1, ArrayList<Edge> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
         Edge var4 = (Edge)var2.get(var3);
         if (var4.node1 == var1) {
            if (var3 > 0) {
               Edge var5 = (Edge)var2.get(var3 - 1);
               var5.node2 = var4.node2;
               if (!$assertionsDisabled && !var4.node2.edges.contains(var4)) {
                  throw new AssertionError();
               }

               var4.node2.edges.remove(var4);
               if (!$assertionsDisabled && var4.node2.edges.contains(var5)) {
                  throw new AssertionError();
               }

               var4.node2.edges.add(var5);
               PolygonalMap2.instance.connectTwoNodes(var5.node1, var5.node2);
            } else {
               ((Edge)var2.get(var3 + 1)).node1 = ((Edge)var2.get(var2.size() - 1)).node2;
            }

            var4.release();
            var2.remove(var3);
            break;
         }
      }
   }

   void calcBounds() {
      float var1 = Float.MAX_VALUE;
      float var2 = Float.MAX_VALUE;
      float var3 = Float.MIN_VALUE;
      float var4 = Float.MIN_VALUE;

      for (int var5 = 0; var5 < this.outer.size(); var5++) {
         Edge var6 = (Edge)this.outer.get(var5);
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

   void render(ArrayList<Edge> var1, boolean var2) {
      if (!var1.isEmpty()) {
         float var3 = 0.0F;
         float var4 = var2 ? 1.0F : 0.5F;
         float var5 = var2 ? 0.0F : 0.5F;

         for (Edge var7 : var1) {
            Node var8 = var7.node1;
            Node var9 = var7.node2;
            LineDrawer.addLine(var8.x, var8.y, var8.z, var9.x, var9.y, var9.z, var3, var4, var5, null, true);
            Vector3f var10 = new Vector3f(var9.x - var8.x, var9.y - var8.y, var9.z - var8.z).normalize();
            Vector3f var11 = new Vector3f(var10).cross(0.0F, 0.0F, 1.0F).normalize();
            var10.mul(0.9F);
            LineDrawer.addLine(
               var9.x - var10.x * 0.1F - var11.x * 0.1F, var9.y - var10.y * 0.1F - var11.y * 0.1F, var9.z, var9.x, var9.y, var9.z, var3, var4, var5, null, true
            );
            LineDrawer.addLine(
               var9.x - var10.x * 0.1F + var11.x * 0.1F, var9.y - var10.y * 0.1F + var11.y * 0.1F, var9.z, var9.x, var9.y, var9.z, var3, var4, var5, null, true
            );
            var3 = 1.0F - var3;
         }

         Node var12 = ((Edge)var1.get(0)).node1;
         LineDrawer.addLine(var12.x - 0.1F, var12.y - 0.1F, var12.z, var12.x + 0.1F, var12.y + 0.1F, var12.z, 1.0F, 0.0F, 0.0F, null, false);
      }
   }

   void render() {
      this.render(this.outer, true);

      for (int var1 = 0; var1 < this.inner.size(); var1++) {
         this.render((ArrayList<Edge>)this.inner.get(var1), false);
      }
   }

   void connectCrawlNodes(VisibilityGraph var1, PolygonalMap2$Obstacle var2) {
      this.connectCrawlNode(var1, var2, this.nodeCrawlFront, var2.nodeCrawlFront);
      this.connectCrawlNode(var1, var2, this.nodeCrawlFront, var2.nodeCrawlRear);
      this.connectCrawlNode(var1, var2, this.nodeCrawlRear, var2.nodeCrawlFront);
      this.connectCrawlNode(var1, var2, this.nodeCrawlRear, var2.nodeCrawlRear);

      for (byte var3 = 0; var3 < this.crawlNodes.size(); var3 += 3) {
         Node var4 = this.crawlNodes.get(var3);
         Node var5 = this.crawlNodes.get(var3 + 2);

         for (byte var6 = 0; var6 < var2.crawlNodes.size(); var6 += 3) {
            Node var7 = var2.crawlNodes.get(var6);
            Node var8 = var2.crawlNodes.get(var6 + 2);
            this.connectCrawlNode(var1, var2, var4, var7);
            this.connectCrawlNode(var1, var2, var4, var8);
            this.connectCrawlNode(var1, var2, var5, var7);
            this.connectCrawlNode(var1, var2, var5, var8);
         }
      }
   }

   void connectCrawlNode(VisibilityGraph var1, PolygonalMap2$Obstacle var2, Node var3, Node var4) {
      if (this.isNodeInsideOf(var4)) {
         var4.flags |= 2;
         var3 = this.getClosestInteriorCrawlNode(var4.x, var4.y);
         if (var3 != null) {
            if (!var3.isConnectedTo(var4)) {
               PolygonalMap2.instance.connectTwoNodes(var3, var4);
            }
         }
      } else if (!var3.ignore && !var4.ignore) {
         if (!var3.isConnectedTo(var4)) {
            if (var1.isVisible(var3, var4)) {
               PolygonalMap2.instance.connectTwoNodes(var3, var4);
            }
         }
      }
   }

   Node getClosestInteriorCrawlNode(float var1, float var2) {
      Node var3 = null;
      float var4 = Float.MAX_VALUE;

      for (byte var5 = 0; var5 < this.crawlNodes.size(); var5 += 3) {
         Node var6 = this.crawlNodes.get(var5 + 1);
         float var7 = IsoUtils.DistanceToSquared(var6.x, var6.y, var1, var2);
         if (var7 < var4) {
            var3 = var6;
            var4 = var7;
         }
      }

      return var3;
   }

   static PolygonalMap2$Obstacle alloc() {
      return pool.isEmpty() ? new PolygonalMap2$Obstacle() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         this.outer.release();
         this.outer.clear();
         EdgeRing.releaseAll(this.inner);
         this.inner.clear();
         pool.push(this);
      }
   }

   static void releaseAll(ArrayList<PolygonalMap2$Obstacle> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         ((PolygonalMap2$Obstacle)var0.get(var1)).release();
      }
   }
}
