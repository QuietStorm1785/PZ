#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace core {
namespace math {


class PZMath {
public:
   private PZMath$UnitTests$lerpFunctions() {
   }

    static void run() {
      DebugLog.General.println("UnitTest_lerpFunctions");
      DebugLog.General.println("x,Sqrt,EaseOutQuad,EaseInQuad,EaseOutInQuad");

      for (int var0 = 0; var0 < 100; var0++) {
    float var1 = var0 / 100.0F;
         DebugLog.General
            .println("%f,%f,%f,%f", var1, PZMath.lerpFunc_EaseOutQuad(var1), PZMath.lerpFunc_EaseInQuad(var1), PZMath.lerpFunc_EaseOutInQuad(var1));
      }

      DebugLog.General.println("UnitTest_lerpFunctions. Complete");
   }
}
} // namespace math
} // namespace core
} // namespace zombie
