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
namespace skinnedmodel {


class HelperFunctions {
public:
   private static const Runnable[] s_unitTests = new Runnable[0];

   private HelperFunctions$UnitTests() {
   }

    static void runAll() {
      PZArrayUtil.forEach(s_unitTests, Runnable::run);
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
