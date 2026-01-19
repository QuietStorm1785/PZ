package zombie.vehicles;

import zombie.ai.astar.Mover;
import zombie.vehicles.PolygonalMap2.Path;

public interface PolygonalMap2$IPathfinder {
   void Succeeded(Path var1, Mover var2);

   void Failed(Mover var1);
}
