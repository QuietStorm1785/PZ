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


class BufferedProfiler {
public:
 private List<Sample> buffer = std::make_unique<ArrayList<>>();

 void getSample(Sample sample) {
 this->buffer.add(sample);
 }

 void sendTo(Profiler profiler) {
 for (Sample sample : this->buffer) {
 profiler.getSample(sample);
 }
 }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
