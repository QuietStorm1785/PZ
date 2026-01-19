package com.jcraft.jorbis;

import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;

class VorbisFile$SeekableInputStream extends InputStream {
   final String mode;
   RandomAccessFile raf;

   VorbisFile$SeekableInputStream(VorbisFile var1, String var2) throws IOException {
      this.this$0 = var1;
      this.mode = "r";
      this.raf = null;
      this.raf = new RandomAccessFile(var2, "r");
   }

   @Override
   public int available() throws IOException {
      return this.raf.length() == this.raf.getFilePointer() ? 0 : 1;
   }

   @Override
   public void close() throws IOException {
      this.raf.close();
   }

   public long getLength() throws IOException {
      return this.raf.length();
   }

   @Override
   public synchronized void mark(int var1) {
   }

   @Override
   public boolean markSupported() {
      return false;
   }

   @Override
   public int read() throws IOException {
      return this.raf.read();
   }

   @Override
   public int read(byte[] var1) throws IOException {
      return this.raf.read(var1);
   }

   @Override
   public int read(byte[] var1, int var2, int var3) throws IOException {
      return this.raf.read(var1, var2, var3);
   }

   @Override
   public synchronized void reset() throws IOException {
   }

   public void seek(long var1) throws IOException {
      this.raf.seek(var1);
   }

   @Override
   public long skip(long var1) throws IOException {
      return this.raf.skipBytes((int)var1);
   }

   public long tell() throws IOException {
      return this.raf.getFilePointer();
   }
}
