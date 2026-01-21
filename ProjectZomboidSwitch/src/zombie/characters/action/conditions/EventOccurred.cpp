#include <string>
#include "zombie/characters/action/conditions/EventOccurred.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {

std::string EventOccurred::getDescription() {
    // TODO: Implement getDescription
    return "";
}

bool EventOccurred::load(Element var1) {
    // TODO: Implement load
    return false;
}

bool EventOccurred::passes(ActionContext var1, int var2) {
    // TODO: Implement passes
    return false;
}

IActionCondition EventOccurred::clone() {
    // TODO: Implement clone
    return nullptr;
}

} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
