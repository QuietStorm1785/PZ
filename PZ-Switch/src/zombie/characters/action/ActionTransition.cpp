#include "zombie/characters/action/ActionTransition.h"

namespace zombie {
namespace characters {
namespace action {

bool ActionTransition::parse(Element element, const std::string &string,
 List<ActionTransition> list) {
 // TODO: Implement parse
 return false;
}

void ActionTransition::parseTransition(Element element,
 List<ActionTransition> list) {
 // TODO: Implement parseTransition
}

void ActionTransition::parseTransitions(Element element,
 const std::string &string,
 List<ActionTransition> list) {
 // TODO: Implement parseTransitions
}

bool ActionTransition::load(Element element) {
 // TODO: Implement load
 return false;
}

std::string ActionTransition::getTransitionTo() {
 // TODO: Implement getTransitionTo
 return "";
}

bool ActionTransition::passes(ActionContext actionContext, int int1) {
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
