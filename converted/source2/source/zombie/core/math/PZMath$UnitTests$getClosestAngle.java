package zombie.core.math;

import zombie.debug.DebugLog;

final class PZMath$UnitTests$getClosestAngle {
   private PZMath$UnitTests$getClosestAngle() {
   }

   public static void run() {
      DebugLog.General.println("runUnitTests_getClosestAngle");
      DebugLog.General.println("a, b, result, expected, pass");
      runUnitTest(0.0F, 0.0F, 0.0F);
      runUnitTest(0.0F, 15.0F, 15.0F);
      runUnitTest(15.0F, 0.0F, -15.0F);
      runUnitTest(0.0F, 179.0F, 179.0F);
      runUnitTest(180.0F, 180.0F, 0.0F);
      runUnitTest(180.0F, 359.0F, 179.0F);
      runUnitTest(90.0F, 180.0F, 90.0F);
      runUnitTest(180.0F, 90.0F, -90.0F);

      for (short var0 = -360; var0 < 360; var0 += 10) {
         for (short var1 = -360; var1 < 360; var1 += 10) {
            float var2 = var0;
            float var3 = var1;
            runUnitTest_noexp(var2, var3);
         }
      }

      DebugLog.General.println("runUnitTests_getClosestAngle. Complete");
   }

   private static void runUnitTest_noexp(float var0, float var1) {
      float var2 = PZMath.getClosestAngleDegrees(var0, var1);
      logResult(var0, var1, var2, "N/A", "N/A");
   }

   private static void runUnitTest(float var0, float var1, float var2) {
      float var3 = PZMath.getClosestAngleDegrees(var0, var1);
      boolean var4 = PZMath.equal(var2, var3, 1.0E-4F);
      String var5 = var4 ? "pass" : "fail";
      logResult(var0, var1, var3, String.valueOf(var2), var5);
   }

   private static void logResult(float var0, float var1, float var2, String var3, String var4) {
      DebugLog.General.println("%f, %f, %f, %s, %s", var0, var1, var2, var3, var4);
   }
}
