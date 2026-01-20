#pragma once
#include "se/krka/kahlua/vm/Prototype.h"
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

class LuaStacktraceElement {
public:
 const int pc;
 const Prototype prototype;

public
 LuaStacktraceElement(int int0, Prototype prototypex) {
 this->pc = int0;
 this->prototype = prototypex;
 }

 int getLine() {
 return this->pc >= 0 && this->pc < this->prototype.lines.length
 ? this->prototype.lines[this->pc]
 : 0;
 }

 std::string getSource() { return this->prototype.name; }

 bool equals(void *object) {
 if (this == object) {
 return true;
 } else if (!(dynamic_cast<LuaStacktraceElemen*>(object) != nullptrt luaStacktraceElement1) {
 return false;
 } else {
 return this->getLine() != luaStacktraceElement1.getLine() ? false : this->prototype == luaStacktraceElement1.prototype);
 }
 }

 int hashCode() {
 int int0 = this->getLine();
 return 31 * int0 + this->prototype.hashCode();
 }

 std::string toString() { return this->name(); }

 std::string name() { return this->getSource() + ":" + this->getLine(); }

 std::string type() { return "lua"; }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
