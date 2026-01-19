package zombie.vehicles;

import org.joml.Vector2f;
import zombie.vehicles.CollideWithObstaclesPoly.CCEdge;
import zombie.vehicles.CollideWithObstaclesPoly.CCNode;

final class CollideWithObstaclesPoly$ClosestPointOnEdge {
   CCEdge edge;
   CCNode node;
   final Vector2f point = new Vector2f();
   double distSq;

   private CollideWithObstaclesPoly$ClosestPointOnEdge() {
   }
}
