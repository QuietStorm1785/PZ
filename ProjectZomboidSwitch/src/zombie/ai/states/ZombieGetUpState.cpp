#include "zombie/ai/states/ZombieGetUpState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieGetUpState& ZombieGetUpState::instance() {
    static ZombieGetUpState _instance;
    return _instance;
}
}

void ZombieGetUpState::enter(IsoGameCharacter* var1) {
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(var1);
    auto& params = var1->getStateMachineParams(this);
    params[PARAM_STANDING] = false;
    State* prevState = var1->getStateMachine()->getPrevious();
    params[PARAM_PREV_STATE] = prevState;
    if (zombie) zombie->parameterZombieState.setState(ParameterZombieState::State::GettingUp);
    if (GameClient::bClient) {
        var1->setKnockedDown(false);
    }
    DebugLog::AI.debug("ZombieGetUpState::enter: GettingUp state set");
}
}

void ZombieGetUpState::execute(IsoGameCharacter* var1) {
    auto& params = var1->getStateMachineParams(this);
    bool standing = params[PARAM_STANDING] == true;
    var1->setOnFloor(!standing);
    if (auto* zombie = dynamic_cast<IsoZombie*>(var1)) {
        zombie->setKnockedDown(!standing);
    }
    DebugLog::AI.debug("ZombieGetUpState::execute: standing=%s", standing ? "true" : "false");
}
}

void ZombieGetUpState::exit(IsoGameCharacter* var1) {
    auto& params = var1->getStateMachineParams(this);
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(var1);
    var1->setCollidable(true);
    var1->clearVariable("SprinterTripped");
    var1->clearVariable("ShouldStandUp");
    if (var1->getHitReaction().empty() && zombie) {
        zombie->setSitAgainstWall(false);
    }
    if (zombie) {
        zombie->setKnockedDown(false);
        zombie->AllowRepathDelay = 0.0f;
    }
    DebugLog::AI.debug("ZombieGetUpState::exit: state cleanup done");
}
}

void ZombieGetUpState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    // No special event logic in Java, but add debug
    DebugLog::AI.debug("ZombieGetUpState::animEvent: event=%s", var2->m_EventName.c_str());
}
}

} // namespace states
} // namespace ai
} // namespace zombie
