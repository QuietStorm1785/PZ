#include "zombie/ai/states/ClimbThroughWindowState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbThroughWindowState ClimbThroughWindowState::instance() {
 // TODO: Implement instance
 return nullptr;
}

void ClimbThroughWindowState::enter(IsoGameCharacter owner) {
 // TODO: Implement enter
}

void ClimbThroughWindowState::execute(IsoGameCharacter owner) {
 // TODO: Implement execute
}

void ClimbThroughWindowState::checkForFallingBack(IsoGridSquare square,
 IsoGameCharacter character) {
 // TODO: Implement checkForFallingBack
}

void ClimbThroughWindowState::checkForFallingFront(IsoGridSquare square,
 IsoGameCharacter character) {
 // TODO: Implement checkForFallingFront
}

void ClimbThroughWindowState::exit(IsoGameCharacter owner) {
 // TODO: Implement exit
}

void ClimbThroughWindowState::slideX(IsoGameCharacter owner, float x) {
 // TODO: Implement slideX
}

void ClimbThroughWindowState::slideY(IsoGameCharacter owner, float y) {
 // TODO: Implement slideY
}

void ClimbThroughWindowState::animEvent(IsoGameCharacter owner,
 AnimEvent event) {
 // TODO: Implement animEvent
}

bool ClimbThroughWindowState::isIgnoreCollide(IsoGameCharacter owner, int fromX,
 int fromY, int fromZ, int toX,
 int toY, int toZ) {
 // TODO: Implement isIgnoreCollide
 return false;
}

IsoObject ClimbThroughWindowState::getWindow(IsoGameCharacter owner) {
 // TODO: Implement getWindow
 return nullptr;
}

bool ClimbThroughWindowState::isWindowClosing(IsoGameCharacter owner) {
 // TODO: Implement isWindowClosing
 return false;
}

void ClimbThroughWindowState::getDeltaModifiers(IsoGameCharacter owner,
 MoveDeltaModifiers modifiers) {
 // TODO: Implement getDeltaModifiers
}

bool ClimbThroughWindowState::isFreeSquare(IsoGridSquare square) {
 // TODO: Implement isFreeSquare
 return false;
}

bool ClimbThroughWindowState::isObstacleSquare(IsoGridSquare square) {
 // TODO: Implement isObstacleSquare
 return false;
}

IsoGridSquare
ClimbThroughWindowState::getFreeSquareAfterObstacles(IsoGridSquare square1,
 IsoDirections directions) {
 // TODO: Implement getFreeSquareAfterObstacles
 return nullptr;
}

void ClimbThroughWindowState::setLungeXVars(IsoZombie zombie0) {
 // TODO: Implement setLungeXVars
}

bool ClimbThroughWindowState::isPastInnerEdgeOfSquare(IsoGameCharacter owner,
 int x, int y,
 IsoDirections moveDir) {
 // TODO: Implement isPastInnerEdgeOfSquare
 return false;
}

bool ClimbThroughWindowState::isPastOuterEdgeOfSquare(IsoGameCharacter owner,
 int x, int y,
 IsoDirections moveDir) {
 // TODO: Implement isPastOuterEdgeOfSquare
 return false;
}

void ClimbThroughWindowState::setParams(IsoGameCharacter owner, IsoObject obj) {
 // TODO: Implement setParams
}

} // namespace states
} // namespace ai
} // namespace zombie
