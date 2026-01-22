#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/characters/action/IActionCondition.h"
#include "zombie/characters/action/IActionCondition/IFactory.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {


class LuaCall {
public:
    IActionCondition create(Element var1) {
      return std::make_unique<LuaCall>();
   }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
