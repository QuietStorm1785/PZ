package zombie.audio;

import java.util.Comparator;
import zombie.audio.ObjectAmbientEmitters.ObjectWithDistance;

class ObjectAmbientEmitters$1 implements Comparator<ObjectWithDistance> {
   ObjectAmbientEmitters$1(ObjectAmbientEmitters var1) {
      this.this$0 = var1;
   }

   public int compare(ObjectWithDistance var1, ObjectWithDistance var2) {
      return Float.compare(var1.distSq, var2.distSq);
   }
}
