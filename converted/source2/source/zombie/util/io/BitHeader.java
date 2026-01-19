package zombie.util.io;

import java.nio.ByteBuffer;
import java.util.concurrent.ConcurrentLinkedDeque;
import zombie.debug.DebugLog;
import zombie.util.io.BitHeader.BitHeaderBase;
import zombie.util.io.BitHeader.BitHeaderByte;
import zombie.util.io.BitHeader.BitHeaderInt;
import zombie.util.io.BitHeader.BitHeaderLong;
import zombie.util.io.BitHeader.BitHeaderShort;
import zombie.util.io.BitHeader.HeaderSize;

public final class BitHeader {
   private static final ConcurrentLinkedDeque<BitHeaderByte> pool_byte = new ConcurrentLinkedDeque<>();
   private static final ConcurrentLinkedDeque<BitHeaderShort> pool_short = new ConcurrentLinkedDeque<>();
   private static final ConcurrentLinkedDeque<BitHeaderInt> pool_int = new ConcurrentLinkedDeque<>();
   private static final ConcurrentLinkedDeque<BitHeaderLong> pool_long = new ConcurrentLinkedDeque<>();
   public static boolean DEBUG = true;

   private static BitHeaderBase getHeader(HeaderSize var0, ByteBuffer var1, boolean var2) {
      if (var0 == HeaderSize.Byte) {
         BitHeaderByte var6 = pool_byte.poll();
         if (var6 == null) {
            var6 = new BitHeaderByte();
         }

         var6.setBuffer(var1);
         var6.setWrite(var2);
         return var6;
      } else if (var0 == HeaderSize.Short) {
         BitHeaderShort var5 = pool_short.poll();
         if (var5 == null) {
            var5 = new BitHeaderShort();
         }

         var5.setBuffer(var1);
         var5.setWrite(var2);
         return var5;
      } else if (var0 == HeaderSize.Integer) {
         BitHeaderInt var4 = pool_int.poll();
         if (var4 == null) {
            var4 = new BitHeaderInt();
         }

         var4.setBuffer(var1);
         var4.setWrite(var2);
         return var4;
      } else if (var0 == HeaderSize.Long) {
         BitHeaderLong var3 = pool_long.poll();
         if (var3 == null) {
            var3 = new BitHeaderLong();
         }

         var3.setBuffer(var1);
         var3.setWrite(var2);
         return var3;
      } else {
         return null;
      }
   }

   private BitHeader() {
   }

   public static void debug_print() {
      if (DEBUG) {
         DebugLog.log("*********************************************");
         DebugLog.log("ByteHeader = " + pool_byte.size());
         DebugLog.log("ShortHeader = " + pool_short.size());
         DebugLog.log("IntHeader = " + pool_int.size());
         DebugLog.log("LongHeader = " + pool_long.size());
      }
   }

   public static BitHeaderWrite allocWrite(HeaderSize var0, ByteBuffer var1) {
      return allocWrite(var0, var1, false);
   }

   public static BitHeaderWrite allocWrite(HeaderSize var0, ByteBuffer var1, boolean var2) {
      BitHeaderBase var3 = getHeader(var0, var1, true);
      if (!var2) {
         var3.create();
      }

      return var3;
   }

   public static BitHeaderRead allocRead(HeaderSize var0, ByteBuffer var1) {
      return allocRead(var0, var1, false);
   }

   public static BitHeaderRead allocRead(HeaderSize var0, ByteBuffer var1, boolean var2) {
      BitHeaderBase var3 = getHeader(var0, var1, false);
      if (!var2) {
         var3.read();
      }

      return var3;
   }
}
