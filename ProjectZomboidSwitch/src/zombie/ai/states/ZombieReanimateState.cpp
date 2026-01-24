#include "zombie/ai/states/ZombieReanimateState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieReanimateState& ZombieReanimateState::instance() {
    static ZombieReanimateState _instance;
    return _instance;
}

void ZombieReanimateState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsReanimating", true);
    DebugLog::AI.debug("ZombieReanimateState::enter: IsReanimating set true for %p", var1);
}

void ZombieReanimateState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("ZombieReanimate");
    DebugLog::AI.debug("ZombieReanimateState::execute: playing reanimate animation for %p", var1);
}

void ZombieReanimateState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsReanimating", false);
    DebugLog::AI.debug("ZombieReanimateState::exit: IsReanimating set false for %p", var1);
}

void ZombieReanimateState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "ReanimateFinished") {
        var1->setVariable("IsReanimating", false);
        DebugLog::AI.debug("ZombieReanimateState::animEvent: ReanimateFinished for %p", var1);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
