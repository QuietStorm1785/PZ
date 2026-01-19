package zombie.Lua;

final class KahluaNumberConverter$DoubleCache {
   static final int low = -128;
   static final int high = 10000;
   static final Double[] cache = new Double[10129];

   private KahluaNumberConverter$DoubleCache() {
   }

   public static Double valueOf(double var0) {
      return var0 == (int)var0 && var0 >= -128.0 && var0 <= 10000.0 ? cache[(int)(var0 + 128.0)] : new Double(var0);
   }

   static {
      int var0 = -128;

      for (int var1 = 0; var1 < cache.length; var1++) {
         cache[var1] = new Double(var0++);
      }
   }
}
