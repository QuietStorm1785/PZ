#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfiler.h"

namespace zombie {
namespace core {
namespace profiling {


class PerformanceProfileFrameProbe : public PerformanceProfileProbe {
public:
    public PerformanceProfileFrameProbe(const std::string& var1) {
      super(var1);
   }

    void onStart() {
      GameProfiler.getInstance().startFrame(this.Name);
      super.onStart();
   }

    void onEnd() {
      super.onEnd();
      GameProfiler.getInstance().endFrame();
   }
}
} // namespace profiling
} // namespace core
} // namespace zombie
