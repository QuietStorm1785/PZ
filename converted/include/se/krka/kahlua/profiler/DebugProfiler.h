#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace profiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DebugProfiler {
public:
 PrintWriter output;

 public DebugProfiler(Writer writer) {
 this->output = new PrintWriter(writer);
 }

 public synchronized void getSample(Sample sample) {
 this->output.println("Sample: " + sample.getTime() + " ms");

 for (StacktraceElement stacktraceElement : sample.getList()) {
 this->output.println("\t" + stacktraceElement.name() + "\t" + stacktraceElement.type() + "\t" + stacktraceElement.hashCode());
 }
 }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
