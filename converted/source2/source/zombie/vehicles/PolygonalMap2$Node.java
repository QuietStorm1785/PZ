package zombie.vehicles;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.vehicles.PolygonalMap2.Connection;
import zombie.vehicles.PolygonalMap2.Edge;
import zombie.vehicles.PolygonalMap2.Obstacle;
import zombie.vehicles.PolygonalMap2.Square;
import zombie.vehicles.PolygonalMap2.VisibilityGraph;

final class PolygonalMap2$Node {
   static int nextID = 1;
   final int ID;
   float x;
   float y;
   int z;
   boolean ignore;
   Square square;
   ArrayList<VisibilityGraph> graphs;
   final ArrayList<Edge> edges = new ArrayList<>();
   final ArrayList<Connection> visible = new ArrayList<>();
   int flags = 0;
   static final ArrayList<Obstacle> tempObstacles = new ArrayList<>();
   static final ArrayDeque<PolygonalMap2$Node> pool = new ArrayDeque<>();

   PolygonalMap2$Node() {
      this.ID = nextID++;
   }

   PolygonalMap2$Node init(float var1, float var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.ignore = false;
      this.square = null;
      if (this.graphs != null) {
         this.graphs.clear();
      }

      this.edges.clear();
      this.visible.clear();
      this.flags = 0;
      return this;
   }

   PolygonalMap2$Node init(Square var1) {
      this.x = var1.x + 0.5F;
      this.y = var1.y + 0.5F;
      this.z = var1.z;
      this.ignore = false;
      this.square = var1;
      if (this.graphs != null) {
         this.graphs.clear();
      }

      this.edges.clear();
      this.visible.clear();
      this.flags = 0;
      return this;
   }

   PolygonalMap2$Node setXY(float var1, float var2) {
      this.x = var1;
      this.y = var2;
      return this;
   }

   void addGraph(VisibilityGraph var1) {
      if (this.graphs == null) {
         this.graphs = new ArrayList<>();
      }

      if (!$assertionsDisabled && this.graphs.contains(var1)) {
         throw new AssertionError();
      } else {
         this.graphs.add(var1);
      }
   }

   boolean sharesEdge(PolygonalMap2$Node var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
         Edge var3 = this.edges.get(var2);
         if (var3.hasNode(var1)) {
            return true;
         }
      }

      return false;
   }

   boolean sharesShape(PolygonalMap2$Node var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
         Edge var3 = this.edges.get(var2);

         for (int var4 = 0; var4 < var1.edges.size(); var4++) {
            Edge var5 = var1.edges.get(var4);
            if (var3.obstacle != null && var3.obstacle == var5.obstacle) {
               return true;
            }
         }
      }

      return false;
   }

   void getObstacles(ArrayList<Obstacle> var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
         Edge var3 = this.edges.get(var2);
         if (!var1.contains(var3.obstacle)) {
            var1.add(var3.obstacle);
         }
      }
   }

   boolean onSameShapeButDoesNotShareAnEdge(PolygonalMap2$Node var1) {
      tempObstacles.clear();
      this.getObstacles(tempObstacles);

      for (int var2 = 0; var2 < tempObstacles.size(); var2++) {
         Obstacle var3 = tempObstacles.get(var2);
         if (var3.hasNode(var1) && !var3.hasAdjacentNodes(this, var1)) {
            return true;
         }
      }

      return false;
   }

   boolean hasFlag(int var1) {
      return (this.flags & var1) != 0;
   }

   boolean isConnectedTo(PolygonalMap2$Node var1) {
      if (this.hasFlag(4)) {
         return true;
      } else {
         for (int var2 = 0; var2 < this.visible.size(); var2++) {
            Connection var3 = this.visible.get(var2);
            if (var3.node1 == var1 || var3.node2 == var1) {
               return true;
            }
         }

         return false;
      }
   }

   static PolygonalMap2$Node alloc() {
      if (pool.isEmpty()) {
         boolean var0 = false;
      } else {
         boolean var1 = false;
      }

      return pool.isEmpty() ? new PolygonalMap2$Node() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         for (int var1 = this.visible.size() - 1; var1 >= 0; var1--) {
            PolygonalMap2.instance.breakConnection(this.visible.get(var1));
         }

         pool.push(this);
      }
   }

   static void releaseAll(ArrayList<PolygonalMap2$Node> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         ((PolygonalMap2$Node)var0.get(var1)).release();
      }
   }
}
