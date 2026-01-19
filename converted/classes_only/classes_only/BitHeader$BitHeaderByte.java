package zombie.util.io;

import java.util.concurrent.ConcurrentLinkedDeque;
import zombie.core.utils.Bits;
import zombie.util.io.BitHeader.BitHeaderBase;

public class BitHeader$BitHeaderByte extends BitHeaderBase {
   private ConcurrentLinkedDeque<BitHeader$BitHeaderByte> pool;
   private byte header;

   private BitHeader$BitHeaderByte() {
   }

   public void release() {
      this.reset();
      BitHeader.pool_byte.offer(this);
   }

   public int getLen() {
      return Bits.getLen(this.header);
   }

   protected void reset_header() {
      this.header = 0;
   }

   protected void write_header() {
      this.buffer.put(this.header);
   }

   protected void read_header() {
      this.header = this.buffer.get();
   }

   protected void addflags_header(int var1) {
      this.header = Bits.addFlags(this.header, var1);
   }

   protected void addflags_header(long var1) {
      this.header = Bits.addFlags(this.header, var1);
   }

   protected boolean hasflags_header(int var1) {
      return Bits.hasFlags(this.header, var1);
   }

   protected boolean hasflags_header(long var1) {
      return Bits.hasFlags(this.header, var1);
   }

   protected boolean equals_header(int var1) {
      return this.header == var1;
   }

   protected boolean equals_header(long var1) {
      return this.header == var1;
   }
}
