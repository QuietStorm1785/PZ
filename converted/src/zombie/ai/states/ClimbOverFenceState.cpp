#include "zombie/ai/states/ClimbOverFenceState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbOverFenceState ClimbOverFenceState::instance() {
 // TODO: Implement instance
 return nullptr;
}

void ClimbOverFenceState::enter(IsoGameCharacter owner) {
 // TODO: Implement enter
}

void ClimbOverFenceState::setLungeXVars(IsoZombie zombie0) {
 // TODO: Implement setLungeXVars
}

void ClimbOverFenceState::execute(IsoGameCharacter owner) {
 // TODO: Implement execute
}

void ClimbOverFenceState::exit(IsoGameCharacter owner) {
 // TODO: Implement exit
}

void ClimbOverFenceState::animEvent(IsoGameCharacter owner, AnimEvent event) {
 // TODO: Implement animEvent
}

void ClimbOverFenceState::getDeltaModifiers(IsoGameCharacter owner, MoveDeltaModifiers modifiers) {
 // TODO: Implement getDeltaModifiers
}

bool ClimbOverFenceState::isIgnoreCollide(IsoGameCharacter owner, int fromX, int fromY, int fromZ, int toX, int toY, int toZ) {
 // TODO: Implement isIgnoreCollide
 return false;
}

void ClimbOverFenceState::slideX(IsoGameCharacter character, float float1) {
 // TODO: Implement slideX
}

void ClimbOverFenceState::slideY(IsoGameCharacter character, float float1) {
 // TODO: Implement slideY
}

IsoObject ClimbOverFenceState::getFence(IsoGameCharacter character) {
 // TODO: Implement getFence
 return nullptr;
}

int ClimbOverFenceState::getFenceType(IsoObject object) {
 // TODO: Implement getFenceType
 return 0;
}

return ClimbOverFenceState::switch() {
 // TODO: Implement switch
 return nullptr;
}

int ClimbOverFenceState::getTripType(IsoObject object) {
 // TODO: Implement getTripType
 return 0;
}

return ClimbOverFenceState::switch() {
 // TODO: Implement switch
 return nullptr;
}

bool ClimbOverFenceState::shouldFallAfterVaultOver(IsoGameCharacter character) {
 // TODO: Implement shouldFallAfterVaultOver
 return false;
}

int ClimbOverFenceState::countZombiesClimbingOver(IsoObject object) {
 // TODO: Implement countZombiesClimbingOver
 return 0;
}

int ClimbOverFenceState::countZombiesClimbingOver(IsoObject object, IsoGridSquare square) {
 // TODO: Implement countZombiesClimbingOver
 return 0;
}

bool ClimbOverFenceState::isMetalFence(IsoObject object) {
 // TODO: Implement isMetalFence
 return false;
}

void ClimbOverFenceState::setParams(IsoGameCharacter owner, IsoDirections dir) {
 // TODO: Implement setParams
}

} // namespace states
} // namespace ai
} // namespace zombie
