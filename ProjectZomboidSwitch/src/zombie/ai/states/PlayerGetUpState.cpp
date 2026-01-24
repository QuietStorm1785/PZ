#include "zombie/ai/states/PlayerGetUpState.h"

namespace zombie {
namespace ai {
namespace states {


PlayerGetUpState& PlayerGetUpState::instance() {
    static PlayerGetUpState _instance;
    return _instance;
}

void PlayerGetUpState::enter(IsoGameCharacter* character) {
    if (!character) return;
    auto& params = character->getStateMachineParams(this);
    character->setIgnoreMovement(true);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
    if (player) {
        player->setInitiateAttack(false);
        player->attackStarted = false;
        player->setAttackType(nullptr);
        player->setBlockMovement(true);
        player->setForceRun(false);
        player->setForceSprint(false);
    }
    character->setVariable("getUpQuick", character->getVariableBoolean("pressedRunButton"));
    if (character->getMoodles()->getMoodleLevel(MoodleType::Panic) > 1) {
        character->setVariable("getUpQuick", true);
    }
    if (character->getVariableBoolean("pressedMovement")) {
        character->setVariable("getUpWalk", true);
    }
    if (GameClient::bClient) {
        character->setKnockedDown(false);
    }
}

void PlayerGetUpState::execute(IsoGameCharacter* character) {
    // No-op
}

void PlayerGetUpState::exit(IsoGameCharacter* character) {
    if (!character) return;
    character->clearVariable("getUpWalk");
    if (character->getVariableBoolean("sitonground")) {
        character->setHideWeaponModel(false);
    }
    character->setIgnoreMovement(false);
    character->setFallOnFront(false);
    character->setOnFloor(false);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(character);
    if (player) {
        player->setBlockMovement(false);
    }
    character->setSitOnGround(false);
}

} // namespace states
} // namespace ai
} // namespace zombie
