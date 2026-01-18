#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"

namespace se {
namespace krka {
namespace kahlua {
namespace profiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class JavaStacktraceElement {
public:
 const JavaFunction javaFunction;

 public JavaStacktraceElement(JavaFunction javaFunctionx) {
 this->javaFunction = javaFunctionx;
 }

 std::string name() {
 return this->javaFunction.toString();
 }

 std::string type() {
 return "java";
 }

 bool equals(void* object) {
 if (this == object) {
 return true;
 } else {
 return !(object instanceof JavaStacktraceElement javaStacktraceElement1) ? false : this->javaFunction == javaStacktraceElement1.javaFunction;
 }
 }

 int hashCode() {
 return this->javaFunction.hashCode();
 }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
