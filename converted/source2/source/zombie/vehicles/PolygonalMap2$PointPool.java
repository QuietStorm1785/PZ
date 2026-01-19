package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.Point;

final class PolygonalMap2$PointPool {
   final ArrayDeque<Point> pool = new ArrayDeque<>();

   private PolygonalMap2$PointPool() {
   }

   Point alloc() {
      return this.pool.isEmpty() ? new Point() : this.pool.pop();
   }

   void release(Point var1) {
      this.pool.push(var1);
   }
}
