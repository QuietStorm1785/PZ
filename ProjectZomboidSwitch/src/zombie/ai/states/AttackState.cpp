#include <string>
#include "zombie\ai\states/AttackState.h"

namespace zombie {
namespace ai {
namespace states {

AttackState AttackState::instance() {
    // TODO: Implement instance
    return nullptr;
}

void AttackState::enter(IsoGameCharacter var1) {
    // TODO: Implement enter
}

void AttackState::execute(IsoGameCharacter var1) {
    // TODO: Implement execute
}

void AttackState::exit(IsoGameCharacter var1) {
    // TODO: Implement exit
}

void AttackState::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    // TODO: Implement animEvent
}

bool AttackState::isAttacking(IsoGameCharacter var1) {
    // TODO: Implement isAttacking
    return false;
}

void AttackState::triggerPlayerReaction(const std::string& var1, IsoGameCharacter var2) {
    // TODO: Implement triggerPlayerReaction
}

} // namespace states
} // namespace ai
} // namespace zombie
