package zombie.network;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.zip.CRC32;
import java.util.zip.Deflater;
import zombie.ChunkMapFilenames;
import zombie.core.network.ByteBufferWriter;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.iso.IsoChunk;
import zombie.network.ClientChunkRequest.Chunk;
import zombie.network.PacketTypes.PacketType;
import zombie.network.PlayerDownloadServer.1;
import zombie.network.PlayerDownloadServer.EThreadCommand;
import zombie.network.PlayerDownloadServer.WorkerThreadCommand;

final class PlayerDownloadServer$WorkerThread extends Thread {
   boolean bQuit;
   volatile boolean bReady;
   final LinkedBlockingQueue<WorkerThreadCommand> commandQ;
   final ConcurrentLinkedQueue<ClientChunkRequest> freeRequests;
   final ConcurrentLinkedQueue<Integer> cancelQ;
   final ArrayList<Integer> cancelled;
   final CRC32 crcMaker;
   static final int chunkSize = 1000;
   private byte[] inMemoryZip;
   private final Deflater compressor;

   private PlayerDownloadServer$WorkerThread(PlayerDownloadServer var1) {
      this.this$0 = var1;
      this.bReady = true;
      this.commandQ = new LinkedBlockingQueue<>();
      this.freeRequests = new ConcurrentLinkedQueue<>();
      this.cancelQ = new ConcurrentLinkedQueue<>();
      this.cancelled = new ArrayList<>();
      this.crcMaker = new CRC32();
      this.inMemoryZip = new byte[20480];
      this.compressor = new Deflater();
   }

   @Override
   public void run() {
      while (!this.bQuit) {
         try {
            this.runInner();
         } catch (Exception var2) {
            var2.printStackTrace();
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private void runInner() throws InterruptedException, IOException {
      MPStatistic.getInstance().PlayerDownloadServer.End();
      WorkerThreadCommand var1 = this.commandQ.take();
      MPStatistic.getInstance().PlayerDownloadServer.Start();
      switch (1.$SwitchMap$zombie$network$PlayerDownloadServer$EThreadCommand[var1.e.ordinal()]) {
         case 1:
            try {
               this.sendLargeArea(var1.ccr);
               break;
            } finally {
               this.bReady = true;
            }
         case 2:
            try {
               this.sendArray(var1.ccr);
               break;
            } finally {
               this.bReady = true;
            }
         case 3:
            this.bQuit = true;
      }
   }

   void putCommand(EThreadCommand var1, ClientChunkRequest var2) {
      WorkerThreadCommand var3 = new WorkerThreadCommand();
      var3.e = var1;
      var3.ccr = var2;

      while (true) {
         try {
            this.commandQ.put(var3);
            return;
         } catch (InterruptedException var5) {
         }
      }
   }

   private int compressChunk(Chunk var1) {
      this.compressor.reset();
      this.compressor.setInput(var1.bb.array(), 0, var1.bb.limit());
      this.compressor.finish();
      if (this.inMemoryZip.length < var1.bb.limit() * 1.5) {
         this.inMemoryZip = new byte[(int)(var1.bb.limit() * 1.5)];
      }

      return this.compressor.deflate(this.inMemoryZip, 0, this.inMemoryZip.length, 3);
   }

   private void sendChunk(Chunk var1) {
      try {
         long var2 = this.compressChunk(var1);
         long var4 = var2 / 1000L;
         if (var2 % 1000L != 0L) {
            var4++;
         }

         long var6 = 0L;

         for (int var8 = 0; var8 < var4; var8++) {
            long var9 = var2 - var6 > 1000L ? 1000L : var2 - var6;
            ByteBufferWriter var11 = this.this$0.startPacket();
            PacketType.SentChunk.doPacket(var11);
            var11.putInt(var1.requestNumber);
            var11.putInt((int)var4);
            var11.putInt(var8);
            var11.putInt((int)var2);
            var11.putInt((int)var6);
            var11.putInt((int)var9);
            var11.bb.put(this.inMemoryZip, (int)var6, (int)var9);
            this.this$0.sendPacket(PacketType.SentChunk);
            var6 += var9;
         }
      } catch (Exception var12) {
         var12.printStackTrace();
         this.sendNotRequired(var1, false);
      }
   }

   private void sendNotRequired(Chunk var1, boolean var2) {
      ByteBufferWriter var3 = this.this$0.startPacket();
      PacketType.NotRequiredInZip.doPacket(var3);
      var3.putInt(1);
      var3.putInt(var1.requestNumber);
      var3.putByte((byte)(var2 ? 1 : 0));
      this.this$0.sendPacket(PacketType.NotRequiredInZip);
   }

   private void sendLargeArea(ClientChunkRequest var1) throws IOException {
      for (int var2 = 0; var2 < var1.chunks.size(); var2++) {
         Chunk var3 = (Chunk)var1.chunks.get(var2);
         int var4 = var3.wx;
         int var5 = var3.wy;
         if (var3.bb != null) {
            var3.bb.limit(var3.bb.position());
            var3.bb.position(0);
            this.sendChunk(var3);
            var1.releaseBuffer(var3);
         } else {
            File var6 = ChunkMapFilenames.instance.getFilename(var4, var5);
            if (var6.exists()) {
               var1.getByteBuffer(var3);
               var3.bb = IsoChunk.SafeRead("map_", var4, var5, var3.bb);
               this.sendChunk(var3);
               var1.releaseBuffer(var3);
            }
         }
      }

      ClientChunkRequest.freeBuffers.clear();
      var1.chunks.clear();
   }

   private void sendArray(ClientChunkRequest var1) throws IOException {
      for (int var2 = 0; var2 < var1.chunks.size(); var2++) {
         Chunk var3 = (Chunk)var1.chunks.get(var2);
         if (!this.isRequestCancelled(var3)) {
            int var4 = var3.wx;
            int var5 = var3.wy;
            long var6 = var3.crc;
            if (var3.bb != null) {
               boolean var8 = true;
               if (var3.crc != 0L) {
                  this.crcMaker.reset();
                  this.crcMaker.update(var3.bb.array(), 0, var3.bb.position());
                  var8 = var3.crc != this.crcMaker.getValue();
                  if (var8 && this.this$0.NetworkFileDebug) {
                     DebugLog.log(DebugType.NetworkFileDebug, var4 + "," + var5 + ": crc server=" + this.crcMaker.getValue() + " client=" + var3.crc);
                  }
               }

               if (var8) {
                  if (this.this$0.NetworkFileDebug) {
                     DebugLog.log(DebugType.NetworkFileDebug, var4 + "," + var5 + ": send=true loaded=true");
                  }

                  var3.bb.limit(var3.bb.position());
                  var3.bb.position(0);
                  this.sendChunk(var3);
               } else {
                  if (this.this$0.NetworkFileDebug) {
                     DebugLog.log(DebugType.NetworkFileDebug, var4 + "," + var5 + ": send=false loaded=true");
                  }

                  this.sendNotRequired(var3, true);
               }

               var1.releaseBuffer(var3);
            } else {
               File var13 = ChunkMapFilenames.instance.getFilename(var4, var5);
               if (var13.exists()) {
                  long var9 = ChunkChecksum.getChecksum(var4, var5);
                  if (var9 != 0L && var9 == var3.crc) {
                     if (this.this$0.NetworkFileDebug) {
                        DebugLog.log(DebugType.NetworkFileDebug, var4 + "," + var5 + ": send=false loaded=false file=true");
                     }

                     this.sendNotRequired(var3, true);
                  } else {
                     var1.getByteBuffer(var3);
                     var3.bb = IsoChunk.SafeRead("map_", var4, var5, var3.bb);
                     boolean var11 = true;
                     if (var3.crc != 0L) {
                        this.crcMaker.reset();
                        this.crcMaker.update(var3.bb.array(), 0, var3.bb.limit());
                        var11 = var3.crc != this.crcMaker.getValue();
                     }

                     if (var11) {
                        if (this.this$0.NetworkFileDebug) {
                           DebugLog.log(DebugType.NetworkFileDebug, var4 + "," + var5 + ": send=true loaded=false file=true");
                        }

                        this.sendChunk(var3);
                     } else {
                        if (this.this$0.NetworkFileDebug) {
                           DebugLog.log(DebugType.NetworkFileDebug, var4 + "," + var5 + ": send=false loaded=false file=true");
                        }

                        this.sendNotRequired(var3, true);
                     }

                     var1.releaseBuffer(var3);
                  }
               } else {
                  if (this.this$0.NetworkFileDebug) {
                     DebugLog.log(DebugType.NetworkFileDebug, var4 + "," + var5 + ": send=false loaded=false file=false");
                  }

                  this.sendNotRequired(var3, var6 == 0L);
               }
            }
         }
      }

      for (int var12 = 0; var12 < var1.chunks.size(); var12++) {
         var1.releaseChunk((Chunk)var1.chunks.get(var12));
      }

      var1.chunks.clear();
      this.freeRequests.add(var1);
   }

   private boolean isRequestCancelled(Chunk var1) {
      for (Integer var2 = this.cancelQ.poll(); var2 != null; var2 = this.cancelQ.poll()) {
         this.cancelled.add(var2);
      }

      for (int var4 = 0; var4 < this.cancelled.size(); var4++) {
         Integer var3 = this.cancelled.get(var4);
         if (var3 == var1.requestNumber) {
            if (this.this$0.NetworkFileDebug) {
               DebugLog.log(DebugType.NetworkFileDebug, "cancelled request #" + var3);
            }

            this.cancelled.remove(var4);
            return true;
         }
      }

      return false;
   }
}
