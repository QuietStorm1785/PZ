#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
namespace debug {

enum class AnimatorDebugMonitor {
   DEFAULT(0),
   LAYER(1),
   NODE(2),
   TRACK(3),
   VAR(4),
   MAX(5);

    const int val;

   private AnimatorDebugMonitor$LogType(int var3) {
      this.val = var3;
   }

    int value() {
      return this.val;
   }
}
} // namespace debug
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
