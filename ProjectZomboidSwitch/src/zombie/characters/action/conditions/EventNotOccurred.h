#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/IActionCondition.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {


class EventNotOccurred {
public:
    std::string eventName;

    std::string getDescription() {
      return "EventNotOccurred(" + this.eventName + ")";
   }

    bool load(Element var1) {
      this.eventName = var1.getTextContent().toLowerCase();
    return true;
   }

    bool passes(ActionContext var1, int var2) {
      return !var1.hasEventOccurred(this.eventName, var2);
   }

    IActionCondition clone() {
    return nullptr;
   }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
