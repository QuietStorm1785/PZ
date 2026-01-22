#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/MonitoredNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/MonitoredTrack.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
namespace debug {


class AnimatorDebugMonitor {
public:
    int index;
    std::string nodeName;
   std::unordered_map<std::string, MonitoredNode> activeNodes;
   std::unordered_map<std::string, MonitoredTrack> animTracks;
    bool active;
    bool updated;

   public AnimatorDebugMonitor$MonitoredLayer(AnimatorDebugMonitor var1, int var2) {
      this.this$0 = var1;
      this.nodeName = "";
      this.activeNodes = std::make_unique<std::unordered_map<>>();
      this.animTracks = std::make_unique<std::unordered_map<>>();
      this.active = false;
      this.updated = false;
      this.index = var2;
   }
}
} // namespace debug
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
