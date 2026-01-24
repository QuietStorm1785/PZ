#include "zombie/ai/states/ClimbThroughWindowState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbThroughWindowState& ClimbThroughWindowState::instance() {
    static ClimbThroughWindowState _instance;
    return _instance;
}

void ClimbThroughWindowState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClimbingThroughWindow", true);
    DebugLog::AI.debug("ClimbThroughWindowState::enter: IsClimbingThroughWindow set true for %p", var1);
}

void ClimbThroughWindowState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("ClimbThroughWindow");
    DebugLog::AI.debug("ClimbThroughWindowState::execute: playing climb through window animation for %p", var1);
}

void ClimbThroughWindowState::checkForFallingBack(IsoGridSquare* var1, IsoGameCharacter* var2) {
    if (!var1 || !var2) return;
    bool shouldFall = var2->getVariableBoolean("ShouldFallBack");
    if (shouldFall) {
        var2->playAnimation("FallBack");
        DebugLog::AI.debug("ClimbThroughWindowState::checkForFallingBack: Falling back for %p", var2);
    }
}

void ClimbThroughWindowState::checkForFallingFront(IsoGridSquare* var1, IsoGameCharacter* var2) {
    if (!var1 || !var2) return;
    bool shouldFall = var2->getVariableBoolean("ShouldFallFront");
    if (shouldFall) {
        var2->playAnimation("FallFront");
        DebugLog::AI.debug("ClimbThroughWindowState::checkForFallingFront: Falling front for %p", var2);
    }
}

void ClimbThroughWindowState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClimbingThroughWindow", false);
    DebugLog::AI.debug("ClimbThroughWindowState::exit: IsClimbingThroughWindow set false for %p", var1);
}

void ClimbThroughWindowState::slideX(IsoGameCharacter* var1, float var2) {
    if (!var1) return;
    var1->setX(var1->getX() + var2);
    DebugLog::AI.debug("ClimbThroughWindowState::slideX: X slid by %.2f for %p", var2, var1);
}

void ClimbThroughWindowState::slideY(IsoGameCharacter* var1, float var2) {
    if (!var1) return;
    var1->setY(var1->getY() + var2);
    DebugLog::AI.debug("ClimbThroughWindowState::slideY: Y slid by %.2f for %p", var2, var1);
}

void ClimbThroughWindowState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    DebugLog::AI.debug("ClimbThroughWindowState::animEvent: event %s for %p", var2->m_EventName.c_str(), var1);
}

bool ClimbThroughWindowState::isIgnoreCollide(IsoGameCharacter* var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    if (!var1) return false;
    bool ignore = var1->getVariableBoolean("IgnoreCollide");
    DebugLog::AI.debug("ClimbThroughWindowState::isIgnoreCollide: ignore=%d for %p", ignore, var1);
    return ignore;
}

IsoObject* ClimbThroughWindowState::getWindow(IsoGameCharacter* var1) {
    if (!var1) return nullptr;
    IsoObject* window = var1->getNearbyWindow();
    DebugLog::AI.debug("ClimbThroughWindowState::getWindow: found window %p for %p", window, var1);
    return window;
}

bool ClimbThroughWindowState::isWindowClosing(IsoGameCharacter* var1) {
    if (!var1) return false;
    bool closing = var1->getVariableBoolean("IsWindowClosing");
    DebugLog::AI.debug("ClimbThroughWindowState::isWindowClosing: closing=%d for %p", closing, var1);
    return closing;
}

void ClimbThroughWindowState::getDeltaModifiers(IsoGameCharacter* var1, MoveDeltaModifiers& var2) {
    if (!var1) return;
    var2.xMod = 1.0f;
    var2.yMod = 1.0f;
    DebugLog::AI.debug("ClimbThroughWindowState::getDeltaModifiers: xMod=%.2f yMod=%.2f for %p", var2.xMod, var2.yMod, var1);
}

bool ClimbThroughWindowState::isFreeSquare(IsoGridSquare* var1) {
    if (!var1) return false;
    bool free = var1->isFree();
    DebugLog::AI.debug("ClimbThroughWindowState::isFreeSquare: free=%d for %p", free, var1);
    return free;
}

bool ClimbThroughWindowState::isObstacleSquare(IsoGridSquare* var1) {
    if (!var1) return false;
    bool obstacle = var1->isObstacle();
    DebugLog::AI.debug("ClimbThroughWindowState::isObstacleSquare: obstacle=%d for %p", obstacle, var1);
    return obstacle;
}

IsoGridSquare* ClimbThroughWindowState::getFreeSquareAfterObstacles(IsoGridSquare* var1, IsoDirections var2) {
    if (!var1) return nullptr;
    IsoGridSquare* freeSquare = var1->getFreeSquareAfterObstacles(var2);
    DebugLog::AI.debug("ClimbThroughWindowState::getFreeSquareAfterObstacles: found %p after obstacles from %p", freeSquare, var1);
    return freeSquare;
}

void ClimbThroughWindowState::setLungeXVars(IsoZombie* var1) {
    if (!var1) return;
    var1->setVariable("LungeX", 0.0f);
    var1->setVariable("LungeY", 0.0f);
    DebugLog::AI.debug("ClimbThroughWindowState::setLungeXVars: LungeX/Y set for %p", var1);
}

} // namespace states
} // namespace ai
} // namespace zombie
