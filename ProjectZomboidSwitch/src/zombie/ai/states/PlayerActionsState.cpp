#include "zombie/ai/states/PlayerActionsState.h"

namespace zombie {
namespace ai {
namespace states {

PlayerActionsState& PlayerActionsState::instance() {
    static PlayerActionsState _instance;
    return _instance;
}

void PlayerActionsState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsPerformingAction", true);
    DebugLog::AI.debug("PlayerActionsState::enter: IsPerformingAction set true for %p", var1);
}

void PlayerActionsState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("PlayerAction");
    DebugLog::AI.debug("PlayerActionsState::execute: playing player action animation for %p", var1);
}

void PlayerActionsState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsPerformingAction", false);
    DebugLog::AI.debug("PlayerActionsState::exit: IsPerformingAction set false for %p", var1);
}

void PlayerActionsState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "PlayerActionFinished") {
        var1->setVariable("IsPerformingAction", false);
        DebugLog::AI.debug("PlayerActionsState::animEvent: PlayerActionFinished for %p", var1);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
