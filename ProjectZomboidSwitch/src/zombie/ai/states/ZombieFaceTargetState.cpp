#include "zombie/ai/states/ZombieFaceTargetState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieFaceTargetState ZombieFaceTargetState::instance() {
    static ZombieFaceTargetState _instance;
    return _instance;
}

void ZombieFaceTargetState::enter(IsoGameCharacter var1) {
    // No-op (matches Java)
}

void ZombieFaceTargetState::execute(IsoGameCharacter var1) {
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(&var1);
    if (zombie && zombie->getTarget() != nullptr) {
        zombie->faceThisObject(zombie->getTarget());
    }
}

void ZombieFaceTargetState::exit(IsoGameCharacter var1) {
    // No-op (matches Java)
}

} // namespace states
} // namespace ai
} // namespace zombie
