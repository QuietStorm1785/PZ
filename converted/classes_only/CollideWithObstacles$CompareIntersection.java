package zombie.vehicles;

import java.util.Comparator;
import zombie.vehicles.CollideWithObstacles.CCEdge;
import zombie.vehicles.CollideWithObstacles.CCIntersection;

final class CollideWithObstacles$CompareIntersection implements Comparator<CCIntersection> {
   CCEdge edge;

   public int compare(CCIntersection var1, CCIntersection var2) {
      float var3 = this.edge == var1.edge1 ? var1.dist1 : var1.dist2;
      float var4 = this.edge == var2.edge1 ? var2.dist1 : var2.dist2;
      if (var3 < var4) {
         return -1;
      } else {
         return var3 > var4 ? 1 : 0;
      }
   }
}
