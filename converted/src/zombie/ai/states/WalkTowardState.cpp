#include "zombie/ai/states/WalkTowardState.h"

namespace zombie {
namespace ai {
namespace states {

WalkTowardState WalkTowardState::instance() {
  // TODO: Implement instance
  return nullptr;
}

void WalkTowardState::enter(IsoGameCharacter owner) {
  // TODO: Implement enter
}

void WalkTowardState::execute(IsoGameCharacter owner) {
  // TODO: Implement execute
}

void WalkTowardState::exit(IsoGameCharacter owner) {
  // TODO: Implement exit
}

void WalkTowardState::animEvent(IsoGameCharacter owner, AnimEvent event) {
  // TODO: Implement animEvent
}

bool WalkTowardState::isMoving(IsoGameCharacter owner) {
  // TODO: Implement isMoving
  return false;
}

bool WalkTowardState::isPathClear(IsoGameCharacter character, float float0,
                                  float float1, float float2) {
  // TODO: Implement isPathClear
  return false;
}

bool WalkTowardState::calculateTargetLocation(IsoZombie zomb,
                                              Vector2 location) {
  // TODO: Implement calculateTargetLocation
  return false;
}

} // namespace states
} // namespace ai
} // namespace zombie
