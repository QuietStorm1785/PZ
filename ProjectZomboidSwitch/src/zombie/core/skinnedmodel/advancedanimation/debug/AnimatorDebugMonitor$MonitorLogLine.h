#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/LogType.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
namespace debug {


class AnimatorDebugMonitor {
public:
    std::string line;
    Color color;
    LogType type;
    int tick;

   private AnimatorDebugMonitor$MonitorLogLine(AnimatorDebugMonitor var1) {
      this.this$0 = var1;
      this.color = nullptr;
      this.type = LogType.DEFAULT;
   }
}
} // namespace debug
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
