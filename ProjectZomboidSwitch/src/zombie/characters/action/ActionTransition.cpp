#include <string>
#include "zombie/characters/action/ActionTransition.h"

namespace zombie {
namespace characters {
namespace action {

bool ActionTransition::parse(Element var0, const std::string& var1, List<ActionTransition> var2) {
    // TODO: Implement parse
    return false;
}

void ActionTransition::parseTransition(Element var0, List<ActionTransition> var1) {
    // TODO: Implement parseTransition
}

void ActionTransition::parseTransitions(Element var0, const std::string& var1, List<ActionTransition> var2) {
    // TODO: Implement parseTransitions
}

bool ActionTransition::load(Element var1) {
    // TODO: Implement load
    return false;
}

std::string ActionTransition::getTransitionTo() {
    // TODO: Implement getTransitionTo
    return "";
}

bool ActionTransition::passes(ActionContext var1, int var2) {
    // TODO: Implement passes
    return false;
}

ActionTransition ActionTransition::clone() {
    // TODO: Implement clone
    return nullptr;
}

} // namespace action
} // namespace characters
} // namespace zombie
