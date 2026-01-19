package zombie;

import zombie.iso.Vector2;

public class CollisionManager$PolygonCollisionResult {
   public boolean WillIntersect;
   public boolean Intersect;
   public Vector2 MinimumTranslationVector;

   public CollisionManager$PolygonCollisionResult(CollisionManager var1) {
      this.this$0 = var1;
      this.MinimumTranslationVector = new Vector2();
   }
}
