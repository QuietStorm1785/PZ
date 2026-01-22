#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace core {
namespace math {


class PZMath {
public:
    static void run() {
      runUnitTest_direction();
   }

    static void runUnitTest_direction() {
      DebugLog.General.println("runUnitTest_direction");
      DebugLog.General.println("x, y, angle, length, rdir.x, rdir.y, rangle, rlength, pass");
      checkDirection(1.0F, 0.0F);
      checkDirection(1.0F, 1.0F);
      checkDirection(0.0F, 1.0F);
      checkDirection(-1.0F, 1.0F);
      checkDirection(-1.0F, 0.0F);
      checkDirection(-1.0F, -1.0F);
      checkDirection(0.0F, -1.0F);
      checkDirection(1.0F, -1.0F);
      DebugLog.General.println("runUnitTest_direction. Complete");
   }

    static void checkDirection(float var0, float var1) {
    Vector2 var2 = std::make_shared<Vector2>(var0, var1);
    float var3 = var2.getDirection();
    float var4 = var2.getLength();
    Vector2 var5 = Vector2.fromLengthDirection(var4, var3);
    float var6 = var5.getDirection();
    float var7 = var5.getLength();
      boolean var8 = PZMath.equal(var2.x, var5.x, 1.0E-4F)
         && PZMath.equal(var2.y, var5.y, 1.0E-4F)
         && PZMath.equal(var3, var6, 1.0E-4F)
         && PZMath.equal(var4, var7, 1.0E-4F);
      DebugLog.General.println("%f, %f, %f, %f, %f, %f, %f, %f, %s", var0, var1, var3, var4, var5.x, var5.y, var6, var7, var8 ? "true" : "false");
   }
}
} // namespace math
} // namespace core
} // namespace zombie
