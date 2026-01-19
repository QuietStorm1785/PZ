package zombie.network;

import zombie.iso.IsoChunk;
import zombie.iso.WorldReuserThread;
import zombie.network.ServerChunkLoader.SaveTask;

class ServerChunkLoader$SaveUnloadedTask implements SaveTask {
   private final IsoChunk chunk;

   public ServerChunkLoader$SaveUnloadedTask(ServerChunkLoader var1, IsoChunk var2) {
      this.this$0 = var1;
      this.chunk = var2;
   }

   public void save() throws Exception {
      this.chunk.Save(false);
   }

   public void release() {
      WorldReuserThread.instance.addReuseChunk(this.chunk);
   }

   public int wx() {
      return this.chunk.wx;
   }

   public int wy() {
      return this.chunk.wy;
   }
}
