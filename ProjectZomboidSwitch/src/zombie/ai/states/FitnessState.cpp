#include "zombie/ai/states/FitnessState.h"

namespace zombie {
namespace ai {
namespace states {

FitnessState FitnessState::instance() {
    static FitnessState _instance;
    return _instance;
}

void FitnessState::enter(IsoGameCharacter* var1) {
    var1->setIgnoreMovement(true);
    var1->setVariable("FitnessFinished", false);
    var1->clearVariable("ExerciseStarted");
    var1->clearVariable("ExerciseEnded");
}

void FitnessState::execute(IsoGameCharacter* var1) {
    // No-op
}

void FitnessState::exit(IsoGameCharacter* var1) {
    if (GameClient::bClient && dynamic_cast<IsoPlayer*>(var1) && static_cast<IsoPlayer*>(var1)->isLocalPlayer()) {
        GameClient::sendEvent(static_cast<IsoPlayer*>(var1), "EventUpdateFitness");
    }
    var1->setIgnoreMovement(false);
    var1->clearVariable("FitnessFinished");
    var1->clearVariable("ExerciseStarted");
    var1->clearVariable("ExerciseHand");
    var1->clearVariable("FitnessStruggle");
    var1->setVariable("ExerciseEnded", true);
}

void FitnessState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    // No-op
}

} // namespace states
} // namespace ai
} // namespace zombie
