#include "zombie/ai/states/ForecastBeatenPlayerState.h"

namespace zombie {
namespace ai {
namespace states {


ForecastBeatenPlayerState& ForecastBeatenPlayerState::instance() {
    static ForecastBeatenPlayerState _instance;
    return _instance;
}

void ForecastBeatenPlayerState::enter(IsoGameCharacter* character) {
    if (character) {
        character->setIgnoreMovement(true);
        character->setReanimateTimer(30.0f);
    }
}

void ForecastBeatenPlayerState::execute(IsoGameCharacter* character) {
    if (character && character->getCurrentSquare() != nullptr) {
        float timer = character->getReanimateTimer();
        timer -= GameTime::getInstance()->getMultiplier() / 1.6f;
        if (timer <= 0.0f) {
            timer = 0.0f;
            character->setVariable("bKnockedDown", true);
        }
        character->setReanimateTimer(timer);
    }
}

void ForecastBeatenPlayerState::exit(IsoGameCharacter* character) {
    if (character) {
        character->setIgnoreMovement(false);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
