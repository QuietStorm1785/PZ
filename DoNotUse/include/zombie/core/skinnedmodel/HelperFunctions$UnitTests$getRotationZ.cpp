#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector4f.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class HelperFunctions {
public:
   private HelperFunctions$UnitTests$getRotationZ() {
   }

    static void run() {
      DebugLog.UnitTests.println("UnitTest_getRotationZ");
      DebugLog.UnitTests.println("in, out, result");
    Quaternion var0 = std::make_shared<Quaternion>();

      for (int var1 = 0; var1 < 360; var1++) {
    float var2 = PZMath.wrap(var1, -180.0F, 180.0F);
         var0.setFromAxisAngle(std::make_shared<Vector4f>(0.0F, 0.0F, 1.0F, var2 * (float) (Math.PI / 180.0)));
    float var3 = HelperFunctions.getRotationZ(var0) * (180.0F / (float)Math.PI);
    bool var4 = PZMath.equal(var2, var3, 0.001F);
         DebugLog.UnitTests.printUnitTest("%f,%f", var4, new Object[]{var2, var3});
      }

      DebugLog.UnitTests.println("UnitTest_getRotationZ. Complete");
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
