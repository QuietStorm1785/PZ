package zombie.audio;

import java.util.HashMap;
import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.iso.IsoObject;

public final class ObjectAmbientEmitters$ChunkData {
   final HashMap<IsoObject, PerObjectLogic> m_objects = new HashMap<>();

   public boolean hasObject(IsoObject var1) {
      return this.m_objects.containsKey(var1);
   }

   public void addObject(IsoObject var1, PerObjectLogic var2) {
      if (!this.m_objects.containsKey(var1)) {
         this.m_objects.put(var1, var2);
      }
   }

   public void removeObject(IsoObject var1) {
      this.m_objects.remove(var1);
   }

   public void reset() {
      this.m_objects.clear();
   }
}
