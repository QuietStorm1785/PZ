#pragma once
#include "zombie/GameProfiler.h"
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

class PerformanceProfileFrameProbe : public PerformanceProfileProbe {
public:
public
 PerformanceProfileFrameProbe(std::string_view string) { super(string); }

 void onStart() {
 GameProfiler.getInstance().startFrame(this->Name);
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
