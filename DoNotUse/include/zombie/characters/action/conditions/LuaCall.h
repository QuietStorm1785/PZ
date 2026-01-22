#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/IActionCondition.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {


class LuaCall {
public:
    std::string getDescription() {
      return "<luaCheck>";
   }

    bool passes(ActionContext var1, int var2) {
    return false;
   }

    IActionCondition clone() {
      return std::make_unique<LuaCall>();
   }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
