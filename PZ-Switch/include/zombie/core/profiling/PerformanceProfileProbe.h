#pragma once
#include "zombie/GameProfiler.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace profiling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PerformanceProfileProbe : public AbstractPerformanceProfileProbe {
public:
private
 Stack<GameProfiler.ProfileArea> m_currentArea =
 std::make_unique<Stack<>>();

public
 PerformanceProfileProbe(std::string_view name) { super(name); }

public
 PerformanceProfileProbe(std::string_view name, bool isEnabled) {
 super(name);
 this->setEnabled(isEnabled);
 }

 void onStart() {
 this->m_currentArea.push(GameProfiler.getInstance().start(this->Name);
 }

 void onEnd() { GameProfiler.getInstance().end(this->m_currentArea.pop()); }
}
} // namespace profiling
} // namespace core
} // namespace zombie
