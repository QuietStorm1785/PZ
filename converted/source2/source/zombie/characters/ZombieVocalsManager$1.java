package zombie.characters;

import java.util.Comparator;
import zombie.characters.ZombieVocalsManager.ObjectWithDistance;

class ZombieVocalsManager$1 implements Comparator<ObjectWithDistance> {
   ZombieVocalsManager$1(ZombieVocalsManager var1) {
      this.this$0 = var1;
   }

   public int compare(ObjectWithDistance var1, ObjectWithDistance var2) {
      return Float.compare(var1.distSq, var2.distSq);
   }
}
