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


class EventOccurred {
public:
    IActionCondition create(Element var1) {
    EventOccurred var2 = std::make_shared<EventOccurred>();
      return var2.load(var1) ? var2 : nullptr;
   }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
