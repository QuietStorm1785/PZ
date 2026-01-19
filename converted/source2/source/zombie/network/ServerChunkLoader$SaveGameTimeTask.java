package zombie.network;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import zombie.GameTime;
import zombie.ZomboidFileSystem;
import zombie.network.ServerChunkLoader.SaveTask;

class ServerChunkLoader$SaveGameTimeTask implements SaveTask {
   private byte[] bytes;

   public ServerChunkLoader$SaveGameTimeTask(ServerChunkLoader var1, GameTime var2) {
      this.this$0 = var1;

      try {
         try (
            ByteArrayOutputStream var3 = new ByteArrayOutputStream(32768);
            DataOutputStream var4 = new DataOutputStream(var3);
         ) {
            var2.save(var4);
            var4.close();
            this.bytes = var3.toByteArray();
         }
      } catch (Exception var11) {
         var11.printStackTrace();
      }
   }

   public void save() throws Exception {
      if (this.bytes != null) {
         File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

         try (FileOutputStream var2 = new FileOutputStream(var1)) {
            var2.write(this.bytes);
         } catch (Exception var7) {
            var7.printStackTrace();
            return;
         }
      }
   }

   public void release() {
   }

   public int wx() {
      return 0;
   }

   public int wy() {
      return 0;
   }
}
