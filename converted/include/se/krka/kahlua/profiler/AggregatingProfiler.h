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

class AggregatingProfiler {
public:
 const StacktraceCounter root = new StacktraceCounter();

 public synchronized void getSample(Sample sample) {
 this->root.addTime(sample.getTime());
 StacktraceCounter stacktraceCounter0 = this->root;

 for (int int0 = sample.getList().size() - 1; int0 >= 0; int0--) {
 StacktraceElement stacktraceElement = sample.getList().get(int0);
 StacktraceCounter stacktraceCounter1 = stacktraceCounter0.getOrCreateChild(stacktraceElement);
 stacktraceCounter1.addTime(sample.getTime());
 stacktraceCounter0 = stacktraceCounter1;
 }
 }

 StacktraceNode toTree(int int0, double double0, int int1) {
 return StacktraceNode.createFrom(this->root, new FakeStacktraceElement("Root", "root"), int0, double0, int1);
 }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
