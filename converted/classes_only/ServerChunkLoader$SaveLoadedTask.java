package zombie.network;

import zombie.iso.IsoChunk;
import zombie.network.ClientChunkRequest.Chunk;
import zombie.network.ServerChunkLoader.SaveTask;

class ServerChunkLoader$SaveLoadedTask implements SaveTask {
   private final ClientChunkRequest ccr;
   private final Chunk chunk;

   public ServerChunkLoader$SaveLoadedTask(ServerChunkLoader var1, ClientChunkRequest var2, Chunk var3) {
      this.this$0 = var1;
      this.ccr = var2;
      this.chunk = var3;
   }

   public void save() throws Exception {
      long var1 = ChunkChecksum.getChecksumIfExists(this.chunk.wx, this.chunk.wy);
      this.this$0.crcSave.reset();
      this.this$0.crcSave.update(this.chunk.bb.array(), 0, this.chunk.bb.position());
      if (var1 != this.this$0.crcSave.getValue()) {
         ChunkChecksum.setChecksum(this.chunk.wx, this.chunk.wy, this.this$0.crcSave.getValue());
         IsoChunk.SafeWrite("map_", this.chunk.wx, this.chunk.wy, this.chunk.bb);
      }
   }

   public void release() {
      this.ccr.releaseChunk(this.chunk);
   }

   public int wx() {
      return this.chunk.wx;
   }

   public int wy() {
      return this.chunk.wy;
   }
}
