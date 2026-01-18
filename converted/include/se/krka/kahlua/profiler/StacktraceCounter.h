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


class StacktraceCounter {
public:
 private Map<StacktraceElement, StacktraceCounter> children = std::make_unique<HashMap<>>();
 long time = 0L;

 void addTime(long long0) {
 this->time += long0;
 }

 StacktraceCounter getOrCreateChild(StacktraceElement stacktraceElement) {
 StacktraceCounter stacktraceCounter0 = this->children.get(stacktraceElement);
 if (stacktraceCounter0 == nullptr) {
 stacktraceCounter0 = std::make_unique<StacktraceCounter>();
 this->children.put(stacktraceElement, stacktraceCounter0);
 }

 return stacktraceCounter0;
 }

 long getTime() {
 return this->time;
 }

 public Map<StacktraceElement, StacktraceCounter> getChildren() {
 return this->children;
 }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
