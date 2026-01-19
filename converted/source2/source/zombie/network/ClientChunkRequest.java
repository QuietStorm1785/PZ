package zombie.network;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.core.raknet.UdpConnection;
import zombie.network.ClientChunkRequest.Chunk;

public class ClientChunkRequest {
   public ArrayList<Chunk> chunks = new ArrayList<>(20);
   private static final ConcurrentLinkedQueue<Chunk> freeChunks = new ConcurrentLinkedQueue<>();
   public static final ConcurrentLinkedQueue<ByteBuffer> freeBuffers = new ConcurrentLinkedQueue<>();
   public boolean largeArea = false;
   int minX;
   int maxX;
   int minY;
   int maxY;

   public Chunk getChunk() {
      Chunk var1 = freeChunks.poll();
      if (var1 == null) {
         var1 = new Chunk();
      }

      return var1;
   }

   public void releaseChunk(Chunk var1) {
      this.releaseBuffer(var1);
      freeChunks.add(var1);
   }

   public void getByteBuffer(Chunk var1) {
      var1.bb = freeBuffers.poll();
      if (var1.bb == null) {
         var1.bb = ByteBuffer.allocate(16384);
      } else {
         var1.bb.clear();
      }
   }

   public void releaseBuffer(Chunk var1) {
      if (var1.bb != null) {
         freeBuffers.add(var1.bb);
         var1.bb = null;
      }
   }

   public void releaseBuffers() {
      for (int var1 = 0; var1 < this.chunks.size(); var1++) {
         this.chunks.get(var1).bb = null;
      }
   }

   public void unpack(ByteBuffer var1, UdpConnection var2) {
      for (int var3 = 0; var3 < this.chunks.size(); var3++) {
         this.releaseBuffer(this.chunks.get(var3));
      }

      freeChunks.addAll(this.chunks);
      this.chunks.clear();
      int var6 = var1.getInt();

      for (int var4 = 0; var4 < var6; var4++) {
         Chunk var5 = this.getChunk();
         var5.requestNumber = var1.getInt();
         var5.wx = var1.getInt();
         var5.wy = var1.getInt();
         var5.crc = var1.getLong();
         this.chunks.add(var5);
      }

      this.largeArea = false;
   }

   public void unpackLargeArea(ByteBuffer var1, UdpConnection var2) {
      for (int var3 = 0; var3 < this.chunks.size(); var3++) {
         this.releaseBuffer(this.chunks.get(var3));
      }

      freeChunks.addAll(this.chunks);
      this.chunks.clear();
      this.minX = var1.getInt();
      this.minY = var1.getInt();
      this.maxX = var1.getInt();
      this.maxY = var1.getInt();

      for (int var6 = this.minX; var6 < this.maxX; var6++) {
         for (int var4 = this.minY; var4 < this.maxY; var4++) {
            Chunk var5 = this.getChunk();
            var5.requestNumber = var1.getInt();
            var5.wx = var6;
            var5.wy = var4;
            var5.crc = 0L;
            this.releaseBuffer(var5);
            this.chunks.add(var5);
         }
      }

      this.largeArea = true;
   }
}
