#include "zombie/ai/State.h"

namespace zombie {
namespace ai {

void State::enter(IsoGameCharacter owner) {
  // TODO: Implement enter
}

void State::execute(IsoGameCharacter owner) {
  // TODO: Implement execute
}

void State::exit(IsoGameCharacter owner) {
  // TODO: Implement exit
}

void State::animEvent(IsoGameCharacter owner, AnimEvent event) {
  // TODO: Implement animEvent
}

bool State::isAttacking(IsoGameCharacter owner) {
  // TODO: Implement isAttacking
  return false;
}

bool State::isMoving(IsoGameCharacter owner) {
  // TODO: Implement isMoving
  return false;
}

bool State::isDoingActionThatCanBeCancelled() {
  // TODO: Implement isDoingActionThatCanBeCancelled
  return false;
}

void State::getDeltaModifiers(IsoGameCharacter owner,
                              MoveDeltaModifiers modifiers) {
  // TODO: Implement getDeltaModifiers
}

bool State::isIgnoreCollide(IsoGameCharacter owner, int fromX, int fromY,
                            int fromZ, int toX, int toY, int toZ) {
  // TODO: Implement isIgnoreCollide
  return false;
}

std::string State::getName() {
  // TODO: Implement getName
  return "";
}

IStatePermissions State::getStatePermissions() {
  // TODO: Implement getStatePermissions
  return nullptr;
}

} // namespace ai
} // namespace zombie
