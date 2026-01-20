#pragma once
#include "se/krka/kahlua/integration/annotations/LuaMethod.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include <cstdint>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IterableExposer {
public:
 global = true
 )
 void* iter(Iterable<?> iterable) {
 const Iterator iterator = iterable.iterator();
 return std::make_unique<JavaFunction>(){int call(
 LuaCallFrame luaCallFrame, int var2){
 return !iterator.hasNext() ? 0
 : luaCallFrame.push(iterator.next());
 }
};
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
} // namespace krka
} // namespace se
