#include "zombie/ai/states/ZombieTurnAlerted.h"

namespace zombie {
namespace ai {
namespace states {

ZombieTurnAlerted& ZombieTurnAlerted::instance() {
    static ZombieTurnAlerted _instance;
    return _instance;
}
}

void ZombieTurnAlerted::enter(IsoGameCharacter* var1) {
    auto& params = var1->getStateMachineParams(this);
    float targetAngle = static_cast<float>(params[PARAM_TARGET_ANGLE]);
    var1->getAnimationPlayer()->setTargetAngle(targetAngle);
    DebugLog::AI.debug("ZombieTurnAlerted::enter: target angle set");
}
}

void ZombieTurnAlerted::execute(IsoGameCharacter* var1) {
    // No-op, but add debug
    DebugLog::AI.debug("ZombieTurnAlerted::execute: called");
}
}

void ZombieTurnAlerted::exit(IsoGameCharacter* var1) {
    var1->pathToSound(var1->getPathTargetX(), var1->getPathTargetY(), var1->getPathTargetZ());
    if (auto* zombie = dynamic_cast<IsoZombie*>(var1)) {
        zombie->alerted = false;
    }
    DebugLog::AI.debug("ZombieTurnAlerted::exit: alerted reset");
}
}

void ZombieTurnAlerted::setParams(IsoGameCharacter* var1, float angle) {
    auto& params = var1->getStateMachineParams(this);
    params.clear();
    params[PARAM_TARGET_ANGLE] = angle;
    DebugLog::AI.debug("ZombieTurnAlerted::setParams: target angle param set");
}
}

} // namespace states
} // namespace ai
} // namespace zombie
