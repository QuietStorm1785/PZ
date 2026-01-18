#include "zombie/characters/action/IActionCondition.h"

namespace zombie {
namespace characters {
namespace action {

std::string IActionCondition::getDescription() {
 // TODO: Implement getDescription
 return "";
}

bool IActionCondition::passes(ActionContext var1, int var2) {
 // TODO: Implement passes
 return false;
}

IActionCondition IActionCondition::clone() {
 // TODO: Implement clone
 return nullptr;
}

IActionCondition IActionCondition::createInstance(Element element) {
 // TODO: Implement createInstance
 return nullptr;
}

void IActionCondition::registerFactory(const std::string& string, IActionCondition.IFactory iFactory) {
 // TODO: Implement registerFactory
}

IActionCondition IActionCondition::create(Element var1) {
 // TODO: Implement create
 return nullptr;
}

} // namespace action
} // namespace characters
} // namespace zombie
