#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfiler.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace profiling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PerformanceProfileProbe : public AbstractPerformanceProfileProbe {
public:
 private Stack<GameProfiler.ProfileArea> m_currentArea = std::make_unique<Stack<>>();

 public PerformanceProfileProbe(const std::string& name) {
 super(name);
 }

 public PerformanceProfileProbe(const std::string& name, bool isEnabled) {
 super(name);
 this->setEnabled(isEnabled);
 }

 void onStart() {
 this->m_currentArea.push(GameProfiler.getInstance().start(this->Name);
 }

 void onEnd() {
 GameProfiler.getInstance().end(this->m_currentArea.pop());
 }
}
} // namespace profiling
} // namespace core
} // namespace zombie
