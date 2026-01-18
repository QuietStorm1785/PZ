#include "zombie/characters/action/ActionContextEvents.h"

namespace zombie {
namespace characters {
namespace action {

void ActionContextEvents::add(const std::string &name, int layer) {
  // TODO: Implement add
}

bool ActionContextEvents::contains(const std::string &name, int layer) {
  // TODO: Implement contains
  return false;
}

bool ActionContextEvents::contains(const std::string &name, int layer,
                                   bool bAgnosticLayer) {
  // TODO: Implement contains
  return false;
}

void ActionContextEvents::clear() {
  // TODO: Implement clear
}

void ActionContextEvents::clearEvent(const std::string &name) {
  // TODO: Implement clearEvent
}

void ActionContextEvents::releaseEvent(ActionContextEvents.Event event1,
                                       ActionContextEvents.Event event0) {
  // TODO: Implement releaseEvent
}

} // namespace action
} // namespace characters
} // namespace zombie
