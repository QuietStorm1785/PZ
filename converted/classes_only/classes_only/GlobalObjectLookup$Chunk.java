package zombie.globalObjects;

import java.util.ArrayList;

final class GlobalObjectLookup$Chunk {
   final ArrayList<GlobalObject> objects = new ArrayList<>();

   private GlobalObjectLookup$Chunk() {
   }

   void Reset() {
      this.objects.clear();
   }
}
