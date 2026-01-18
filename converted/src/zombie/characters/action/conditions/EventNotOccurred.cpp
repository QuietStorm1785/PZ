#include "zombie/characters/action/conditions/EventNotOccurred.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {

std::string EventNotOccurred::getDescription() {
 // TODO: Implement getDescription
 return "";
}

bool EventNotOccurred::load(Element element) {
 // TODO: Implement load
 return false;
}

bool EventNotOccurred::passes(ActionContext actionContext, int int0) {
 // TODO: Implement passes
 return false;
}

IActionCondition EventNotOccurred::clone() {
 // TODO: Implement clone
 return nullptr;
}

IActionCondition EventNotOccurred::create(Element element) {
 // TODO: Implement create
 return nullptr;
}

} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
