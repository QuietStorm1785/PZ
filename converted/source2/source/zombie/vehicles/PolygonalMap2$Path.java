package zombie.vehicles;

import java.awt.geom.Line2D;
import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.iso.IsoUtils;
import zombie.vehicles.PolygonalMap2.PathNode;
import zombie.vehicles.PolygonalMap2.SearchNode;

public final class PolygonalMap2$Path {
   final ArrayList<PathNode> nodes = new ArrayList<>();
   final ArrayDeque<PathNode> nodePool = new ArrayDeque<>();

   void clear() {
      for (int var1 = 0; var1 < this.nodes.size(); var1++) {
         this.nodePool.push(this.nodes.get(var1));
      }

      this.nodes.clear();
   }

   boolean isEmpty() {
      return this.nodes.isEmpty();
   }

   PathNode addNode(float var1, float var2, float var3) {
      return this.addNode(var1, var2, var3, 0);
   }

   PathNode addNode(float var1, float var2, float var3, int var4) {
      PathNode var5 = this.nodePool.isEmpty() ? new PathNode() : this.nodePool.pop();
      var5.init(var1, var2, var3, var4);
      this.nodes.add(var5);
      return var5;
   }

   PathNode addNode(SearchNode var1) {
      return this.addNode(var1.getX(), var1.getY(), var1.getZ(), var1.vgNode == null ? 0 : var1.vgNode.flags);
   }

   PathNode getNode(int var1) {
      return this.nodes.get(var1);
   }

   PathNode getLastNode() {
      return this.nodes.get(this.nodes.size() - 1);
   }

   void copyFrom(PolygonalMap2$Path var1) {
      if (!$assertionsDisabled && this == var1) {
         throw new AssertionError();
      } else {
         this.clear();

         for (int var2 = 0; var2 < var1.nodes.size(); var2++) {
            PathNode var3 = var1.nodes.get(var2);
            this.addNode(var3.x, var3.y, var3.z, var3.flags);
         }
      }
   }

   float length() {
      float var1 = 0.0F;

      for (int var2 = 0; var2 < this.nodes.size() - 1; var2++) {
         PathNode var3 = this.nodes.get(var2);
         PathNode var4 = this.nodes.get(var2 + 1);
         var1 += IsoUtils.DistanceTo(var3.x, var3.y, var3.z, var4.x, var4.y, var4.z);
      }

      return var1;
   }

   public boolean crossesSquare(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.nodes.size() - 1; var4++) {
         PathNode var5 = this.nodes.get(var4);
         PathNode var6 = this.nodes.get(var4 + 1);
         if ((int)var5.z == var3 || (int)var6.z == var3) {
            if (Line2D.linesIntersect(var5.x, var5.y, var6.x, var6.y, var1, var2, var1 + 1, var2)) {
               return true;
            }

            if (Line2D.linesIntersect(var5.x, var5.y, var6.x, var6.y, var1 + 1, var2, var1 + 1, var2 + 1)) {
               return true;
            }

            if (Line2D.linesIntersect(var5.x, var5.y, var6.x, var6.y, var1 + 1, var2 + 1, var1, var2 + 1)) {
               return true;
            }

            if (Line2D.linesIntersect(var5.x, var5.y, var6.x, var6.y, var1, var2 + 1, var1, var2)) {
               return true;
            }
         }
      }

      return false;
   }
}
