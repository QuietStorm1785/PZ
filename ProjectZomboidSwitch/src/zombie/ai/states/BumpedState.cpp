#include "zombie/ai/states/BumpedState.h"

namespace zombie {
namespace ai {
namespace states {


BumpedState& BumpedState::instance() {
    static BumpedState _instance;
    return _instance;
}

void BumpedState::enter(IsoGameCharacter* character) {
    if (!character) return;
    character->setBumpDone(false);
    character->setVariable("BumpFallAnimFinished", false);
    character->getAnimationPlayer()->setTargetToAngle();
    character->getForwardDirection()->setLengthAndDirection(character->getAnimationPlayer()->getAngle(), 1.0f);
    setCharacterBlockMovement(character, true);
    if (character->getVariableBoolean("BumpFall")) {
        long soundId = character->playSound("TripOverObstacle");
        IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
        if (player) {
            auto* param = player->getParameterCharacterMovementSpeed();
            character->getEmitter()->setParameterValue(soundId, param->getParameterDescription(), param->calculateCurrentValue());
        }
        std::string type = character->getVariableString("TripObstacleType");
        if (type.empty()) type = "zombie";
        character->clearVariable("TripObstacleType");
        int value = (type == "tree") ? 5 : 6;
        character->getEmitter()->setParameterValue(soundId, OpenALSoundEmitter::getParameterDescription("TripObstacleType"), value);
    }
}

void BumpedState::execute(IsoGameCharacter* character) {
    if (!character) return;
    bool block = character->isBumpFall() || character->isBumpStaggered();
    setCharacterBlockMovement(character, block);
}

void BumpedState::setCharacterBlockMovement(IsoGameCharacter* character, bool block) {
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
    if (player) {
        player->setBlockMovement(block);
    }
}

void BumpedState::exit(IsoGameCharacter* character) {
    if (!character) return;
    character->clearVariable("BumpFallType");
    character->clearVariable("BumpFallAnimFinished");
    character->clearVariable("BumpAnimFinished");
    character->setBumpType("");
    character->setBumpedChr(nullptr);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
    if (player) {
        player->setInitiateAttack(false);
        player->attackStarted = false;
        player->setAttackType(nullptr);
    }
    if (player && character->isBumpFall()) {
        character->fallenOnKnees();
    }
    character->setOnFloor(false);
    character->setBumpFall(false);
    setCharacterBlockMovement(character, false);
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(character);
    if (zombie && zombie->target) {
        character->pathToLocation(static_cast<int>(zombie->target->getX()), static_cast<int>(zombie->target->getY()), static_cast<int>(zombie->target->getZ()));
    }
}

void BumpedState::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    if (!character || !event) return;
    if (event->m_EventName == "FallOnFront") {
        character->setFallOnFront(event->m_ParameterValue == "true");
        character->setOnFloor(character->isFallOnFront());
    }
    if (event->m_EventName == "FallOnBack") {
        character->setOnFloor(event->m_ParameterValue == "true");
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
