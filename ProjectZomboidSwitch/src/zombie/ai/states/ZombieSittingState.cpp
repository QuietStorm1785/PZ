#include "zombie/ai/states/ZombieSittingState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieSittingState& ZombieSittingState::instance() {
    static ZombieSittingState _instance;
    return _instance;
}

void ZombieSittingState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsSitting", true);
    DebugLog::AI.debug("ZombieSittingState::enter: IsSitting set true for %p", var1);
}

void ZombieSittingState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("ZombieSit");
    DebugLog::AI.debug("ZombieSittingState::execute: playing sit animation for %p", var1);
}

void ZombieSittingState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsSitting", false);
    DebugLog::AI.debug("ZombieSittingState::exit: IsSitting set false for %p", var1);
}

} // namespace states
} // namespace ai
} // namespace zombie
