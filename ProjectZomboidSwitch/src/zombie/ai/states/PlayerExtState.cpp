#include "zombie/ai/states/PlayerExtState.h"

namespace zombie {
namespace ai {
namespace states {


PlayerExtState& PlayerExtState::instance() {
    static PlayerExtState _instance;
    return _instance;
}

void PlayerExtState::enter(IsoGameCharacter* character) {
    if (character) {
        character->setVariable("ExtPlaying", true);
    }
}

void PlayerExtState::execute(IsoGameCharacter* character) {
    // No-op
}

void PlayerExtState::exit(IsoGameCharacter* character) {
    if (character) {
        character->clearVariable("ExtPlaying");
    }
}

void PlayerExtState::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    if (character && event && event->m_EventName == "ExtFinishing") {
        character->setVariable("ExtPlaying", false);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
