package zombie.network;

import zombie.network.ServerChunkLoader.SaveTask;

class ServerChunkLoader$QuitThreadTask implements SaveTask {
   private ServerChunkLoader$QuitThreadTask(ServerChunkLoader var1) {
      this.this$0 = var1;
   }

   public void save() throws Exception {
      this.this$0.threadSave.quit = true;
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
