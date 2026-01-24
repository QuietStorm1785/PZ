#include "zombie/ai/states/PlayerKnockedDown.h"

namespace zombie {
namespace ai {
namespace states {


PlayerKnockedDown& PlayerKnockedDown::instance() {
    static PlayerKnockedDown _instance;
    return _instance;
}

void PlayerKnockedDown::enter(IsoGameCharacter* character) {
    if (!character) return;
    character->setIgnoreMovement(true);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
    if (player) player->setBlockMovement(true);
    character->setHitReaction("");
}

void PlayerKnockedDown::execute(IsoGameCharacter* character) {
    if (!character) return;
    if (character->isDead()) {
        if (!GameServer::bServer && !GameClient::bClient) {
            character->Kill(nullptr);
        }
    } else {
        character->setReanimateTimer(character->getReanimateTimer() - GameTime::getInstance()->getMultiplier() / 1.6f);
    }
}

void PlayerKnockedDown::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    if (!character || !event) return;
    if (event->m_EventName == "FallOnFront") {
        character->setFallOnFront(event->m_ParameterValue == "true");
    }
    if (event->m_EventName == "FallOnBack") {
        character->setFallOnFront(event->m_ParameterValue == "true");
    }
    if (event->m_EventName == "setSitOnGround") {
        character->setSitOnGround(event->m_ParameterValue == "true");
    }
}

void PlayerKnockedDown::exit(IsoGameCharacter* character) {
    if (!character) return;
    character->setIgnoreMovement(false);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
    if (player) {
        player->setBlockMovement(false);
        player->setKnockedDown(false);
    }
    character->setOnFloor(true);
}

} // namespace states
} // namespace ai
} // namespace zombie
