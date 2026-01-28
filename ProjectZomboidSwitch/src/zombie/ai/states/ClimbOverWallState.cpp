#include "zombie/ai/states/ClimbOverWallState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbOverWallState ClimbOverWallState::instance() {
    static ClimbOverWallState _instance;
    return _instance;
}

void ClimbOverWallState::enter(IsoGameCharacter* var1) {
    var1->setIgnoreMovement(true);
    var1->setHideWeaponModel(true);
    auto& var2 = var1->getStateMachineParams(this);
    auto stats = var1->getStats();
    stats->endurance -= ZomboidGlobals::RunningEnduranceReduce * 1200.0f;
    IsoPlayer* var3 = dynamic_cast<IsoPlayer*>(var1);
    bool var4 = var3 ? var3->isClimbOverWallStruggle() : false;
    if (var4) {
        stats->endurance -= ZomboidGlobals::RunningEnduranceReduce * 500.0f;
    }
    bool var5 = var3 ? var3->isClimbOverWallSuccess() : false;
    var1->setVariable("ClimbFenceFinished", false);
    var1->setVariable("ClimbFenceOutcome", var5 ? "success" : "fail");
    var1->setVariable("ClimbFenceStarted", false);
    var1->setVariable("ClimbFenceStruggle", var4);
}

void ClimbOverWallState::execute(IsoGameCharacter* var1) {
    auto& var2 = var1->getStateMachineParams(this);
    IsoDirections* var3 = dynamic_cast<IsoDirections*>(var2[PARAM_DIR]);
    var1->setAnimated(true);
    if (var3) var1->setDir(*var3);
    bool var4 = var1->getVariableBoolean("ClimbFenceStarted");
    if (!var4) {
        int var5 = static_cast<int>(var2[PARAM_START_X]);
        int var6 = static_cast<int>(var2[PARAM_START_Y]);
        float var7 = 0.15f;
        float var8 = var1->getX();
        float var9 = var1->getY();
        switch (*var3) {
            case IsoDirections::N:
                var9 = var6 + var7;
                break;
            case IsoDirections::S:
                var9 = var6 + 1 - var7;
                break;
            case IsoDirections::W:
                var8 = var5 + var7;
                break;
            case IsoDirections::E:
                var8 = var5 + 1 - var7;
                break;
        }
        float var10 = GameTime::getInstance()->getMultiplier() / 1.6f / 8.0f;
        var1->setX(var1->x + (var8 - var1->x) * var10);
        var1->setY(var1->y + (var9 - var1->y) * var10);
    }
}

void ClimbOverWallState::exit(IsoGameCharacter* var1) {
    var1->clearVariable("ClimbFenceFinished");
    var1->clearVariable("ClimbFenceOutcome");
    var1->clearVariable("ClimbFenceStarted");
    var1->clearVariable("ClimbFenceStruggle");
    var1->setIgnoreMovement(false);
    var1->setHideWeaponModel(false);
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(var1);
    if (zombie) {
        zombie->networkAI.isClimbing = false;
    }
}

void ClimbOverWallState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "PlayFenceSound")) {
        IsoObject* var3 = this->getFence(var1);
        if (!var3) return;
        int var4 = this->getFenceType(var3);
        long var5 = var1->getEmitter()->playSoundImpl(var2->m_ParameterValue, nullptr);
        var1->getEmitter()->setParameterValue(var5, OpenALSoundEmitter::getParameterDescription("FenceTypeHigh"), var4);
    }
}

bool ClimbOverWallState::isIgnoreCollide(IsoGameCharacter* var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    auto& var8 = var1->getStateMachineParams(this);
    int var9 = static_cast<int>(var8[PARAM_START_X]);
    int var10 = static_cast<int>(var8[PARAM_START_Y]);
    int var11 = static_cast<int>(var8[PARAM_END_X]);
    int var12 = static_cast<int>(var8[PARAM_END_Y]);
    int var13 = static_cast<int>(var8[PARAM_Z]);
    if (var13 == var4 && var13 == var7) {
        int var14 = std::min(var9, var11);
        int var15 = std::min(var10, var12);
        int var16 = std::max(var9, var11);
        int var17 = std::max(var10, var12);
        int var18 = std::min(var2, var5);
        int var19 = std::min(var3, var6);
        int var20 = std::max(var2, var5);
        int var21 = std::max(var3, var6);
        return var14 <= var18 && var15 <= var19 && var16 >= var20 && var17 >= var21;
    } else {
        return false;
    }
}

IsoObject ClimbOverWallState::getClimbableWallN(IsoGridSquare var1) {
    // Find climbable wall to the north
    for (auto obj : var1->getObjects()) {
        if (obj->isClimbableWallN()) {
            DebugLog::AI.debug("ClimbOverWallState::getClimbableWallN: found climbable wall N");
            return obj;
        }
    }
    DebugLog::AI.debug("ClimbOverWallState::getClimbableWallN: no climbable wall N found");
    return nullptr;
}

IsoObject ClimbOverWallState::getClimbableWallW(IsoGridSquare var1) {
    // Find climbable wall to the west
    for (auto obj : var1->getObjects()) {
        if (obj->isClimbableWallW()) {
            DebugLog::AI.debug("ClimbOverWallState::getClimbableWallW: found climbable wall W");
            return obj;
        }
    }
    DebugLog::AI.debug("ClimbOverWallState::getClimbableWallW: no climbable wall W found");
    return nullptr;
}

IsoObject ClimbOverWallState::getFence(IsoGameCharacter var1) {
    // Find fence object at character's position
    IsoGridSquare* square = var1->getCurrentSquare();
    if (!square) return nullptr;
    for (auto obj : square->getObjects()) {
        if (obj->isFence()) {
            DebugLog::AI.debug("ClimbOverWallState::getFence: found fence");
            return obj;
        }
    }
    DebugLog::AI.debug("ClimbOverWallState::getFence: no fence found");
    return nullptr;
}

return ClimbOverWallState::switch() {
    // Placeholder for switch logic
    DebugLog::AI.debug("ClimbOverWallState::switch: called");
    return nullptr;
}

int ClimbOverWallState::getFenceType(IsoObject var1) {
    // Return fence type based on object properties
    if (!var1) return 0;
    if (var1->isMetalFence()) return 1;
    if (var1->isMetalBars()) return 2;
    return 0;
}

return ClimbOverWallState::switch() {
    // Placeholder for switch logic
    DebugLog::AI.debug("ClimbOverWallState::switch: called");
    return nullptr;
}

void ClimbOverWallState::setParams(IsoGameCharacter var1, IsoDirections var2) {
    // Set parameters for climbing
    var1->setVariable("ClimbFenceStarted", true);
    var1->setDir(var2);
    DebugLog::AI.debug("ClimbOverWallState::setParams: started climb, dir=%d", static_cast<int>(var2));
}

} // namespace states
} // namespace ai
} // namespace zombie
