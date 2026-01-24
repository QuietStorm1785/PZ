#include "zombie/ai/states/ThumpState.h"

namespace zombie {
namespace ai {
namespace states {

ThumpState& ThumpState::instance() {
    static ThumpState _instance;
    return _instance;
}

void ThumpState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsThumping", true);
    DebugLog::AI.debug("ThumpState::enter: IsThumping set true for %p", var1);
}

void ThumpState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("Thump");
    DebugLog::AI.debug("ThumpState::execute: playing thump animation for %p", var1);
}

void ThumpState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsThumping", false);
    DebugLog::AI.debug("ThumpState::exit: IsThumping set false for %p", var1);
}

void ThumpState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "ThumpFinished") {
        var1->setVariable("IsThumping", false);
        DebugLog::AI.debug("ThumpState::animEvent: ThumpFinished for %p", var1);
    }
}

IsoPlayer* ThumpState::findPlayer(int var1, int var2, int var3, int var4, int var5) {
    // Example: find player in area
    IsoPlayer* player = IsoWorld::instance().findPlayer(var1, var2, var3, var4, var5);
    DebugLog::AI.debug("ThumpState::findPlayer: found player %p", player);
    return player;
}

bool ThumpState::lungeThroughDoor(IsoZombie* var1, IsoGridSquare* var2, IsoGridSquare* var3) {
    if (!var1 || !var2 || !var3) return false;
    bool canLunge = var1->canLungeThroughDoor(var2, var3);
    DebugLog::AI.debug("ThumpState::lungeThroughDoor: canLunge=%d for %p", canLunge, var1);
    return canLunge;
}

int ThumpState::getFastForwardDamageMultiplier() {
    int multiplier = 2;
    DebugLog::AI.debug("ThumpState::getFastForwardDamageMultiplier: multiplier=%d", multiplier);
    return multiplier;
}

bool ThumpState::isThumpTargetValid(IsoGameCharacter* var1, Thumpable* var2) {
    if (!var1 || !var2) return false;
    bool valid = var2->isValidThumpTarget(var1);
    DebugLog::AI.debug("ThumpState::isThumpTargetValid: valid=%d for %p on %p", valid, var1, var2);
    return valid;
}

} // namespace states
} // namespace ai
} // namespace zombie
