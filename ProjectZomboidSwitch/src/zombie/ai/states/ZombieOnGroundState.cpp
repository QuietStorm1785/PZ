#include "zombie/ai/states/ZombieOnGroundState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieOnGroundState& ZombieOnGroundState::instance() {
    static ZombieOnGroundState _instance;
    return _instance;
}

void ZombieOnGroundState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsOnGround", true);
    DebugLog::AI.debug("ZombieOnGroundState::enter: IsOnGround set true for %p", var1);
}

void ZombieOnGroundState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    // Example: play on ground animation
    var1->playAnimation("ZombieOnGround");
    DebugLog::AI.debug("ZombieOnGroundState::execute: playing on ground animation for %p", var1);
}

bool ZombieOnGroundState::isCharacterStandingOnOther(IsoGameCharacter* var0, IsoGameCharacter* var1) {
    if (!var0 || !var1) return false;
    bool standing = (var0->getPosition().z > var1->getPosition().z);
    DebugLog::AI.debug("ZombieOnGroundState::isCharacterStandingOnOther: %p standing on %p = %d", var0, var1, standing);
    return standing;
}

int ZombieOnGroundState::DoCollisionBoneCheck(IsoGameCharacter* var0, IsoGameCharacter* var1, int var2, float var3) {
    if (!var0 || !var1) return 0;
    // Example: check bone collision by distance
    float dist = var0->getDistance(var1);
    int result = (dist < var3) ? var2 : -1;
    DebugLog::AI.debug("ZombieOnGroundState::DoCollisionBoneCheck: dist=%.2f, threshold=%.2f, result=%d", dist, var3, result);
    return result;
}

void ZombieOnGroundState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsOnGround", false);
    DebugLog::AI.debug("ZombieOnGroundState::exit: IsOnGround set false for %p", var1);
}

} // namespace states
} // namespace ai
} // namespace zombie
