package zombie.core;

public class FastTrig {
   public static double cos(double var0) {
      return sin(var0 + (Math.PI / 2));
   }

   public static double sin(double var0) {
      var0 = reduceSinAngle(var0);
      return Math.abs(var0) <= Math.PI / 4 ? Math.sin(var0) : Math.cos((Math.PI / 2) - var0);
   }

   private static double reduceSinAngle(double var0) {
      var0 %= Math.PI * 2;
      if (Math.abs(var0) > Math.PI) {
         var0 -= Math.PI * 2;
      }

      if (Math.abs(var0) > Math.PI / 2) {
         var0 = Math.PI - var0;
      }

      return var0;
   }
}
