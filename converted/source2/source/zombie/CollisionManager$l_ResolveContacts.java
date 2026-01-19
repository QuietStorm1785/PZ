package zombie;

import java.util.ArrayList;
import java.util.List;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoPushableObject;
import zombie.iso.Vector2;

class CollisionManager$l_ResolveContacts {
   static final Vector2 vel = new Vector2();
   static final Vector2 vel2 = new Vector2();
   static final List<IsoPushableObject> pushables = new ArrayList<>();
   static IsoMovingObject[] objectListInvoking = new IsoMovingObject[1024];

   private CollisionManager$l_ResolveContacts() {
   }
}
