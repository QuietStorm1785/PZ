#include "zombie/ai/states/ClimbOverWallState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbOverWallState ClimbOverWallState::instance() {
  // TODO: Implement instance
  return nullptr;
}

void ClimbOverWallState::enter(IsoGameCharacter owner) {
  // TODO: Implement enter
}

void ClimbOverWallState::execute(IsoGameCharacter owner) {
  // TODO: Implement execute
}

void ClimbOverWallState::exit(IsoGameCharacter owner) {
  // TODO: Implement exit
}

void ClimbOverWallState::animEvent(IsoGameCharacter owner, AnimEvent event) {
  // TODO: Implement animEvent
}

bool ClimbOverWallState::isIgnoreCollide(IsoGameCharacter owner, int fromX,
                                         int fromY, int fromZ, int toX, int toY,
                                         int toZ) {
  // TODO: Implement isIgnoreCollide
  return false;
}

IsoObject ClimbOverWallState::getClimbableWallN(IsoGridSquare square) {
  // TODO: Implement getClimbableWallN
  return nullptr;
}

IsoObject ClimbOverWallState::getClimbableWallW(IsoGridSquare square) {
  // TODO: Implement getClimbableWallW
  return nullptr;
}

IsoObject ClimbOverWallState::getFence(IsoGameCharacter character) {
  // TODO: Implement getFence
  return nullptr;
}

return ClimbOverWallState::switch () {
  // TODO: Implement switch
  return nullptr;
}

int ClimbOverWallState::getFenceType(IsoObject object) {
  // TODO: Implement getFenceType
  return 0;
}

return ClimbOverWallState::switch () {
  // TODO: Implement switch
  return nullptr;
}

void ClimbOverWallState::setParams(IsoGameCharacter owner, IsoDirections dir) {
  // TODO: Implement setParams
}

} // namespace states
} // namespace ai
} // namespace zombie
