package zombie.vehicles;

import gnu.trove.list.array.TIntArrayList;
import java.awt.geom.Line2D;
import java.nio.ByteBuffer;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import org.joml.Vector2f;
import zombie.debug.DebugOptions;
import zombie.debug.LineDrawer;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoUtils;
import zombie.vehicles.BaseVehicle.Vector2fObjectPool;
import zombie.vehicles.PolygonalMap2.AdjustStartEndNodeData;
import zombie.vehicles.PolygonalMap2.ClosestPointOnEdge;
import zombie.vehicles.PolygonalMap2.ClusterOutline;
import zombie.vehicles.PolygonalMap2.ClusterOutlineGrid;
import zombie.vehicles.PolygonalMap2.Connection;
import zombie.vehicles.PolygonalMap2.Edge;
import zombie.vehicles.PolygonalMap2.EdgeRing;
import zombie.vehicles.PolygonalMap2.ImmutableRectF;
import zombie.vehicles.PolygonalMap2.Intersection;
import zombie.vehicles.PolygonalMap2.Node;
import zombie.vehicles.PolygonalMap2.ObjectOutline;
import zombie.vehicles.PolygonalMap2.Obstacle;
import zombie.vehicles.PolygonalMap2.Square;
import zombie.vehicles.PolygonalMap2.Vehicle;
import zombie.vehicles.PolygonalMap2.VehicleCluster;
import zombie.vehicles.PolygonalMap2.VehiclePoly;
import zombie.vehicles.PolygonalMap2.VehicleRect;
import zombie.vehicles.PolygonalMap2.VisibilityGraph.CompareIntersection;

final class PolygonalMap2$VisibilityGraph {
   boolean created;
   VehicleCluster cluster;
   final ArrayList<Node> nodes = new ArrayList<>();
   final ArrayList<Edge> edges = new ArrayList<>();
   final ArrayList<Obstacle> obstacles = new ArrayList<>();
   final ArrayList<Node> intersectNodes = new ArrayList<>();
   final ArrayList<Node> perimeterNodes = new ArrayList<>();
   final ArrayList<Edge> perimeterEdges = new ArrayList<>();
   final ArrayList<Node> obstacleTraceNodes = new ArrayList<>();
   final TIntArrayList splitXY = new TIntArrayList();
   static final CompareIntersection comparator = new CompareIntersection();
   private static final ClusterOutlineGrid clusterOutlineGrid = new ClusterOutlineGrid();
   private static final ArrayDeque<PolygonalMap2$VisibilityGraph> pool = new ArrayDeque<>();

   private PolygonalMap2$VisibilityGraph() {
   }

   PolygonalMap2$VisibilityGraph init(VehicleCluster var1) {
      this.created = false;
      this.cluster = var1;
      this.edges.clear();
      this.nodes.clear();
      this.obstacles.clear();
      this.intersectNodes.clear();
      this.perimeterEdges.clear();
      this.perimeterNodes.clear();
      return this;
   }

   void addEdgesForVehicle(Vehicle var1) {
      VehiclePoly var2 = var1.polyPlusRadius;
      int var3 = (int)var2.z;
      Node var4 = Node.alloc().init(var2.x1, var2.y1, var3);
      Node var5 = Node.alloc().init(var2.x2, var2.y2, var3);
      Node var6 = Node.alloc().init(var2.x3, var2.y3, var3);
      Node var7 = Node.alloc().init(var2.x4, var2.y4, var3);
      Obstacle var8 = Obstacle.alloc().init(var1);
      this.obstacles.add(var8);
      Edge var9 = Edge.alloc().init(var4, var5, var8, var8.outer);
      Edge var10 = Edge.alloc().init(var5, var6, var8, var8.outer);
      Edge var11 = Edge.alloc().init(var6, var7, var8, var8.outer);
      Edge var12 = Edge.alloc().init(var7, var4, var8, var8.outer);
      var8.outer.add(var9);
      var8.outer.add(var10);
      var8.outer.add(var11);
      var8.outer.add(var12);
      var8.calcBounds();
      this.nodes.add(var4);
      this.nodes.add(var5);
      this.nodes.add(var6);
      this.nodes.add(var7);
      this.edges.add(var9);
      this.edges.add(var10);
      this.edges.add(var11);
      this.edges.add(var12);
      if (!(var1.upVectorDot < 0.95F)) {
         var8.nodeCrawlFront = Node.alloc().init((var2.x1 + var2.x2) / 2.0F, (var2.y1 + var2.y2) / 2.0F, var3);
         var8.nodeCrawlRear = Node.alloc().init((var2.x3 + var2.x4) / 2.0F, (var2.y3 + var2.y4) / 2.0F, var3);
         var8.nodeCrawlFront.flags |= 1;
         var8.nodeCrawlRear.flags |= 1;
         this.nodes.add(var8.nodeCrawlFront);
         this.nodes.add(var8.nodeCrawlRear);
         Edge var13 = var9.split(var8.nodeCrawlFront);
         Edge var14 = var11.split(var8.nodeCrawlRear);
         this.edges.add(var13);
         this.edges.add(var14);
         Vector2fObjectPool var15 = (Vector2fObjectPool)BaseVehicle.TL_vector2f_pool.get();
         Vector2f var16 = (Vector2f)var15.alloc();
         Vector2f var17 = (Vector2f)var15.alloc();
         var8.crawlNodes.clear();

         for (int var18 = 0; var18 < var1.crawlOffsets.size(); var18++) {
            float var19 = var1.crawlOffsets.get(var18);
            var16.set(var6.x, var6.y);
            var17.set(var5.x, var5.y);
            var17.sub(var16).mul(var19).add(var16);
            Node var20 = Node.alloc().init(var17.x, var17.y, var3);
            var20.flags |= 1;
            var16.set(var7.x, var7.y);
            var17.set(var4.x, var4.y);
            var17.sub(var16).mul(var19).add(var16);
            Node var21 = Node.alloc().init(var17.x, var17.y, var3);
            var21.flags |= 1;
            Node var22 = Node.alloc().init((var20.x + var21.x) / 2.0F, (var20.y + var21.y) / 2.0F, var3);
            var22.flags |= 3;
            var8.crawlNodes.add(var20);
            var8.crawlNodes.add(var22);
            var8.crawlNodes.add(var21);
            this.nodes.add(var20);
            this.nodes.add(var22);
            this.nodes.add(var21);
            Edge var23 = var10.split(var20);
            var12 = var12.split(var21);
            this.edges.add(var23);
            this.edges.add(var12);
         }

         var15.release(var16);
         var15.release(var17);
      }
   }

   boolean isVisible(Node var1, Node var2) {
      if (var1.sharesEdge(var2)) {
         return !var1.onSameShapeButDoesNotShareAnEdge(var2);
      } else if (var1.sharesShape(var2)) {
         return false;
      } else {
         for (int var3 = 0; var3 < this.edges.size(); var3++) {
            Edge var4 = this.edges.get(var3);
            if (this.intersects(var1, var2, var4)) {
               return false;
            }
         }

         for (int var5 = 0; var5 < this.perimeterEdges.size(); var5++) {
            Edge var6 = this.perimeterEdges.get(var5);
            if (this.intersects(var1, var2, var6)) {
               return false;
            }
         }

         return true;
      }
   }

   boolean intersects(Node var1, Node var2, Edge var3) {
      return !var3.hasNode(var1) && !var3.hasNode(var2)
         ? Line2D.linesIntersect(var1.x, var1.y, var2.x, var2.y, var3.node1.x, var3.node1.y, var3.node2.x, var3.node2.y)
         : false;
   }

   public Intersection getIntersection(Edge var1, Edge var2) {
      float var3 = var1.node1.x;
      float var4 = var1.node1.y;
      float var5 = var1.node2.x;
      float var6 = var1.node2.y;
      float var7 = var2.node1.x;
      float var8 = var2.node1.y;
      float var9 = var2.node2.x;
      float var10 = var2.node2.y;
      double var11 = (var10 - var8) * (var5 - var3) - (var9 - var7) * (var6 - var4);
      if (var11 == 0.0) {
         return null;
      } else {
         double var13 = ((var9 - var7) * (var4 - var8) - (var10 - var8) * (var3 - var7)) / var11;
         double var15 = ((var5 - var3) * (var4 - var8) - (var6 - var4) * (var3 - var7)) / var11;
         if (var13 >= 0.0 && var13 <= 1.0 && var15 >= 0.0 && var15 <= 1.0) {
            float var17 = (float)(var3 + var13 * (var5 - var3));
            float var18 = (float)(var4 + var13 * (var6 - var4));
            return new Intersection(var1, var2, (float)var13, (float)var15, var17, var18);
         } else {
            return null;
         }
      }
   }

   @Deprecated
   void addWorldObstacles() {
      VehicleRect var1 = this.cluster.bounds();
      var1.x--;
      var1.y--;
      var1.w += 3;
      var1.h += 3;
      ObjectOutline[][] var2 = new ObjectOutline[var1.w][var1.h];
      int var3 = this.cluster.z;

      for (int var4 = var1.top(); var4 < var1.bottom() - 1; var4++) {
         for (int var5 = var1.left(); var5 < var1.right() - 1; var5++) {
            Square var6 = PolygonalMap2.instance.getSquare(var5, var4, var3);
            if (var6 != null && this.contains(var6, 1)) {
               if (var6.has(504) || var6.isReallySolid()) {
                  ObjectOutline.setSolid(var5 - var1.left(), var4 - var1.top(), var3, var2);
               }

               if (var6.has(2)) {
                  ObjectOutline.setWest(var5 - var1.left(), var4 - var1.top(), var3, var2);
               }

               if (var6.has(4)) {
                  ObjectOutline.setNorth(var5 - var1.left(), var4 - var1.top(), var3, var2);
               }

               if (var6.has(262144)) {
                  ObjectOutline.setWest(var5 - var1.left() + 1, var4 - var1.top(), var3, var2);
               }

               if (var6.has(524288)) {
                  ObjectOutline.setNorth(var5 - var1.left(), var4 - var1.top() + 1, var3, var2);
               }
            }
         }
      }

      for (int var12 = 0; var12 < var1.h; var12++) {
         for (int var14 = 0; var14 < var1.w; var14++) {
            ObjectOutline var16 = ObjectOutline.get(var14, var12, var3, var2);
            if (var16 != null && var16.nw && var16.nw_w && var16.nw_n) {
               var16.trace(var2, this.obstacleTraceNodes);
               if (!var16.nodes.isEmpty()) {
                  Obstacle var7 = Obstacle.alloc().init((IsoGridSquare)null);

                  for (int var8 = 0; var8 < var16.nodes.size() - 1; var8++) {
                     Node var9 = (Node)var16.nodes.get(var8);
                     Node var10 = (Node)var16.nodes.get(var8 + 1);
                     var9.x = var9.x + var1.left();
                     var9.y = var9.y + var1.top();
                     if (!this.contains(var9.x, var9.y, var9.z)) {
                        var9.ignore = true;
                     }

                     Edge var11 = Edge.alloc().init(var9, var10, var7, var7.outer);
                     var7.outer.add(var11);
                     this.nodes.add(var9);
                  }

                  var7.calcBounds();
                  this.obstacles.add(var7);
                  this.edges.addAll(var7.outer);
               }
            }
         }
      }

      for (int var13 = 0; var13 < var1.h; var13++) {
         for (int var15 = 0; var15 < var1.w; var15++) {
            if (var2[var15][var13] != null) {
               var2[var15][var13].release();
            }
         }
      }

      var1.release();
   }

   void addWorldObstaclesClipper() {
      VehicleRect var1 = this.cluster.bounds();
      var1.x--;
      var1.y--;
      var1.w += 2;
      var1.h += 2;
      if (PolygonalMap2.instance.clipperThread == null) {
         PolygonalMap2.instance.clipperThread = new Clipper();
      }

      Clipper var2 = PolygonalMap2.instance.clipperThread;
      var2.clear();
      int var3 = this.cluster.z;

      for (int var4 = var1.top(); var4 < var1.bottom(); var4++) {
         for (int var5 = var1.left(); var5 < var1.right(); var5++) {
            Square var6 = PolygonalMap2.instance.getSquare(var5, var4, var3);
            if (var6 != null && this.contains(var6, 1)) {
               if (var6.has(504) || var6.isReallySolid()) {
                  var2.addAABB(var5 - 0.3F, var4 - 0.3F, var5 + 1 + 0.3F, var4 + 1 + 0.3F);
               }

               if (var6.has(2)) {
                  var2.addAABB(var5 - 0.3F, var4 - 0.3F, var5 + 0.3F, var4 + 1 + 0.3F);
               }

               if (var6.has(4)) {
                  var2.addAABB(var5 - 0.3F, var4 - 0.3F, var5 + 1 + 0.3F, var4 + 0.3F);
               }
            }
         }
      }

      var1.release();
      ByteBuffer var10 = PolygonalMap2.instance.xyBufferThread;
      int var11 = var2.generatePolygons();

      for (int var12 = 0; var12 < var11; var12++) {
         var10.clear();
         var2.getPolygon(var12, var10);
         Obstacle var7 = Obstacle.alloc().init((IsoGridSquare)null);
         this.getEdgesFromBuffer(var10, var7, true, var3);
         short var8 = var10.getShort();

         for (int var9 = 0; var9 < var8; var9++) {
            this.getEdgesFromBuffer(var10, var7, false, var3);
         }

         var7.calcBounds();
         this.obstacles.add(var7);
         this.edges.addAll(var7.outer);

         for (int var13 = 0; var13 < var7.inner.size(); var13++) {
            this.edges.addAll((Collection<? extends Edge>)var7.inner.get(var13));
         }
      }
   }

   void getEdgesFromBuffer(ByteBuffer var1, Obstacle var2, boolean var3, int var4) {
      short var5 = var1.getShort();
      if (var5 < 3) {
         var1.position(var1.position() + var5 * 4 * 2);
      } else {
         EdgeRing var6 = var2.outer;
         if (!var3) {
            var6 = EdgeRing.alloc();
            var6.clear();
            var2.inner.add(var6);
         }

         int var7 = this.nodes.size();

         for (int var8 = var5 - 1; var8 >= 0; var8--) {
            float var9 = var1.getFloat();
            float var10 = var1.getFloat();
            Node var11 = Node.alloc().init(var9, var10, var4);
            this.nodes.add(var11);
         }

         for (int var12 = var7; var12 < this.nodes.size() - 1; var12++) {
            Node var14 = this.nodes.get(var12);
            Node var16 = this.nodes.get(var12 + 1);
            if (!this.contains(var14.x, var14.y, var14.z)) {
               var14.ignore = true;
            }

            Edge var18 = Edge.alloc().init(var14, var16, var2, var6);
            var6.add(var18);
         }

         Node var13 = this.nodes.get(this.nodes.size() - 1);
         Node var15 = this.nodes.get(var7);
         Edge var17 = Edge.alloc().init(var13, var15, var2, var6);
         var6.add(var17);
      }
   }

   void trySplit(Edge var1, VehicleRect var2, TIntArrayList var3) {
      if (Math.abs(var1.node1.x - var1.node2.x) > Math.abs(var1.node1.y - var1.node2.y)) {
         float var4 = Math.min(var1.node1.x, var1.node2.x);
         float var5 = Math.max(var1.node1.x, var1.node2.x);
         float var6 = var1.node1.y;
         if (var2.left() > var4
            && var2.left() < var5
            && var2.top() < var6
            && var2.bottom() > var6
            && !var3.contains(var2.left())
            && !this.contains(var2.left() - 0.5F, var6, this.cluster.z)) {
            var3.add(var2.left());
         }

         if (var2.right() > var4
            && var2.right() < var5
            && var2.top() < var6
            && var2.bottom() > var6
            && !var3.contains(var2.right())
            && !this.contains(var2.right() + 0.5F, var6, this.cluster.z)) {
            var3.add(var2.right());
         }
      } else {
         float var7 = Math.min(var1.node1.y, var1.node2.y);
         float var8 = Math.max(var1.node1.y, var1.node2.y);
         float var9 = var1.node1.x;
         if (var2.top() > var7
            && var2.top() < var8
            && var2.left() < var9
            && var2.right() > var9
            && !var3.contains(var2.top())
            && !this.contains(var9, var2.top() - 0.5F, this.cluster.z)) {
            var3.add(var2.top());
         }

         if (var2.bottom() > var7
            && var2.bottom() < var8
            && var2.left() < var9
            && var2.right() > var9
            && !var3.contains(var2.bottom())
            && !this.contains(var9, var2.bottom() + 0.5F, this.cluster.z)) {
            var3.add(var2.bottom());
         }
      }
   }

   void splitWorldObstacleEdges(EdgeRing var1) {
      for (int var2 = var1.size() - 1; var2 >= 0; var2--) {
         Edge var3 = (Edge)var1.get(var2);
         this.splitXY.clear();

         for (int var4 = 0; var4 < this.cluster.rects.size(); var4++) {
            VehicleRect var5 = (VehicleRect)this.cluster.rects.get(var4);
            this.trySplit(var3, var5, this.splitXY);
         }

         if (!this.splitXY.isEmpty()) {
            this.splitXY.sort();
            if (Math.abs(var3.node1.x - var3.node2.x) > Math.abs(var3.node1.y - var3.node2.y)) {
               if (var3.node1.x < var3.node2.x) {
                  for (int var10 = this.splitXY.size() - 1; var10 >= 0; var10--) {
                     Node var14 = Node.alloc().init(this.splitXY.get(var10), var3.node1.y, this.cluster.z);
                     Edge var17 = var3.split(var14);
                     this.nodes.add(var14);
                     this.edges.add(var17);
                  }
               } else {
                  for (int var9 = 0; var9 < this.splitXY.size(); var9++) {
                     Node var13 = Node.alloc().init(this.splitXY.get(var9), var3.node1.y, this.cluster.z);
                     Edge var16 = var3.split(var13);
                     this.nodes.add(var13);
                     this.edges.add(var16);
                  }
               }
            } else if (var3.node1.y < var3.node2.y) {
               for (int var8 = this.splitXY.size() - 1; var8 >= 0; var8--) {
                  Node var12 = Node.alloc().init(var3.node1.x, this.splitXY.get(var8), this.cluster.z);
                  Edge var15 = var3.split(var12);
                  this.nodes.add(var12);
                  this.edges.add(var15);
               }
            } else {
               for (int var7 = 0; var7 < this.splitXY.size(); var7++) {
                  Node var11 = Node.alloc().init(var3.node1.x, this.splitXY.get(var7), this.cluster.z);
                  Edge var6 = var3.split(var11);
                  this.nodes.add(var11);
                  this.edges.add(var6);
               }
            }
         }
      }
   }

   void getStairSquares(ArrayList<Square> var1) {
      VehicleRect var2 = this.cluster.bounds();
      var2.x -= 4;
      var2.w += 4;
      var2.w++;
      var2.y -= 4;
      var2.h += 4;
      var2.h++;

      for (int var3 = var2.top(); var3 < var2.bottom(); var3++) {
         for (int var4 = var2.left(); var4 < var2.right(); var4++) {
            Square var5 = PolygonalMap2.instance.getSquare(var4, var3, this.cluster.z);
            if (var5 != null && var5.has(72) && !var1.contains(var5)) {
               var1.add(var5);
            }
         }
      }

      var2.release();
   }

   void getCanPathSquares(ArrayList<Square> var1) {
      VehicleRect var2 = this.cluster.bounds();
      var2.x--;
      var2.w += 2;
      var2.y--;
      var2.h += 2;

      for (int var3 = var2.top(); var3 < var2.bottom(); var3++) {
         for (int var4 = var2.left(); var4 < var2.right(); var4++) {
            Square var5 = PolygonalMap2.instance.getSquare(var4, var3, this.cluster.z);
            if (var5 != null && (var5.isCanPathW() || var5.isCanPathN()) && !var1.contains(var5)) {
               var1.add(var5);
            }
         }
      }

      var2.release();
   }

   void connectVehicleCrawlNodes() {
      for (int var1 = 0; var1 < this.obstacles.size(); var1++) {
         Obstacle var2 = this.obstacles.get(var1);
         if (var2.vehicle != null && var2.nodeCrawlFront != null) {
            for (byte var3 = 0; var3 < var2.crawlNodes.size(); var3 += 3) {
               Node var4 = (Node)var2.crawlNodes.get(var3);
               Node var5 = (Node)var2.crawlNodes.get(var3 + 1);
               Node var6 = (Node)var2.crawlNodes.get(var3 + 2);
               PolygonalMap2.instance.connectTwoNodes(var4, var5);
               PolygonalMap2.instance.connectTwoNodes(var6, var5);
               if (var3 + 3 < var2.crawlNodes.size()) {
                  Node var7 = (Node)var2.crawlNodes.get(var3 + 3 + 1);
                  PolygonalMap2.instance.connectTwoNodes(var5, var7);
               }
            }

            if (!var2.crawlNodes.isEmpty()) {
               int var37 = var2.crawlNodes.size() - 2;
               Node var41 = (Node)var2.crawlNodes.get(var37);
               PolygonalMap2.instance.connectTwoNodes(var2.nodeCrawlFront, var41);
               byte var38 = 1;
               var41 = (Node)var2.crawlNodes.get(var38);
               PolygonalMap2.instance.connectTwoNodes(var2.nodeCrawlRear, var41);
            }

            if (!var2.crawlNodes.isEmpty()) {
               ImmutableRectF var39 = var2.bounds;
               int var43 = (int)var39.x;
               int var45 = (int)var39.y;
               int var46 = (int)Math.ceil(var39.right());
               int var47 = (int)Math.ceil(var39.bottom());

               for (int var8 = var45; var8 < var47; var8++) {
                  for (int var9 = var43; var9 < var46; var9++) {
                     Square var10 = PolygonalMap2.instance.getSquare(var9, var8, this.cluster.z);
                     if (var10 != null && var2.isPointInside(var9 + 0.5F, var8 + 0.5F)) {
                        Node var11 = PolygonalMap2.instance.getNodeForSquare(var10);

                        for (int var12 = var11.visible.size() - 1; var12 >= 0; var12--) {
                           Connection var13 = (Connection)var11.visible.get(var12);
                           if (var13.has(1)) {
                              Node var14 = var13.otherNode(var11);
                              Node var15 = var2.getClosestInteriorCrawlNode(var11.x, var11.y);

                              for (int var16 = 0; var16 < var2.outer.size(); var16++) {
                                 Edge var17 = (Edge)var2.outer.get(var16);
                                 float var18 = var17.node1.x;
                                 float var19 = var17.node1.y;
                                 float var20 = var17.node2.x;
                                 float var21 = var17.node2.y;
                                 float var22 = var13.node1.x;
                                 float var23 = var13.node1.y;
                                 float var24 = var13.node2.x;
                                 float var25 = var13.node2.y;
                                 double var26 = (var25 - var23) * (var20 - var18) - (var24 - var22) * (var21 - var19);
                                 if (var26 != 0.0) {
                                    double var28 = ((var24 - var22) * (var19 - var23) - (var25 - var23) * (var18 - var22)) / var26;
                                    double var30 = ((var20 - var18) * (var19 - var23) - (var21 - var19) * (var18 - var22)) / var26;
                                    if (var28 >= 0.0 && var28 <= 1.0 && var30 >= 0.0 && var30 <= 1.0) {
                                       float var32 = (float)(var18 + var28 * (var20 - var18));
                                       float var33 = (float)(var19 + var28 * (var21 - var19));
                                       Node var34 = Node.alloc().init(var32, var33, this.cluster.z);
                                       var34.flags |= 1;
                                       boolean var35 = var17.node1.isConnectedTo(var17.node2);
                                       Edge var36 = var17.split(var34);
                                       if (var35) {
                                          PolygonalMap2.instance.connectTwoNodes(var17.node1, var17.node2);
                                          PolygonalMap2.instance.connectTwoNodes(var36.node1, var36.node2);
                                       }

                                       this.edges.add(var36);
                                       this.nodes.add(var34);
                                       PolygonalMap2.instance.connectTwoNodes(var14, var34, var13.flags & 2 | 1);
                                       PolygonalMap2.instance.connectTwoNodes(var34, var15, 0);
                                       break;
                                    }
                                 }
                              }

                              PolygonalMap2.instance.breakConnection(var13);
                           }
                        }
                     }
                  }
               }
            }

            for (int var40 = var1 + 1; var40 < this.obstacles.size(); var40++) {
               Obstacle var44 = this.obstacles.get(var40);
               if (var44.vehicle != null && var44.nodeCrawlFront != null) {
                  var2.connectCrawlNodes(this, var44);
                  var44.connectCrawlNodes(this, var2);
               }
            }
         }
      }
   }

   void checkEdgeIntersection() {
      for (int var1 = 0; var1 < this.obstacles.size(); var1++) {
         Obstacle var2 = this.obstacles.get(var1);

         for (int var3 = var1 + 1; var3 < this.obstacles.size(); var3++) {
            Obstacle var4 = this.obstacles.get(var3);
            if (var2.bounds.intersects(var4.bounds)) {
               this.checkEdgeIntersection(var2.outer, var4.outer);

               for (int var5 = 0; var5 < var4.inner.size(); var5++) {
                  EdgeRing var6 = (EdgeRing)var4.inner.get(var5);
                  this.checkEdgeIntersection(var2.outer, var6);
               }

               for (int var12 = 0; var12 < var2.inner.size(); var12++) {
                  EdgeRing var13 = (EdgeRing)var2.inner.get(var12);
                  this.checkEdgeIntersection(var13, var4.outer);

                  for (int var7 = 0; var7 < var4.inner.size(); var7++) {
                     EdgeRing var8 = (EdgeRing)var4.inner.get(var7);
                     this.checkEdgeIntersection(var13, var8);
                  }
               }
            }
         }
      }

      for (int var9 = 0; var9 < this.obstacles.size(); var9++) {
         Obstacle var10 = this.obstacles.get(var9);
         this.checkEdgeIntersectionSplit(var10.outer);

         for (int var11 = 0; var11 < var10.inner.size(); var11++) {
            this.checkEdgeIntersectionSplit((EdgeRing)var10.inner.get(var11));
         }
      }
   }

   void checkEdgeIntersection(EdgeRing var1, EdgeRing var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
         Edge var4 = (Edge)var1.get(var3);

         for (int var5 = 0; var5 < var2.size(); var5++) {
            Edge var6 = (Edge)var2.get(var5);
            if (this.intersects(var4.node1, var4.node2, var6)) {
               Intersection var7 = this.getIntersection(var4, var6);
               if (var7 != null) {
                  var4.intersections.add(var7);
                  var6.intersections.add(var7);
                  this.nodes.add(var7.nodeSplit);
                  this.intersectNodes.add(var7.nodeSplit);
               }
            }
         }
      }
   }

   void checkEdgeIntersectionSplit(EdgeRing var1) {
      for (int var2 = var1.size() - 1; var2 >= 0; var2--) {
         Edge var3 = (Edge)var1.get(var2);
         if (!var3.intersections.isEmpty()) {
            comparator.edge = var3;
            Collections.sort(var3.intersections, comparator);

            for (int var4 = var3.intersections.size() - 1; var4 >= 0; var4--) {
               Intersection var5 = (Intersection)var3.intersections.get(var4);
               Edge var6 = var5.split(var3);
               this.edges.add(var6);
            }
         }
      }
   }

   void checkNodesInObstacles() {
      for (int var1 = 0; var1 < this.nodes.size(); var1++) {
         Node var2 = this.nodes.get(var1);

         for (int var3 = 0; var3 < this.obstacles.size(); var3++) {
            Obstacle var4 = this.obstacles.get(var3);
            if (var4.isNodeInsideOf(var2)) {
               var2.ignore = true;
               break;
            }
         }
      }

      for (int var5 = 0; var5 < this.perimeterNodes.size(); var5++) {
         Node var6 = this.perimeterNodes.get(var5);

         for (int var7 = 0; var7 < this.obstacles.size(); var7++) {
            Obstacle var8 = this.obstacles.get(var7);
            if (var8.isNodeInsideOf(var6)) {
               var6.ignore = true;
               break;
            }
         }
      }
   }

   void addPerimeterEdges() {
      VehicleRect var1 = this.cluster.bounds();
      var1.x--;
      var1.y--;
      var1.w += 2;
      var1.h += 2;
      ClusterOutlineGrid var2 = clusterOutlineGrid.setSize(var1.w, var1.h);
      int var3 = this.cluster.z;

      for (int var4 = 0; var4 < this.cluster.rects.size(); var4++) {
         VehicleRect var5 = (VehicleRect)this.cluster.rects.get(var4);
         var5 = VehicleRect.alloc().init(var5.x - 1, var5.y - 1, var5.w + 2, var5.h + 2, var5.z);

         for (int var6 = var5.top(); var6 < var5.bottom(); var6++) {
            for (int var7 = var5.left(); var7 < var5.right(); var7++) {
               var2.setInner(var7 - var1.left(), var6 - var1.top(), var3);
            }
         }

         var5.release();
      }

      for (int var12 = 0; var12 < var1.h; var12++) {
         for (int var15 = 0; var15 < var1.w; var15++) {
            ClusterOutline var17 = var2.get(var15, var12, var3);
            if (var17.inner) {
               if (!var2.isInner(var15 - 1, var12, var3)) {
                  var17.w = true;
               }

               if (!var2.isInner(var15, var12 - 1, var3)) {
                  var17.n = true;
               }

               if (!var2.isInner(var15 + 1, var12, var3)) {
                  var17.e = true;
               }

               if (!var2.isInner(var15, var12 + 1, var3)) {
                  var17.s = true;
               }
            }
         }
      }

      for (int var13 = 0; var13 < var1.h; var13++) {
         for (int var16 = 0; var16 < var1.w; var16++) {
            ClusterOutline var18 = var2.get(var16, var13, var3);
            if (var18 != null && (var18.w || var18.n || var18.e || var18.s || var18.innerCorner)) {
               Square var19 = PolygonalMap2.instance.getSquare(var1.x + var16, var1.y + var13, var3);
               if (var19 != null && !var19.isNonThumpableSolid() && !var19.has(504)) {
                  Node var8 = PolygonalMap2.instance.getNodeForSquare(var19);
                  var8.flags |= 8;
                  var8.addGraph(this);
                  this.perimeterNodes.add(var8);
               }
            }

            if (var18 != null && var18.n && var18.w && var18.inner && !(var18.tw | var18.tn | var18.te | var18.ts)) {
               ArrayList var20 = var2.trace(var18);
               if (!var20.isEmpty()) {
                  for (int var21 = 0; var21 < var20.size() - 1; var21++) {
                     Node var9 = (Node)var20.get(var21);
                     Node var10 = (Node)var20.get(var21 + 1);
                     var9.x = var9.x + var1.left();
                     var9.y = var9.y + var1.top();
                     Edge var11 = Edge.alloc().init(var9, var10, null, null);
                     this.perimeterEdges.add(var11);
                  }

                  if (var20.get(var20.size() - 1) != var20.get(0)) {
                     Node var10000 = (Node)var20.get(var20.size() - 1);
                     var10000.x = var10000.x + var1.left();
                     var10000 = (Node)var20.get(var20.size() - 1);
                     var10000.y = var10000.y + var1.top();
                  }
               }
            }
         }
      }

      var2.releaseElements();
      var1.release();
   }

   void calculateNodeVisibility() {
      ArrayList var1 = new ArrayList();
      var1.addAll(this.nodes);
      var1.addAll(this.perimeterNodes);

      for (int var2 = 0; var2 < var1.size(); var2++) {
         Node var3 = (Node)var1.get(var2);
         if (!var3.ignore && (var3.square == null || !var3.square.has(504))) {
            for (int var4 = var2 + 1; var4 < var1.size(); var4++) {
               Node var5 = (Node)var1.get(var4);
               if (!var5.ignore && (var5.square == null || !var5.square.has(504)) && (!var3.hasFlag(8) || !var5.hasFlag(8))) {
                  if (var3.isConnectedTo(var5)) {
                     if ((var3.square == null || !var3.square.isCanPathW() && !var3.square.isCanPathN())
                        && (var5.square == null || !var5.square.isCanPathW() && !var5.square.isCanPathN())
                        && !$assertionsDisabled) {
                        throw new AssertionError();
                     }
                  } else if (this.isVisible(var3, var5)) {
                     PolygonalMap2.instance.connectTwoNodes(var3, var5);
                  }
               }
            }
         }
      }
   }

   void addNode(Node var1) {
      if (this.created && !var1.ignore) {
         ArrayList var2 = new ArrayList();
         var2.addAll(this.nodes);
         var2.addAll(this.perimeterNodes);

         for (int var3 = 0; var3 < var2.size(); var3++) {
            Node var4 = (Node)var2.get(var3);
            if (!var4.ignore && this.isVisible(var4, var1)) {
               PolygonalMap2.instance.connectTwoNodes(var1, var4);
            }
         }
      }

      this.nodes.add(var1);
   }

   void removeNode(Node var1) {
      this.nodes.remove(var1);

      for (int var2 = var1.visible.size() - 1; var2 >= 0; var2--) {
         Connection var3 = (Connection)var1.visible.get(var2);
         PolygonalMap2.instance.breakConnection(var3);
      }
   }

   boolean contains(float var1, float var2, int var3) {
      for (int var4 = 0; var4 < this.cluster.rects.size(); var4++) {
         VehicleRect var5 = (VehicleRect)this.cluster.rects.get(var4);
         if (var5.containsPoint(var1, var2, var3)) {
            return true;
         }
      }

      return false;
   }

   boolean contains(float var1, float var2, int var3, int var4) {
      for (int var5 = 0; var5 < this.cluster.rects.size(); var5++) {
         VehicleRect var6 = (VehicleRect)this.cluster.rects.get(var5);
         if (var6.containsPoint(var1, var2, var3, var4)) {
            return true;
         }
      }

      return false;
   }

   boolean contains(Square var1) {
      for (int var2 = 0; var2 < this.cluster.rects.size(); var2++) {
         VehicleRect var3 = (VehicleRect)this.cluster.rects.get(var2);
         if (var3.containsPoint(var1.x + 0.5F, var1.y + 0.5F, var1.z)) {
            return true;
         }
      }

      return false;
   }

   boolean contains(Square var1, int var2) {
      for (int var3 = 0; var3 < this.cluster.rects.size(); var3++) {
         VehicleRect var4 = (VehicleRect)this.cluster.rects.get(var3);
         if (var4.containsPoint(var1.x + 0.5F, var1.y + 0.5F, var1.z, var2)) {
            return true;
         }
      }

      return false;
   }

   private int getPointOutsideObstacles(float var1, float var2, float var3, AdjustStartEndNodeData var4) {
      ClosestPointOnEdge var5 = PolygonalMap2.instance.closestPointOnEdge;
      double var6 = Double.MAX_VALUE;
      Edge var8 = null;
      Node var9 = null;
      float var10 = 0.0F;
      float var11 = 0.0F;

      for (int var12 = 0; var12 < this.obstacles.size(); var12++) {
         Obstacle var13 = this.obstacles.get(var12);
         if (var13.bounds.containsPoint(var1, var2) && var13.isPointInside(var1, var2)) {
            var13.getClosestPointOnEdge(var1, var2, var5);
            if (var5.edge != null && var5.distSq < var6) {
               var6 = var5.distSq;
               var8 = var5.edge;
               var9 = var5.node;
               var10 = var5.point.x;
               var11 = var5.point.y;
            }
         }
      }

      if (var8 != null) {
         var5.edge = var8;
         var5.node = var9;
         var5.point.set(var10, var11);
         var5.distSq = var6;
         if (var8.obstacle.splitEdgeAtNearestPoint(var5, (int)var3, var4)) {
            var4.graph = this;
            if (var4.isNodeNew) {
               this.edges.add(var4.newEdge);
               this.addNode(var4.node);
            }

            return 1;
         } else {
            return -1;
         }
      } else {
         return 0;
      }
   }

   Node getClosestNodeTo(float var1, float var2) {
      Node var3 = null;
      float var4 = Float.MAX_VALUE;

      for (int var5 = 0; var5 < this.nodes.size(); var5++) {
         Node var6 = this.nodes.get(var5);
         float var7 = IsoUtils.DistanceToSquared(var6.x, var6.y, var1, var2);
         if (var7 < var4) {
            var3 = var6;
            var4 = var7;
         }
      }

      return var3;
   }

   void create() {
      for (int var1 = 0; var1 < this.cluster.rects.size(); var1++) {
         VehicleRect var2 = (VehicleRect)this.cluster.rects.get(var1);
         this.addEdgesForVehicle(var2.vehicle);
      }

      this.addWorldObstaclesClipper();

      for (int var4 = 0; var4 < this.obstacles.size(); var4++) {
         Obstacle var5 = this.obstacles.get(var4);
         if (var5.vehicle == null) {
            this.splitWorldObstacleEdges(var5.outer);

            for (int var3 = 0; var3 < var5.inner.size(); var3++) {
               this.splitWorldObstacleEdges((EdgeRing)var5.inner.get(var3));
            }
         }
      }

      this.checkEdgeIntersection();
      this.checkNodesInObstacles();
      this.calculateNodeVisibility();
      this.connectVehicleCrawlNodes();
      this.created = true;
   }

   static PolygonalMap2$VisibilityGraph alloc() {
      return pool.isEmpty() ? new PolygonalMap2$VisibilityGraph() : pool.pop();
   }

   void release() {
      for (int var1 = 0; var1 < this.nodes.size(); var1++) {
         if (!PolygonalMap2.instance.squareToNode.containsValue(this.nodes.get(var1))) {
            this.nodes.get(var1).release();
         }
      }

      for (int var3 = 0; var3 < this.perimeterEdges.size(); var3++) {
         this.perimeterEdges.get(var3).node1.release();
         this.perimeterEdges.get(var3).release();
      }

      for (int var4 = 0; var4 < this.obstacles.size(); var4++) {
         Obstacle var2 = this.obstacles.get(var4);
         var2.release();
      }

      for (int var5 = 0; var5 < this.cluster.rects.size(); var5++) {
         ((VehicleRect)this.cluster.rects.get(var5)).release();
      }

      this.cluster.release();
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }

   void render() {
      float var1 = 1.0F;

      for (Edge var3 : this.perimeterEdges) {
         LineDrawer.addLine(var3.node1.x, var3.node1.y, this.cluster.z, var3.node2.x, var3.node2.y, this.cluster.z, var1, 0.5F, 0.5F, null, true);
         var1 = 1.0F - var1;
      }

      for (Obstacle var14 : this.obstacles) {
         var1 = 1.0F;

         for (Edge var5 : var14.outer) {
            LineDrawer.addLine(var5.node1.x, var5.node1.y, this.cluster.z, var5.node2.x, var5.node2.y, this.cluster.z, var1, 0.5F, 0.5F, null, true);
            var1 = 1.0F - var1;
         }

         for (EdgeRing var23 : var14.inner) {
            for (Edge var7 : var23) {
               LineDrawer.addLine(var7.node1.x, var7.node1.y, this.cluster.z, var7.node2.x, var7.node2.y, this.cluster.z, var1, 0.5F, 0.5F, null, true);
               var1 = 1.0F - var1;
            }
         }

         if (DebugOptions.instance.PolymapRenderCrawling.getValue()) {
            for (Node var24 : var14.crawlNodes) {
               LineDrawer.addLine(
                  var24.x - 0.05F, var24.y - 0.05F, this.cluster.z, var24.x + 0.05F, var24.y + 0.05F, this.cluster.z, 0.5F, 1.0F, 0.5F, null, false
               );

               for (Connection var32 : var24.visible) {
                  Node var8 = var32.otherNode(var24);
                  if (var8.hasFlag(1)) {
                     LineDrawer.addLine(var24.x, var24.y, this.cluster.z, var8.x, var8.y, this.cluster.z, 0.5F, 1.0F, 0.5F, null, true);
                  }
               }
            }
         }
      }

      for (Node var15 : this.perimeterNodes) {
         if (DebugOptions.instance.PolymapRenderConnections.getValue()) {
            for (Connection var25 : var15.visible) {
               Node var29 = var25.otherNode(var15);
               LineDrawer.addLine(var15.x, var15.y, this.cluster.z, var29.x, var29.y, this.cluster.z, 0.0F, 0.25F, 0.0F, null, true);
            }
         }

         if (DebugOptions.instance.PolymapRenderNodes.getValue()) {
            float var21 = 1.0F;
            float var26 = 0.5F;
            float var30 = 0.0F;
            if (var15.ignore) {
               var26 = 1.0F;
            }

            LineDrawer.addLine(
               var15.x - 0.05F, var15.y - 0.05F, this.cluster.z, var15.x + 0.05F, var15.y + 0.05F, this.cluster.z, var21, var26, var30, null, false
            );
         }
      }

      for (Node var16 : this.nodes) {
         if (DebugOptions.instance.PolymapRenderConnections.getValue()) {
            for (Connection var27 : var16.visible) {
               Node var31 = var27.otherNode(var16);
               if (this.nodes.contains(var31)) {
                  LineDrawer.addLine(var16.x, var16.y, this.cluster.z, var31.x, var31.y, this.cluster.z, 0.0F, 1.0F, 0.0F, null, true);
               }
            }
         }

         if (DebugOptions.instance.PolymapRenderNodes.getValue() || var16.ignore) {
            LineDrawer.addLine(
               var16.x - 0.05F, var16.y - 0.05F, this.cluster.z, var16.x + 0.05F, var16.y + 0.05F, this.cluster.z, 1.0F, 1.0F, 0.0F, null, false
            );
         }
      }

      for (Node var17 : this.intersectNodes) {
         LineDrawer.addLine(var17.x - 0.1F, var17.y - 0.1F, this.cluster.z, var17.x + 0.1F, var17.y + 0.1F, this.cluster.z, 1.0F, 0.0F, 0.0F, null, false);
      }
   }
}
