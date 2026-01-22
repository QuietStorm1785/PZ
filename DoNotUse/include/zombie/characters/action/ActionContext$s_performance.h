#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {
namespace characters {
namespace action {


class ActionContext {
public:
    static const PerformanceProfileProbe update = std::make_shared<PerformanceProfileProbe>("ActionContext.update");
    static const PerformanceProfileProbe evaluateCurrentStateTransitions = std::make_shared<PerformanceProfileProbe>("ActionContext.evaluateCurrentStateTransitions");
    static const PerformanceProfileProbe evaluateSubStateTransitions = std::make_shared<PerformanceProfileProbe>("ActionContext.evaluateSubStateTransitions");

   private ActionContext$s_performance() {
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
