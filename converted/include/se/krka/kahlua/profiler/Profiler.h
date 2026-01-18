#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace se {
namespace krka {
namespace kahlua {
namespace profiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Profiler {
public:
 virtual ~Profiler() = default;
 void getSample(Sample var1);
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
