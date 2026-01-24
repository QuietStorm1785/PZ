#include "zombie/ai/states/PlayerHitReactionPVPState.h"

namespace zombie {
namespace ai {
namespace states {

PlayerHitReactionPVPState& PlayerHitReactionPVPState::instance() {
    static PlayerHitReactionPVPState _instance;
    return _instance;
}

void PlayerHitReactionPVPState::enter(IsoGameCharacter* character) {
    if (!character) return;
    if (!character->getCharacterActions().empty()) {
        auto* action = dynamic_cast<BaseAction*>(character->getCharacterActions().front());
        if (action) action->forceStop();
    }
    character->setSitOnGround(false);
}

void PlayerHitReactionPVPState::execute(IsoGameCharacter* character) {
    // No-op
}

void PlayerHitReactionPVPState::exit(IsoGameCharacter* character) {
    if (!character) return;
    character->setIgnoreMovement(false);
    character->setHitReaction("");
    character->setVariable("hitpvp", false);
}

void PlayerHitReactionPVPState::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    if (!character || !event) return;
    if (event->m_EventName == "PushAwayZombie") {
        if (character->getAttackedBy()) {
            character->getAttackedBy()->setHitForce(0.03f);
            auto* zombie = dynamic_cast<IsoZombie*>(character->getAttackedBy());
            if (zombie) {
                zombie->setPlayerAttackPosition(nullptr);
                zombie->setStaggerBack(true);
            }
        }
    }
    if (event->m_EventName == "Defend") {
        if (character->getAttackedBy()) {
            character->getAttackedBy()->setHitReaction("BiteDefended");
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
}

} // namespace states
} // namespace ai
} // namespace zombie
