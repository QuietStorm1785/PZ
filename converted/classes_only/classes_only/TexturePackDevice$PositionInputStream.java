package zombie.fileSystem;

import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStream;

public final class TexturePackDevice$PositionInputStream extends FilterInputStream {
   private long pos;
   private long mark;

   public TexturePackDevice$PositionInputStream(TexturePackDevice var1, InputStream var2) {
      super(var2);
      this.this$0 = var1;
      this.pos = 0L;
      this.mark = 0L;
   }

   public synchronized long getPosition() {
      return this.pos;
   }

   @Override
   public synchronized int read() throws IOException {
      int var1 = super.read();
      if (var1 >= 0) {
         this.pos++;
      }

      return var1;
   }

   @Override
   public synchronized int read(byte[] var1, int var2, int var3) throws IOException {
      int var4 = super.read(var1, var2, var3);
      if (var4 > 0) {
         this.pos += var4;
      }

      return var4;
   }

   @Override
   public synchronized long skip(long var1) throws IOException {
      long var3 = super.skip(var1);
      if (var3 > 0L) {
         this.pos += var3;
      }

      return var3;
   }

   @Override
   public synchronized void mark(int var1) {
      super.mark(var1);
      this.mark = this.pos;
   }

   @Override
   public synchronized void reset() throws IOException {
      if (!this.markSupported()) {
         throw new IOException("Mark not supported.");
      } else {
         super.reset();
         this.pos = this.mark;
      }
   }
}
