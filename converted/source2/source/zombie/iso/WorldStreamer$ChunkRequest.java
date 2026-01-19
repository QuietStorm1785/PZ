package zombie.iso;

import java.nio.ByteBuffer;
import java.util.ArrayDeque;

final class WorldStreamer$ChunkRequest {
   static final ArrayDeque<WorldStreamer$ChunkRequest> pool = new ArrayDeque<>();
   IsoChunk chunk;
   int requestNumber;
   boolean[] partsReceived = null;
   long crc;
   ByteBuffer bb;
   transient int flagsMain;
   transient int flagsUDP;
   transient int flagsWS;
   long time;
   WorldStreamer$ChunkRequest next;

   private WorldStreamer$ChunkRequest() {
   }

   boolean isReceived() {
      if (this.partsReceived == null) {
         return false;
      } else {
         for (int var1 = 0; var1 < this.partsReceived.length; var1++) {
            if (!this.partsReceived[var1]) {
               return false;
            }
         }

         return true;
      }
   }

   static WorldStreamer$ChunkRequest alloc() {
      return pool.isEmpty() ? new WorldStreamer$ChunkRequest() : pool.pop();
   }

   static void release(WorldStreamer$ChunkRequest var0) {
      var0.chunk = null;
      var0.partsReceived = null;
      var0.bb = null;
      var0.flagsMain = 0;
      var0.flagsUDP = 0;
      var0.flagsWS = 0;
      pool.push(var0);
   }
}
