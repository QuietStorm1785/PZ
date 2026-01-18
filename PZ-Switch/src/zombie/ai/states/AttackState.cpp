#include "zombie/ai/states/AttackState.h"

namespace zombie {
namespace ai {
namespace states {

AttackState AttackState::instance() {
 // TODO: Implement instance
 return nullptr;
}

void AttackState::enter(IsoGameCharacter owner) {
 // TODO: Implement enter
}

void AttackState::execute(IsoGameCharacter owner) {
 // TODO: Implement execute
}

void AttackState::exit(IsoGameCharacter owner) {
 // TODO: Implement exit
}

void AttackState::animEvent(IsoGameCharacter owner, AnimEvent event) {
 // TODO: Implement animEvent
}

bool AttackState::isAttacking(IsoGameCharacter owner) {
 // TODO: Implement isAttacking
 return false;
}

void AttackState::triggerPlayerReaction(const std::string &string1,
 IsoGameCharacter character0) {
 // TODO: Implement triggerPlayerReaction
}

} // namespace states
} // namespace ai
} // namespace zombie
