#include "zombie/ai/states/CollideWithWallState.h"

namespace zombie {
namespace ai {
namespace states {

CollideWithWallState& CollideWithWallState::instance() {
    static CollideWithWallState _instance;
    return _instance;
}
}
void CollideWithWallState::enter(IsoGameCharacter* var1) {
    // Ignore movement and set direction based on collision
    var1->setIgnoreMovement(true);
    if (auto* player = dynamic_cast<IsoPlayer*>(var1)) {
        player->setIsAiming(false);
    }
    if (var1->isCollidedN()) var1->setDir(IsoDirections::N);
    if (var1->isCollidedS()) var1->setDir(IsoDirections::S);
    if (var1->isCollidedE()) var1->setDir(IsoDirections::E);
    if (var1->isCollidedW()) var1->setDir(IsoDirections::W);
    var1->setCollideType("wall");
    DebugLog::AI.debug("CollideWithWallState::enter: direction set, movement ignored");
}
    // Already implemented: enter
void CollideWithWallState::execute(IsoGameCharacter* var1) {
    var1->setLastCollideTime(70.0f);
    DebugLog::AI.debug("CollideWithWallState::execute: last collide time set");
}
void CollideWithWallState::execute(IsoGameCharacter var1) {
void CollideWithWallState::exit(IsoGameCharacter* var1) {
    var1->setCollideType(nullptr);
    var1->setIgnoreMovement(false);
    DebugLog::AI.debug("CollideWithWallState::exit: movement restored");
}

void CollideWithWallState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (var2->m_EventName == "PlayCollideSound") {
        long soundId = var1->playSound(var2->m_ParameterValue);
        if (auto* player = dynamic_cast<IsoPlayer*>(var1)) {
            auto* paramSpeed = player->getParameterCharacterMovementSpeed();
            var1->getEmitter()->setParameterValue(soundId, paramSpeed->getParameterDescription(), MovementType::Sprint.label);
            var1->getEmitter()->setParameterValue(soundId, FMODManager::instance().getParameterDescription("TripObstacleType"), 7.0f);
        }
        DebugLog::AI.debug("CollideWithWallState::animEvent: PlayCollideSound triggered");
    }
}
}

void CollideWithWallState::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    // This overload is not used; see animEvent(IsoGameCharacter*, AnimEvent*)
}

} // namespace states
} // namespace ai
} // namespace zombie
