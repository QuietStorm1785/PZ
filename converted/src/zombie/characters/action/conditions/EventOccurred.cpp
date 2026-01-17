#include "zombie/characters/action/conditions/EventOccurred.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {

std::string EventOccurred::getDescription() {
  // TODO: Implement getDescription
  return "";
}

bool EventOccurred::load(Element element) {
  // TODO: Implement load
  return false;
}

bool EventOccurred::passes(ActionContext actionContext, int int0) {
  // TODO: Implement passes
  return false;
}

IActionCondition EventOccurred::clone() {
  // TODO: Implement clone
  return nullptr;
}

IActionCondition EventOccurred::create(Element element) {
  // TODO: Implement create
  return nullptr;
}

} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
