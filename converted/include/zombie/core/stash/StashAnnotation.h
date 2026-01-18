#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace stash {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class StashAnnotation {
public:
 std::string symbol;
 std::string text;
 float x;
 float y;
 float r;
 float g;
 float b;

 void fromLua(KahluaTable table) {
 KahluaTableImpl kahluaTableImpl = (KahluaTableImpl)table;
 this->symbol = Type.tryCastTo(table.rawget("symbol"), String.class);
 this->text = Type.tryCastTo(table.rawget("text"), String.class);
 this->x = kahluaTableImpl.rawgetFloat("x");
 this->y = kahluaTableImpl.rawgetFloat("y");
 this->r = kahluaTableImpl.rawgetFloat("r");
 this->g = kahluaTableImpl.rawgetFloat("g");
 this->b = kahluaTableImpl.rawgetFloat("b");
 }
}
} // namespace stash
} // namespace core
} // namespace zombie
