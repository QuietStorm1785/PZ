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

class AnimatorDebugMonitor {
public:
    std::string name;
    float blendDelta;
    bool active;
    bool updated;

   private AnimatorDebugMonitor$MonitoredTrack(AnimatorDebugMonitor var1) {
      this.this$0 = var1;
      this.name = "";
      this.active = false;
      this.updated = false;
   }
}
} // namespace debug
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
