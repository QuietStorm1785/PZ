#include "zombie/ai/states/PlayerHitReactionState.h"

namespace zombie {
namespace ai {
namespace states {


PlayerHitReactionState& PlayerHitReactionState::instance() {
    static PlayerHitReactionState _instance;
    return _instance;
}

void PlayerHitReactionState::enter(IsoGameCharacter* character) {
    if (!character) return;
    character->setIgnoreMovement(true);
    if (!character->getCharacterActions().empty()) {
        auto* action = dynamic_cast<BaseAction*>(character->getCharacterActions().front());
        if (action) action->forceStop();
    }
    character->setIsAiming(false);
}

void PlayerHitReactionState::execute(IsoGameCharacter* character) {
    // No-op
}

void PlayerHitReactionState::exit(IsoGameCharacter* character) {
    if (!character) return;
    character->setIgnoreMovement(false);
    character->setHitReaction("");
}

void PlayerHitReactionState::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    if (!character || !event) return;
    auto* zombie = dynamic_cast<IsoZombie*>(character->getAttackedBy());
    if (character->getAttackedBy() && zombie) {
        if (event->m_EventName == "PushAwayZombie") {
            character->getAttackedBy()->setHitForce(0.03f);
            zombie->setPlayerAttackPosition(nullptr);
            zombie->setStaggerBack(true);
        }
        if (event->m_EventName == "Defend") {
            character->getAttackedBy()->setHitReaction("BiteDefended");
            if (GameClient::bClient) {
                GameClient::sendHitCharacter(character->getAttackedBy(), character, nullptr, 0.0f, false, 1.0f, false, false, false);
            }
        }
        if (event->m_EventName == "DeathSound") {
            if (character->isPlayingDeathSound()) return;
            character->setPlayingDeathSound(true);
            std::string gender = character->isFemale() ? "Female" : "Male";
            gender += "BeingEatenDeath";
            character->playSound(gender);
        }
        if (event->m_EventName == "Death") {
            character->setOnFloor(true);
            if (!GameServer::bServer) {
                character->Kill(character->getAttackedBy());
            }
        }
    } else {
        DebugLog::log("PlayerHitReactionState.animEvent (" + event->m_EventName + ") zombie is null");
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
