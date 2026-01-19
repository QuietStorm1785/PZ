package de.jarnbjo.ogg;

import de.jarnbjo.ogg.CachedUrlStream.LoaderThread;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;

public class CachedUrlStream implements PhysicalOggStream {
   private boolean closed = false;
   private URLConnection source;
   private InputStream sourceStream;
   private Object drainLock = new Object();
   private RandomAccessFile drain;
   private byte[] memoryCache;
   private ArrayList pageOffsets = new ArrayList();
   private ArrayList pageLengths = new ArrayList();
   private long numberOfSamples = -1L;
   private long cacheLength;
   private HashMap logicalStreams = new HashMap();
   private LoaderThread loaderThread;

   public CachedUrlStream(URL var1) throws OggFormatException, IOException {
      this(var1, null);
   }

   public CachedUrlStream(URL var1, RandomAccessFile var2) throws OggFormatException, IOException {
      this.source = var1.openConnection();
      if (var2 == null) {
         int var3 = this.source.getContentLength();
         if (var3 == -1) {
            throw new IOException("The URLConncetion's content length must be set when operating with a in-memory cache.");
         }

         this.memoryCache = new byte[var3];
      }

      this.drain = var2;
      this.sourceStream = this.source.getInputStream();
      this.loaderThread = new LoaderThread(this, this.sourceStream, var2, this.memoryCache);
      new Thread(this.loaderThread).start();

      while (!this.loaderThread.isBosDone() || this.pageOffsets.size() < 20) {
         try {
            Thread.sleep(200L);
         } catch (InterruptedException var4) {
         }
      }
   }

   public Collection getLogicalStreams() {
      return this.logicalStreams.values();
   }

   public boolean isOpen() {
      return !this.closed;
   }

   public void close() throws IOException {
      this.closed = true;
      this.sourceStream.close();
   }

   public long getCacheLength() {
      return this.cacheLength;
   }

   public OggPage getOggPage(int var1) throws IOException {
      synchronized (this.drainLock) {
         Long var3 = (Long)this.pageOffsets.get(var1);
         Long var4 = (Long)this.pageLengths.get(var1);
         if (var3 != null) {
            if (this.drain != null) {
               this.drain.seek(var3);
               return OggPage.create(this.drain);
            } else {
               byte[] var5 = new byte[var4.intValue()];
               System.arraycopy(this.memoryCache, var3.intValue(), var5, 0, var4.intValue());
               return OggPage.create(var5);
            }
         } else {
            return null;
         }
      }
   }

   private LogicalOggStream getLogicalStream(int var1) {
      return (LogicalOggStream)this.logicalStreams.get(new Integer(var1));
   }

   public void setTime(long var1) throws IOException {
      for (LogicalOggStream var4 : this.logicalStreams.values()) {
         var4.setTime(var1);
      }
   }

   public boolean isSeekable() {
      return true;
   }
}
