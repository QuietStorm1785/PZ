#include <string>
#include "zombie\characters\action/ActionContextEvents.h"

namespace zombie {
namespace characters {
namespace action {

void ActionContextEvents::add(const std::string& var1, int var2) {
    // TODO: Implement add
}

bool ActionContextEvents::contains(const std::string& var1, int var2) {
    // TODO: Implement contains
    return false;
}

bool ActionContextEvents::contains(const std::string& var1, int var2, bool var3) {
    // TODO: Implement contains
    return false;
}

void ActionContextEvents::clear() {
    // TODO: Implement clear
}

void ActionContextEvents::clearEvent(const std::string& var1) {
    // TODO: Implement clearEvent
}

Event ActionContextEvents::allocEvent() {
    // TODO: Implement allocEvent
    return nullptr;
}

void ActionContextEvents::releaseEvent(Event var1, Event var2) {
    // TODO: Implement releaseEvent
}

} // namespace action
} // namespace characters
} // namespace zombie
