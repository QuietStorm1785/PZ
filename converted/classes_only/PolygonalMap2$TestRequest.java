package zombie.vehicles;

import zombie.ai.astar.Mover;
import zombie.vehicles.PolygonalMap2.IPathfinder;
import zombie.vehicles.PolygonalMap2.Path;

final class PolygonalMap2$TestRequest implements IPathfinder {
   final Path path = new Path();
   boolean done;

   private PolygonalMap2$TestRequest() {
   }

   public void Succeeded(Path var1, Mover var2) {
      this.path.copyFrom(var1);
      this.done = true;
   }

   public void Failed(Mover var1) {
      this.path.clear();
      this.done = true;
   }
}
