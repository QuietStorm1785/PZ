package de.jarnbjo.ogg;

import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.util.LinkedList;

public class UncachedUrlStream$LoaderThread implements Runnable {
   private InputStream source;
   private LinkedList pageCache;
   private RandomAccessFile drain;
   private byte[] memoryCache;
   private boolean bosDone;
   private int pageNumber;

   public UncachedUrlStream$LoaderThread(UncachedUrlStream var1, InputStream var2, LinkedList var3) {
      this.this$0 = var1;
      this.bosDone = false;
      this.source = var2;
      this.pageCache = var3;
   }

   @Override
   public void run() {
      try {
         boolean var1 = false;
         byte[] var2 = new byte[8192];

         while (!var1) {
            OggPage var3 = OggPage.create(this.source);
            synchronized (this.this$0.drainLock) {
               this.pageCache.add(var3);
            }

            if (!var3.isBos()) {
               this.bosDone = true;
            }

            if (var3.isEos()) {
               var1 = true;
            }

            LogicalOggStreamImpl var10 = (LogicalOggStreamImpl)this.this$0.getLogicalStream(var3.getStreamSerialNumber());
            if (var10 == null) {
               var10 = new LogicalOggStreamImpl(this.this$0, var3.getStreamSerialNumber());
               this.this$0.logicalStreams.put(new Integer(var3.getStreamSerialNumber()), var10);
               var10.checkFormat(var3);
            }

            this.pageNumber++;

            while (this.pageCache.size() > 10) {
               try {
                  Thread.sleep(200L);
               } catch (InterruptedException var6) {
               }
            }
         }
      } catch (EndOfOggStreamException var8) {
      } catch (IOException var9) {
         var9.printStackTrace();
      }
   }

   public boolean isBosDone() {
      return this.bosDone;
   }
}
