#include "zombie/ai/states/AttackNetworkState.h"

namespace zombie {
namespace ai {
namespace states {

AttackNetworkState& AttackNetworkState::instance() {
    static AttackNetworkState _instance;
    return _instance;
}
}

void AttackNetworkState::enter(IsoGameCharacter* var1) {
    var1->setVariable("IsAttacking", true);
    DebugLog::AI.debug("AttackNetworkState::enter: IsAttacking set true");
}
}

void AttackNetworkState::execute(IsoGameCharacter* var1) {
    // Example: reduce stamina during attack
    var1->getStats()->endurance -= 0.1f;
    DebugLog::AI.debug("AttackNetworkState::execute: endurance reduced");
}
}

void AttackNetworkState::exit(IsoGameCharacter* var1) {
    var1->setVariable("IsAttacking", false);
    DebugLog::AI.debug("AttackNetworkState::exit: IsAttacking set false");
}
}

void AttackNetworkState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (var2->m_EventName == "PlayAttackSound") {
        var1->playSound(var2->m_ParameterValue);
        DebugLog::AI.debug("AttackNetworkState::animEvent: PlayAttackSound triggered");
    }
}
}

bool AttackNetworkState::isAttacking(IsoGameCharacter* var1) {
    bool attacking = var1->getVariableBoolean("IsAttacking");
    DebugLog::AI.debug("AttackNetworkState::isAttacking: %s", attacking ? "true" : "false");
    return attacking;
}
}

} // namespace states
} // namespace ai
} // namespace zombie
