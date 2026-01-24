#include "zombie/ai/states/FakeDeadZombieState.h"

namespace zombie {
namespace ai {
namespace states {

FakeDeadZombieState& FakeDeadZombieState::instance() {
    static FakeDeadZombieState _instance;
    return _instance;
}

void FakeDeadZombieState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsFakeDead", true);
    DebugLog::AI.debug("FakeDeadZombieState::enter: IsFakeDead set true for %p", var1);
}

void FakeDeadZombieState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("FakeDead");
    DebugLog::AI.debug("FakeDeadZombieState::execute: playing fake dead animation for %p", var1);
}

IsoDeadBody* FakeDeadZombieState::IsoDeadBody() {
    // Example: create a new dead body object
    IsoDeadBody* body = new IsoDeadBody();
    DebugLog::AI.debug("FakeDeadZombieState::IsoDeadBody: created dead body %p", body);
    return body;
}

void FakeDeadZombieState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsFakeDead", false);
    DebugLog::AI.debug("FakeDeadZombieState::exit: IsFakeDead set false for %p", var1);
}

} // namespace states
} // namespace ai
} // namespace zombie
