#include "zombie/ai/states/CloseWindowState.h"

namespace zombie {
namespace ai {
namespace states {

CloseWindowState CloseWindowState::instance() {
  // TODO: Implement instance
  return nullptr;
}

void CloseWindowState::enter(IsoGameCharacter owner) {
  // TODO: Implement enter
}

void CloseWindowState::execute(IsoGameCharacter owner) {
  // TODO: Implement execute
}

void CloseWindowState::exit(IsoGameCharacter owner) {
  // TODO: Implement exit
}

void CloseWindowState::animEvent(IsoGameCharacter owner, AnimEvent event) {
  // TODO: Implement animEvent
}

bool CloseWindowState::isDoingActionThatCanBeCancelled() {
  // TODO: Implement isDoingActionThatCanBeCancelled
  return false;
}

void CloseWindowState::onAttemptFinished(IsoGameCharacter character,
                                         IsoWindow window) {
  // TODO: Implement onAttemptFinished
}

void CloseWindowState::onSuccess(IsoGameCharacter character, IsoWindow window) {
  // TODO: Implement onSuccess
}

void CloseWindowState::exert(IsoGameCharacter character) {
  // TODO: Implement exert
}

IsoWindow CloseWindowState::getWindow(IsoGameCharacter owner) {
  // TODO: Implement getWindow
  return nullptr;
}

} // namespace states
} // namespace ai
} // namespace zombie
