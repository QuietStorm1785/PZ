#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "org/lwjgl/util/vector/Vector4f.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class HelperFunctions {
public:
   private HelperFunctions$UnitTests$transformQuaternion() {
   }

    static void run() {
      DebugLog.UnitTests.println("UnitTest_transformQuaternion");
      DebugLog.UnitTests.println("roll, pitch, yaw, out.x, out.y, out.z, cout.x, cout.y, cout.z, result");
    Quaternion var0 = std::make_shared<Quaternion>();
    std::make_shared<Vector3f>();
    std::make_shared<Vector3f>();
    Vector3f var3 = std::make_shared<Vector3f>();
    Vector3f var4 = std::make_shared<Vector3f>();
    Matrix4f var5 = std::make_shared<Matrix4f>();
    Vector4f var6 = std::make_shared<Vector4f>();
    Vector4f var7 = std::make_shared<Vector4f>();
    Vector3f var8 = std::make_shared<Vector3f>(1.0F, 0.0F, 0.0F);
    Vector3f var9 = std::make_shared<Vector3f>(0.0F, 1.0F, 0.0F);
    Vector3f var10 = std::make_shared<Vector3f>(0.0F, 0.0F, 1.0F);
      runTest(0.0F, 0.0F, 90.0F, var0, var3, var4, var5, var6, var7, var8, var9, var10);
      runTest(0.0F, 0.0F, 5.0F, var0, var3, var4, var5, var6, var7, var8, var9, var10);

      for (int var11 = 0; var11 < 10; var11++) {
    float var12 = PZMath.wrap(var11 / 10.0F * 360.0F, -180.0F, 180.0F);

         for (int var13 = 0; var13 < 10; var13++) {
    float var14 = PZMath.wrap(var13 / 10.0F * 360.0F, -180.0F, 180.0F);

            for (int var15 = 0; var15 < 10; var15++) {
    float var16 = PZMath.wrap(var15 / 10.0F * 360.0F, -180.0F, 180.0F);
               runTest(var12, var14, var16, var0, var3, var4, var5, var6, var7, var8, var9, var10);
            }
         }
      }

      DebugLog.UnitTests.println("UnitTest_transformQuaternion. Complete");
   }

   public static void runTest(
      float var0,
      float var1,
      float var2,
      Quaternion var3,
      Vector3f var4,
      Vector3f var5,
      Matrix4f var6,
      Vector4f var7,
      Vector4f var8,
      Vector3f var9,
      Vector3f var10,
      Vector3f var11
   ) {
    Vector3f var12 = std::make_shared<Vector3f>(15.0F, 0.0F, 0.0F);
      var6.setIdentity();
      var6.translate(var12);
      var6.rotate(var0 * (float) (Math.PI / 180.0), var9);
      var6.rotate(var1 * (float) (Math.PI / 180.0), var10);
      var6.rotate(var2 * (float) (Math.PI / 180.0), var11);
      HelperFunctions.getRotation(var6, var3);
      var4.set(1.0F, 0.0F, 0.0F);
      var7.set(var4.x, var4.y, var4.z, 1.0F);
      HelperFunctions.transform(var6, var7, var8);
      HelperFunctions.transform(var3, var4, var5);
      var5.x = var5.x + var12.x;
      var5.y = var5.y + var12.y;
      var5.z = var5.z + var12.z;
    bool var13 = PZMath.equal(var5.x, var8.x, 0.01F) && PZMath.equal(var5.y, var8.y, 0.01F) && PZMath.equal(var5.z, var8.z, 0.01F);
      DebugLog.UnitTests.printUnitTest("%f,%f,%f,%f,%f,%f,%f,%f,%f", var13, new Object[]{var0, var1, var2, var5.x, var5.y, var5.z, var8.x, var8.y, var8.z});
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
