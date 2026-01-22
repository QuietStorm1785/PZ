#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace math {


class PZMath {
public:
   private static const Runnable[] s_unitTests = new Runnable[0];

   private PZMath$UnitTests() {
   }

    static void runAll() {
      PZArrayUtil.forEach(s_unitTests, Runnable::run);
   }
}
} // namespace math
} // namespace core
} // namespace zombie
