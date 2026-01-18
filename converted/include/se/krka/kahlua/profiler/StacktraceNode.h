#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace profiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class StacktraceNode {
public:
 const long time;
 const StacktraceElement element;
 private List<StacktraceNode> children;

 public StacktraceNode(StacktraceElement stacktraceElement, List<StacktraceNode> list, long long0) {
 this->element = stacktraceElement;
 this->children = list;
 this->time = long0;
 }

 static StacktraceNode createFrom(StacktraceCounter stacktraceCounter0, StacktraceElement stacktraceElement0, int int0, double double0, int int2) {
 StacktraceNode stacktraceNode0 = new StacktraceNode(stacktraceElement0, new ArrayList<>(), stacktraceCounter0.getTime());
 if (int0 > 0) {
 std::unordered_map map = stacktraceCounter0.getChildren();
 std::vector arrayList = new ArrayList(map.entrySet());
 Collections.sort(arrayList, new Comparator<Entry<StacktraceElement, StacktraceCounter>>() {
 int compare(StacktraceCounter> entry0, StacktraceCounter> entry1) {
 return Long.signum(((StacktraceCounter)entry1.getValue()).getTime() - ((StacktraceCounter)entry0.getValue()).getTime());
 }
 });

 for (int int1 = arrayList.size() - 1; int1 >= int2; int1--) {
 arrayList.remove(int1);
 }

 for (auto& entry : arrayList) StacktraceElement stacktraceElement1 = (StacktraceElement)entry.getKey();
 StacktraceCounter stacktraceCounter1 = (StacktraceCounter)entry.getValue();
 if (stacktraceCounter1.getTime() >= double0 * stacktraceCounter0.getTime()) {
 StacktraceNode stacktraceNode1 = createFrom(stacktraceCounter1, stacktraceElement1, int0 - 1, double0, int2);
 stacktraceNode0.children.add(stacktraceNode1);
 }
 }
 }

 return stacktraceNode0;
 }

 void output(PrintWriter printWriter) {
 this->output(printWriter, "", this->time, this->time);
 }

 void output(PrintWriter printWriter, const std::string& string0, long long1, long long0) {
 printWriter.println(
 String.format(
 "%-40s %4d ms %5.1f%% of parent %5.1f%% of total",
 string0 + this->element.name() + " (" + this->element.type() + ")",
 this->time,
 100.0 * this->time / long1,
 100.0 * this->time / long0
 )
 );
 std::string string1 = string0 + " ";

 for (StacktraceNode stacktraceNode1 : this->children) {
 stacktraceNode1.output(printWriter, string1, this->time, long0);
 }
 }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
