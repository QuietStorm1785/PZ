#include "zombie/ai/states/ZombieHitReactionState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieHitReactionState& ZombieHitReactionState::instance() {
    static ZombieHitReactionState _instance;
    return _instance;
}

void ZombieHitReactionState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsHitReacting", true);
    DebugLog::AI.debug("ZombieHitReactionState::enter: IsHitReacting set true for %p", var1);
}

void ZombieHitReactionState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("HitReaction");
    DebugLog::AI.debug("ZombieHitReactionState::execute: playing hit reaction animation for %p", var1);
}

void ZombieHitReactionState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsHitReacting", false);
    DebugLog::AI.debug("ZombieHitReactionState::exit: IsHitReacting set false for %p", var1);
}

void ZombieHitReactionState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "HitReactionFinished") {
        var1->setVariable("IsHitReacting", false);
        DebugLog::AI.debug("ZombieHitReactionState::animEvent: HitReactionFinished for %p", var1);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
