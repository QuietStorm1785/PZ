package zombie.util.io;

import java.nio.ByteBuffer;

public abstract class BitHeader$BitHeaderBase implements BitHeaderRead, BitHeaderWrite {
   protected boolean isWrite;
   protected ByteBuffer buffer;
   protected int start_pos = -1;

   protected void setBuffer(ByteBuffer var1) {
      this.buffer = var1;
   }

   protected void setWrite(boolean var1) {
      this.isWrite = var1;
   }

   public int getStartPosition() {
      return this.start_pos;
   }

   protected void reset() {
      this.buffer = null;
      this.isWrite = false;
      this.start_pos = -1;
      this.reset_header();
   }

   public abstract int getLen();

   public abstract void release();

   protected abstract void reset_header();

   protected abstract void write_header();

   protected abstract void read_header();

   protected abstract void addflags_header(int var1);

   protected abstract void addflags_header(long var1);

   protected abstract boolean hasflags_header(int var1);

   protected abstract boolean hasflags_header(long var1);

   protected abstract boolean equals_header(int var1);

   protected abstract boolean equals_header(long var1);

   public void create() {
      if (this.isWrite) {
         this.start_pos = this.buffer.position();
         this.reset_header();
         this.write_header();
      } else {
         throw new RuntimeException("BitHeader -> Cannot write to a non write Header.");
      }
   }

   public void write() {
      if (this.isWrite) {
         int var1 = this.buffer.position();
         this.buffer.position(this.start_pos);
         this.write_header();
         this.buffer.position(var1);
      } else {
         throw new RuntimeException("BitHeader -> Cannot write to a non write Header.");
      }
   }

   public void read() {
      if (!this.isWrite) {
         this.start_pos = this.buffer.position();
         this.read_header();
      } else {
         throw new RuntimeException("BitHeader -> Cannot read from a non read Header.");
      }
   }

   public void addFlags(int var1) {
      if (this.isWrite) {
         this.addflags_header(var1);
      } else {
         throw new RuntimeException("BitHeader -> Cannot set bits on a non write Header.");
      }
   }

   public void addFlags(long var1) {
      if (this.isWrite) {
         this.addflags_header(var1);
      } else {
         throw new RuntimeException("BitHeader -> Cannot set bits on a non write Header.");
      }
   }

   public boolean hasFlags(int var1) {
      return this.hasflags_header(var1);
   }

   public boolean hasFlags(long var1) {
      return this.hasflags_header(var1);
   }

   public boolean equals(int var1) {
      return this.equals_header(var1);
   }

   public boolean equals(long var1) {
      return this.equals_header(var1);
   }
}
