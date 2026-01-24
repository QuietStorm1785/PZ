#include "zombie/ai/states/PlayerEmoteState.h"

namespace zombie {
namespace ai {
namespace states {

PlayerEmoteState& PlayerEmoteState::instance() {
    static PlayerEmoteState _instance;
    return _instance;
}

void PlayerEmoteState::enter(IsoGameCharacter* character) {
    if (!character) return;
    character->setVariable("EmotePlaying", true);
    character->resetModelNextFrame();
}

void PlayerEmoteState::execute(IsoGameCharacter* character) {
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
    if (player && player->pressedCancelAction()) {
        character->setVariable("EmotePlaying", false);
    }
}

void PlayerEmoteState::exit(IsoGameCharacter* character) {
    if (!character) return;
    character->clearVariable("EmotePlaying");
    character->resetModelNextFrame();
}

void PlayerEmoteState::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    if (!character || !event) return;
    if (event->m_EventName == "EmoteFinishing") {
        character->setVariable("EmotePlaying", false);
    }
    // EmoteLooped event is a no-op
}

bool PlayerEmoteState::isDoingActionThatCanBeCancelled() {
    // Implement as needed
    return false;
}

} // namespace states
} // namespace ai
} // namespace zombie
