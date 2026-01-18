#pragma once
#include "org/w3c/dom/Element.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/IActionCondition.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace action {
namespace conditions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaCall {
public:
 std::string getDescription() { return "<luaCheck>"; }

 bool passes(ActionContext var1, int var2) { return false; }

 IActionCondition clone() { return std::make_unique<LuaCall>(); }

public
 static class Factory implements IActionCondition.IFactory {
 IActionCondition create(Element var1) {
 return std::make_unique<LuaCall>();
 }
 }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
