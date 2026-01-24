#include "zombie/ai/states/PlayerFallDownState.h"

namespace zombie {
namespace ai {
namespace states {


PlayerFallDownState& PlayerFallDownState::instance() {
    static PlayerFallDownState _instance;
    return _instance;
}

void PlayerFallDownState::enter(IsoGameCharacter* character) {
    if (!character) return;
    character->setIgnoreMovement(true);
    character->clearVariable("bKnockedDown");
    if (character->isDead() && !GameServer::bServer && !GameClient::bClient) {
        character->Kill(nullptr);
    }
}

void PlayerFallDownState::execute(IsoGameCharacter* character) {
    // No-op
}

void PlayerFallDownState::exit(IsoGameCharacter* character) {
    if (!character) return;
    character->setIgnoreMovement(false);
    character->setOnFloor(true);
}

void PlayerFallDownState::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    if (GameClient::bClient && event && event->m_EventName == "FallOnFront") {
        character->setFallOnFront(event->m_ParameterValue == "true");
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
