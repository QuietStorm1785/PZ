package zombie.core.skinnedmodel;

import org.lwjgl.util.vector.Matrix4f;
import org.lwjgl.util.vector.Quaternion;
import org.lwjgl.util.vector.Vector4f;
import zombie.core.math.PZMath;
import zombie.debug.DebugLog;

final class HelperFunctions$UnitTests$getRotationMatrix {
   private HelperFunctions$UnitTests$getRotationMatrix() {
   }

   public static void run() {
      DebugLog.UnitTests.println("UnitTest_getRotationMatrix");
      DebugLog.UnitTests.println("q.x, q.y, q.z, q.w, q_out.x, q_out.y, q_out.z, q_out.w");
      Quaternion var0 = new Quaternion();
      Vector4f var1 = new Vector4f();
      Matrix4f var2 = new Matrix4f();
      Quaternion var3 = new Quaternion();
      Quaternion var4 = new Quaternion();

      for (byte var5 = 0; var5 < 360; var5 += 10) {
         float var6 = PZMath.wrap(var5, -180.0F, 180.0F);
         var1.set(1.0F, 0.0F, 0.0F, var6 * (float) (Math.PI / 180.0));
         var0.setFromAxisAngle(var1);
         HelperFunctions.CreateFromQuaternion(var0, var2);
         HelperFunctions.getRotation(var2, var3);
         var4.set(-var3.x, -var3.y, -var3.z, -var3.w);
         boolean var7 = PZMath.equal(var0.x, var3.x, 0.01F)
               && PZMath.equal(var0.y, var3.y, 0.01F)
               && PZMath.equal(var0.z, var3.z, 0.01F)
               && PZMath.equal(var0.w, var3.w, 0.01F)
            || PZMath.equal(var0.x, var4.x, 0.01F)
               && PZMath.equal(var0.y, var4.y, 0.01F)
               && PZMath.equal(var0.z, var4.z, 0.01F)
               && PZMath.equal(var0.w, var4.w, 0.01F);
         DebugLog.UnitTests.printUnitTest("%f,%f,%f,%f, %f,%f,%f,%f", var7, new Object[]{var0.x, var0.y, var0.z, var0.w, var3.x, var3.y, var3.z, var3.w});
      }

      DebugLog.UnitTests.println("UnitTest_getRotationMatrix. Complete");
   }
}
