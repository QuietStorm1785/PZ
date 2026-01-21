#include "zombie/ai/states/ClimbThroughWindowState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbThroughWindowState ClimbThroughWindowState::instance() {
    // TODO: Implement instance
    return nullptr;
}

void ClimbThroughWindowState::enter(IsoGameCharacter var1) {
    // TODO: Implement enter
}

void ClimbThroughWindowState::execute(IsoGameCharacter var1) {
    // TODO: Implement execute
}

void ClimbThroughWindowState::checkForFallingBack(IsoGridSquare var1, IsoGameCharacter var2) {
    // TODO: Implement checkForFallingBack
}

void ClimbThroughWindowState::checkForFallingFront(IsoGridSquare var1, IsoGameCharacter var2) {
    // TODO: Implement checkForFallingFront
}

void ClimbThroughWindowState::exit(IsoGameCharacter var1) {
    // TODO: Implement exit
}

void ClimbThroughWindowState::slideX(IsoGameCharacter var1, float var2) {
    // TODO: Implement slideX
}

void ClimbThroughWindowState::slideY(IsoGameCharacter var1, float var2) {
    // TODO: Implement slideY
}

void ClimbThroughWindowState::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    // TODO: Implement animEvent
}

bool ClimbThroughWindowState::isIgnoreCollide(IsoGameCharacter var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    // TODO: Implement isIgnoreCollide
    return false;
}

IsoObject ClimbThroughWindowState::getWindow(IsoGameCharacter var1) {
    // TODO: Implement getWindow
    return nullptr;
}

bool ClimbThroughWindowState::isWindowClosing(IsoGameCharacter var1) {
    // TODO: Implement isWindowClosing
    return false;
}

void ClimbThroughWindowState::getDeltaModifiers(IsoGameCharacter var1, MoveDeltaModifiers var2) {
    // TODO: Implement getDeltaModifiers
}

bool ClimbThroughWindowState::isFreeSquare(IsoGridSquare var1) {
    // TODO: Implement isFreeSquare
    return false;
}

bool ClimbThroughWindowState::isObstacleSquare(IsoGridSquare var1) {
    // TODO: Implement isObstacleSquare
    return false;
}

IsoGridSquare ClimbThroughWindowState::getFreeSquareAfterObstacles(IsoGridSquare var1, IsoDirections var2) {
    // TODO: Implement getFreeSquareAfterObstacles
    return nullptr;
}

void ClimbThroughWindowState::setLungeXVars(IsoZombie var1) {
    // TODO: Implement setLungeXVars
}

bool ClimbThroughWindowState::isPastInnerEdgeOfSquare(IsoGameCharacter var1, int var2, int var3, IsoDirections var4) {
    // TODO: Implement isPastInnerEdgeOfSquare
    return false;
}

bool ClimbThroughWindowState::isPastOuterEdgeOfSquare(IsoGameCharacter var1, int var2, int var3, IsoDirections var4) {
    // TODO: Implement isPastOuterEdgeOfSquare
    return false;
}

void ClimbThroughWindowState::setParams(IsoGameCharacter var1, IsoObject var2) {
    // TODO: Implement setParams
}

} // namespace states
} // namespace ai
} // namespace zombie
