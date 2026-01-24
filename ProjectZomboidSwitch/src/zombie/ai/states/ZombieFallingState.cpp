#include "zombie/ai/states/ZombieFallingState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieFallingState ZombieFallingState::instance() {
    static ZombieFallingState _instance;
    return _instance;
}

void ZombieFallingState::enter(IsoGameCharacter var1) {
    var1.setVariable("bHardFall", false);
    var1.clearVariable("bLandAnimFinished");
}

void ZombieFallingState::execute(IsoGameCharacter var1) {
    // No-op (matches Java)
}

void ZombieFallingState::exit(IsoGameCharacter var1) {
    var1.clearVariable("bHardFall");
    var1.clearVariable("bLandAnimFinished");
}

void ZombieFallingState::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    if (var2.m_EventName == "FallOnFront") {
        var1.setFallOnFront(var2.m_ParameterValue == "true");
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
