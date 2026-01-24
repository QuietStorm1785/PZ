#include "zombie/ai/states/PlayerFallingState.h"

namespace zombie {
namespace ai {
namespace states {


PlayerFallingState& PlayerFallingState::instance() {
    static PlayerFallingState _instance;
    return _instance;
}

void PlayerFallingState::enter(IsoGameCharacter* character) {
    if (character) {
        character->setVariable("bHardFall", false);
        character->clearVariable("bLandAnimFinished");
    }
}

void PlayerFallingState::execute(IsoGameCharacter* character) {
    // No-op
}

void PlayerFallingState::exit(IsoGameCharacter* character) {
    if (character) {
        character->clearVariable("bHardFall");
        character->clearVariable("bLandAnimFinished");
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
