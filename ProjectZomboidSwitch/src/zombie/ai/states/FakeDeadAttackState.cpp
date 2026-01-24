#include "zombie/ai/states/FakeDeadAttackState.h"

namespace zombie {
namespace ai {
namespace states {

FakeDeadAttackState& FakeDeadAttackState::instance() {
    static FakeDeadAttackState _instance;
    return _instance;
}

void FakeDeadAttackState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsFakeDeadAttacking", true);
    DebugLog::AI.debug("FakeDeadAttackState::enter: IsFakeDeadAttacking set true for %p", var1);
}

void FakeDeadAttackState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("FakeDeadAttack");
    DebugLog::AI.debug("FakeDeadAttackState::execute: playing fake dead attack animation for %p", var1);
}

void FakeDeadAttackState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsFakeDeadAttacking", false);
    DebugLog::AI.debug("FakeDeadAttackState::exit: IsFakeDeadAttacking set false for %p", var1);
}

void FakeDeadAttackState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "FakeDeadAttackFinished") {
        var1->setVariable("IsFakeDeadAttacking", false);
        DebugLog::AI.debug("FakeDeadAttackState::animEvent: FakeDeadAttackFinished for %p", var1);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
