#include <string>
#include "zombie\characters\action\conditions/EventNotOccurred.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {

std::string EventNotOccurred::getDescription() {
    // TODO: Implement getDescription
    return "";
}

bool EventNotOccurred::load(Element var1) {
    // TODO: Implement load
    return false;
}

bool EventNotOccurred::passes(ActionContext var1, int var2) {
    // TODO: Implement passes
    return false;
}

IActionCondition EventNotOccurred::clone() {
    // TODO: Implement clone
    return nullptr;
}

} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
