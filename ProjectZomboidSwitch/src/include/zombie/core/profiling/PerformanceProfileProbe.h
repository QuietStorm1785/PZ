#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfiler.h"
#include "zombie/GameProfiler/ProfileArea.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace profiling {


class PerformanceProfileProbe : public AbstractPerformanceProfileProbe {
public:
   private const std::stack<ProfileArea> m_currentArea = std::make_unique<std::stack<>>();

    public PerformanceProfileProbe(const std::string& var1) {
      super(var1);
   }

    public PerformanceProfileProbe(const std::string& var1, bool var2) {
      super(var1);
      this.setEnabled(var2);
   }

    void onStart() {
      this.m_currentArea.push(GameProfiler.getInstance().start(this.Name));
   }

    void onEnd() {
      GameProfiler.getInstance().end(this.m_currentArea.pop());
   }
}
} // namespace profiling
} // namespace core
} // namespace zombie
