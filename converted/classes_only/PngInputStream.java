package com.sixlegs.png;

import java.io.DataInput;
import java.io.DataInputStream;
import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.util.zip.CRC32;

final class PngInputStream extends InputStream implements DataInput {
   private final CRC32 crc = new CRC32();
   private final InputStream in;
   private final DataInputStream data;
   private final byte[] tmp = new byte[4096];
   private long total;
   private int length;
   private int left;

   public PngInputStream(InputStream var1) throws IOException {
      this.in = var1;
      this.data = new DataInputStream(this);
      this.left = 8;
      long var2 = this.readLong();
      if (var2 != -8552249625308161526L) {
         throw new PngException("Improper signature, expected 0x" + Long.toHexString(-8552249625308161526L) + ", got 0x" + Long.toHexString(var2), true);
      } else {
         this.total += 8L;
      }
   }

   public int startChunk() throws IOException {
      this.left = 8;
      this.length = this.readInt();
      if (this.length < 0) {
         throw new PngException("Bad chunk length: " + (4294967295L & this.length), true);
      } else {
         this.crc.reset();
         int var1 = this.readInt();
         this.left = this.length;
         this.total += 8L;
         return var1;
      }
   }

   public int endChunk(int var1) throws IOException {
      if (this.getRemaining() != 0) {
         throw new PngException(PngConstants.getChunkName(var1) + " read " + (this.length - this.left) + " bytes, expected " + this.length, true);
      } else {
         this.left = 4;
         int var2 = (int)this.crc.getValue();
         int var3 = this.readInt();
         if (var2 != var3) {
            throw new PngException("Bad CRC value for " + PngConstants.getChunkName(var1) + " chunk", true);
         } else {
            this.total = this.total + (this.length + 4);
            return var2;
         }
      }
   }

   @Override
   public int read() throws IOException {
      if (this.left == 0) {
         return -1;
      } else {
         int var1 = this.in.read();
         if (var1 != -1) {
            this.crc.update(var1);
            this.left--;
         }

         return var1;
      }
   }

   @Override
   public int read(byte[] var1, int var2, int var3) throws IOException {
      if (var3 == 0) {
         return 0;
      } else if (this.left == 0) {
         return -1;
      } else {
         int var4 = this.in.read(var1, var2, Math.min(this.left, var3));
         if (var4 != -1) {
            this.crc.update(var1, var2, var4);
            this.left -= var4;
         }

         return var4;
      }
   }

   @Override
   public long skip(long var1) throws IOException {
      int var3 = this.read(this.tmp, 0, (int)Math.min((long)this.tmp.length, var1));
      return var3 < 0 ? 0L : var3;
   }

   @Override
   public void close() {
      throw new UnsupportedOperationException("do not close me");
   }

   @Override
   public boolean readBoolean() throws IOException {
      return this.readUnsignedByte() != 0;
   }

   @Override
   public int readUnsignedByte() throws IOException {
      int var1 = this.read();
      if (var1 < 0) {
         throw new EOFException();
      } else {
         return var1;
      }
   }

   @Override
   public byte readByte() throws IOException {
      return (byte)this.readUnsignedByte();
   }

   @Override
   public int readUnsignedShort() throws IOException {
      int var1 = this.read();
      int var2 = this.read();
      if ((var1 | var2) < 0) {
         throw new EOFException();
      } else {
         return (var1 << 8) + (var2 << 0);
      }
   }

   @Override
   public short readShort() throws IOException {
      return (short)this.readUnsignedShort();
   }

   @Override
   public char readChar() throws IOException {
      return (char)this.readUnsignedShort();
   }

   @Override
   public int readInt() throws IOException {
      int var1 = this.read();
      int var2 = this.read();
      int var3 = this.read();
      int var4 = this.read();
      if ((var1 | var2 | var3 | var4) < 0) {
         throw new EOFException();
      } else {
         return (var1 << 24) + (var2 << 16) + (var3 << 8) + (var4 << 0);
      }
   }

   @Override
   public long readLong() throws IOException {
      return (4294967295L & this.readInt()) << 32 | 4294967295L & this.readInt();
   }

   @Override
   public float readFloat() throws IOException {
      return Float.intBitsToFloat(this.readInt());
   }

   @Override
   public double readDouble() throws IOException {
      return Double.longBitsToDouble(this.readLong());
   }

   @Override
   public void readFully(byte[] var1) throws IOException {
      this.data.readFully(var1, 0, var1.length);
   }

   @Override
   public void readFully(byte[] var1, int var2, int var3) throws IOException {
      this.data.readFully(var1, var2, var3);
   }

   @Override
   public int skipBytes(int var1) throws IOException {
      return this.data.skipBytes(var1);
   }

   @Override
   public String readLine() throws IOException {
      return this.data.readLine();
   }

   @Override
   public String readUTF() throws IOException {
      return this.data.readUTF();
   }

   public int getRemaining() {
      return this.left;
   }

   public long getOffset() {
      return this.total;
   }
}
