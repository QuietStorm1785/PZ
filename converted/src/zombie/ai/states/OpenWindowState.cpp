#include "zombie/ai/states/OpenWindowState.h"

namespace zombie {
namespace ai {
namespace states {

OpenWindowState OpenWindowState::instance() {
  // TODO: Implement instance
  return nullptr;
}

void OpenWindowState::enter(IsoGameCharacter owner) {
  // TODO: Implement enter
}

void OpenWindowState::execute(IsoGameCharacter owner) {
  // TODO: Implement execute
}

void OpenWindowState::exit(IsoGameCharacter owner) {
  // TODO: Implement exit
}

void OpenWindowState::animEvent(IsoGameCharacter owner, AnimEvent event) {
  // TODO: Implement animEvent
}

bool OpenWindowState::isDoingActionThatCanBeCancelled() {
  // TODO: Implement isDoingActionThatCanBeCancelled
  return false;
}

void OpenWindowState::onAttemptFinished(IsoGameCharacter character,
                                        IsoWindow window) {
  // TODO: Implement onAttemptFinished
}

void OpenWindowState::onSuccess(IsoGameCharacter character, IsoWindow window) {
  // TODO: Implement onSuccess
}

void OpenWindowState::exert(IsoGameCharacter character) {
  // TODO: Implement exert
}

void OpenWindowState::slideX(IsoGameCharacter character, float float1) {
  // TODO: Implement slideX
}

void OpenWindowState::slideY(IsoGameCharacter character, float float1) {
  // TODO: Implement slideY
}

void OpenWindowState::setParams(IsoGameCharacter owner, IsoWindow window) {
  // TODO: Implement setParams
}

} // namespace states
} // namespace ai
} // namespace zombie
