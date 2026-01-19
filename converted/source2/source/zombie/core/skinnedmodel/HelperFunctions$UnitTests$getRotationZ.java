package zombie.core.skinnedmodel;

import org.lwjgl.util.vector.Quaternion;
import org.lwjgl.util.vector.Vector4f;
import zombie.core.math.PZMath;
import zombie.debug.DebugLog;

final class HelperFunctions$UnitTests$getRotationZ {
   private HelperFunctions$UnitTests$getRotationZ() {
   }

   public static void run() {
      DebugLog.UnitTests.println("UnitTest_getRotationZ");
      DebugLog.UnitTests.println("in, out, result");
      Quaternion var0 = new Quaternion();

      for (int var1 = 0; var1 < 360; var1++) {
         float var2 = PZMath.wrap(var1, -180.0F, 180.0F);
         var0.setFromAxisAngle(new Vector4f(0.0F, 0.0F, 1.0F, var2 * (float) (Math.PI / 180.0)));
         float var3 = HelperFunctions.getRotationZ(var0) * (180.0F / (float)Math.PI);
         boolean var4 = PZMath.equal(var2, var3, 0.001F);
         DebugLog.UnitTests.printUnitTest("%f,%f", var4, new Object[]{var2, var3});
      }

      DebugLog.UnitTests.println("UnitTest_getRotationZ. Complete");
   }
}
