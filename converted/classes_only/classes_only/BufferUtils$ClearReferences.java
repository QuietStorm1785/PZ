package zombie.core.utils;

import java.lang.ref.Reference;

class BufferUtils$ClearReferences extends Thread {
   BufferUtils$ClearReferences() {
      this.setDaemon(true);
   }

   @Override
   public void run() {
      try {
         while (true) {
            Reference var1 = BufferUtils.removeCollected.remove();
            BufferUtils.trackedBuffers.remove(var1);
         }
      } catch (InterruptedException var2) {
         var2.printStackTrace();
      }
   }
}
