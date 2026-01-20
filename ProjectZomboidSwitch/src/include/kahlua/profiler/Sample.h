#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace profiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Sample {
public:
private
 List<StacktraceElement> list;
 const long time;

public
 Sample(List<StacktraceElement> listx, long long0) {
 this->list = listx;
 this->time = long0;
 }

public
 List<StacktraceElement> getList() { return this->list; }

 long getTime() { return this->time; }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
