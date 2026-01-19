package de.jarnbjo.ogg;

import de.jarnbjo.ogg.UncachedUrlStream.LoaderThread;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;

public class UncachedUrlStream implements PhysicalOggStream {
   private boolean closed = false;
   private URLConnection source;
   private InputStream sourceStream;
   private Object drainLock = new Object();
   private LinkedList pageCache = new LinkedList();
   private long numberOfSamples = -1L;
   private HashMap logicalStreams = new HashMap();
   private LoaderThread loaderThread;
   private static final int PAGECACHE_SIZE = 10;

   public UncachedUrlStream(URL var1) throws OggFormatException, IOException {
      this.source = var1.openConnection();
      this.sourceStream = this.source.getInputStream();
      this.loaderThread = new LoaderThread(this, this.sourceStream, this.pageCache);
      new Thread(this.loaderThread).start();

      while (!this.loaderThread.isBosDone() || this.pageCache.size() < 10) {
         try {
            Thread.sleep(200L);
         } catch (InterruptedException var3) {
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

   public OggPage getOggPage(int var1) throws IOException {
      while (this.pageCache.size() == 0) {
         try {
            Thread.sleep(100L);
         } catch (InterruptedException var4) {
         }
      }

      synchronized (this.drainLock) {
         return (OggPage)this.pageCache.removeFirst();
      }
   }

   private LogicalOggStream getLogicalStream(int var1) {
      return (LogicalOggStream)this.logicalStreams.get(new Integer(var1));
   }

   public void setTime(long var1) throws IOException {
      throw new UnsupportedOperationException("Method not supported by this class");
   }

   public boolean isSeekable() {
      return false;
   }
}
