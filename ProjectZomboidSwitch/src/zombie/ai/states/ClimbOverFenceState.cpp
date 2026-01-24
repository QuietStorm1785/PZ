#include "zombie/ai/states/ClimbOverFenceState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbOverFenceState& ClimbOverFenceState::instance() {
    static ClimbOverFenceState _instance;
    return _instance;
}

void ClimbOverFenceState::enter(IsoGameCharacter* var1) {
    // Set initial lunge variables
    var1->setVariable("FenceLungeX", 0.0f);
    var1->setVariable("FenceLungeY", 0.0f);
    auto var2 = var1->getStateMachineParams(this);
    var1->setIgnoreMovement(true);
    if (var2[PARAM_RUN] == true) {
        var1->setVariable("VaultOverRun", true);
        auto stats = var1->getStats();
        stats->endurance -= ZomboidGlobals::RunningEnduranceReduce * 300.0f;
    } else if (var2[PARAM_SPRINT] == true) {
        var1->setVariable("VaultOverSprint", true);
        auto stats = var1->getStats();
        stats->endurance -= ZomboidGlobals::RunningEnduranceReduce * 700.0f;
    }

    bool var3 = var2[PARAM_SCRATCH] == true;
    IsoZombie* var4 = dynamic_cast<IsoZombie*>(var1);
    if (!var3 && var4 && var4->shouldDoFenceLunge()) {
        var1->setVariable("ClimbFenceOutcome", "lunge");
        this->setLungeXVars(var4);
    }

    if (var2[PARAM_SOLID_FLOOR] == false) {
        var1->setVariable("ClimbFenceOutcome", "falling");
    }

    if (!(dynamic_cast<IsoZombie*>(var1)) && var2[PARAM_SHEET_ROPE] == true) {
        var1->setVariable("ClimbFenceOutcome", "rope");
    }

    IsoPlayer* player = dynamic_cast<IsoPlayer*>(var1);
    if (player && player->isLocalPlayer()) {
        player->dirtyRecalcGridStackTime = 20.0f;
    }
}

void ClimbOverFenceState::setLungeXVars(IsoZombie* var1) {
    IsoMovingObject* var2 = var1->getTarget();
    if (var2) {
        var1->setVariable("FenceLungeX", 0.0f);
        var1->setVariable("FenceLungeY", 0.0f);
        float var3 = 0.0f;
        Vector2 var4 = var1->getForwardDirection();
        SideOfLine var5 = PZMath::testSideOfLine(var1->x, var1->y, var1->x + var4.x, var1->y + var4.y, var2->x, var2->y);
        float var6 = acos(var1->getDotWithForwardDirection(var2->x, var2->y));
        float var7 = PZMath::clamp(PZMath::radToDeg(var6), 0.0f, 90.0f);
        switch (var5) {
            case SideOfLine::Left:
                var3 = -var7 / 90.0f;
                break;
            case SideOfLine::On:
                var3 = 0.0f;
                break;
            case SideOfLine::Right:
                var3 = var7 / 90.0f;
                break;
        }
        var1->setVariable("FenceLungeX", var3);
    }
}

void ClimbOverFenceState::execute(IsoGameCharacter* var1) {
    auto var2 = var1->getStateMachineParams(this);
    IsoDirections* var3 = dynamic_cast<IsoDirections*>(var2[PARAM_DIR]);
    int var4 = static_cast<int>(var2[PARAM_END_X]);
    int var5 = static_cast<int>(var2[PARAM_END_Y]);
    var1->setAnimated(true);
    if (var3) {
        var1->setDir(*var3);
           ClimbOverFenceState& ClimbOverFenceState::instance() {
              static ClimbOverFenceState _instance;
              return _instance;
           }
    std::string var6 = var1->getVariableString("ClimbFenceOutcome");
    if (var6 != "lunge") {
        float var7 = 0.05f;
           // Example: Reduce movement speed when climbing
           if (var1->getVariableBoolean("ClimbFenceStarted")) {
              var2.speed *= 0.5f;
              DebugLog::AI.debug("getDeltaModifiers: speed reduced for climbing");
           }
            var1->x = var1->nx = PZMath::clamp(var1->x, var4 + var7, var4 + 1 - var7);
        } else if (*var3 == IsoDirections::W || *var3 == IsoDirections::E) {
            var1->y = var1->ny = PZMath::clamp(var1->y, var5 + var7, var5 + 1 - var7);
           // Ignore collision if character is vaulting
           bool ignore = var1->getVariableBoolean("VaultOverRun") || var1->getVariableBoolean("VaultOverSprint");
           DebugLog::AI.debug("isIgnoreCollide: %s", ignore ? "true" : "false");
           return ignore;

    if (var1->getVariableBoolean("ClimbFenceStarted") &&
        var6 != "back" && var6 != "fallback" && var6 != "lunge" &&
           // Slide character along X axis during climb
           var1->x += var2;
           DebugLog::AI.debug("slideX: x=%f", var1->x);
        float var9 = static_cast<int>(var2[PARAM_START_X]);
        float var8 = static_cast<int>(var2[PARAM_START_Y]);
        switch (*var3) {
           // Slide character along Y axis during climb
           var1->y += var2;
           DebugLog::AI.debug("slideY: y=%f", var1->y);
                var8 -= 0.1f;
                break;
            case IsoDirections::S:
           // Find fence object at character's position
           IsoGridSquare* square = var1->getCurrentSquare();
           if (!square) return nullptr;
           for (auto obj : square->getObjects()) {
              if (obj->isFence()) {
                 DebugLog::AI.debug("getFence: found fence");
                 return obj;
              }
           }
           DebugLog::AI.debug("getFence: no fence found");
           return nullptr;
            case IsoDirections::W:
                var9 -= 0.1f;
                break;
           // Return fence type based on object properties
           if (!var1) return 0;
           if (var1->isMetalFence()) return 1;
           if (var1->isMetalBars()) return 2;
           return 0;
                break;
        }
        if (static_cast<int>(var1->x) != static_cast<int>(var9) && (*var3 == IsoDirections::W || *var3 == IsoDirections::E)) {
           // Return trip type based on fence type
           int type = getFenceType(var1);
           switch (type) {
              case 1: return TRIP_METAL_BARS;
              case 2: return TRIP_WINDOW;
              default: return TRIP_ZOMBIE;
           }
        if (static_cast<int>(var1->y) != static_cast<int>(var8) && (*var3 == IsoDirections::N || *var3 == IsoDirections::S)) {
            this->slideY(var1, var8);
        }
           // Fall if running or sprinting and random chance
           if (var1->getVariableBoolean("VaultOverRun") || var1->getVariableBoolean("VaultOverSprint")) {
              bool fall = Rand::Next(0, 100) < 20; // 20% chance
              DebugLog::AI.debug("shouldFallAfterVaultOver: %s", fall ? "true" : "false");
              return fall;
           }
           return false;
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(var1);
    if (zombie) {
        bool var10 = var2[PARAM_ZOMBIE_ON_FLOOR] == true;
           // Count zombies climbing over this fence
           int count = 0;
           if (!var1) return 0;
           for (auto chr : var1->getSquare()->getMovingCharacters()) {
              if (chr->isZombie() && chr->getVariableBoolean("ClimbFenceStarted")) {
                 ++count;
              }
           }
           DebugLog::AI.debug("countZombiesClimbingOver: %d", count);
           return count;
        var1->setFallOnFront(var10);
    }
}
           // Check if fence is metal
           bool metal = var1 && var1->isMetalFence();
           DebugLog::AI.debug("isMetalFence: %s", metal ? "true" : "false");
           return metal;
    auto var2 = var1->getStateMachineParams(this);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(var1);
    if (player && var1->getVariableString("ClimbFenceOutcome") == "fall") {
           // Set parameters for climbing
           var1->setVariable("ClimbFenceStarted", true);
           var1->setDir(var2);
           DebugLog::AI.debug("setParams: started climb, dir=%d", static_cast<int>(var2));
    }
    var1->clearVariable("ClimbingFence");
    var1->clearVariable("ClimbFenceFinished");
    var1->clearVariable("ClimbFenceOutcome");
    var1->clearVariable("ClimbFenceStarted");
    var1->clearVariable("ClimbFenceFlopped");
    var1->clearVariable("VaultOverSprint");
    var1->clearVariable("VaultOverRun");
    var1->setIgnoreMovement(false);
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(var1);
    if (zombie) {
        zombie->AllowRepathDelay = 0.0f;
        // Assuming PathFindState and WalkTowardState are implemented similarly in C++
        if (var2[PARAM_PREV_STATE] == PathFindState::instance()) {
            if (!var1->getPathFindBehavior2()->getTargetChar()) {
                var1->setVariable("bPathfind", true);
                var1->setVariable("bMoving", false);
            } else if (zombie->isTargetLocationKnown()) {
                var1->pathToCharacter(var1->getPathFindBehavior2()->getTargetChar());
            } else if (zombie->LastTargetSeenX != -1) {
                var1->pathToLocation(zombie->LastTargetSeenX, zombie->LastTargetSeenY, zombie->LastTargetSeenZ);
            }
        } else if (var2[PARAM_PREV_STATE] == WalkTowardState::instance() || var2[PARAM_PREV_STATE] == WalkTowardNetworkState::instance()) {
            var1->setVariable("bPathFind", false);
            var1->setVariable("bMoving", true);
        }
    }
    if (zombie) {
        zombie->networkAI.isClimbing = false;
    }
}

void ClimbOverFenceState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    auto var3 = var1->getStateMachineParams(this);
    IsoZombie* var4 = dynamic_cast<IsoZombie*>(var1);
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "CheckAttack") && var4 && dynamic_cast<IsoGameCharacter*>(var4->target)) {
        static_cast<IsoGameCharacter*>(var4->target)->attackFromWindowsLunge(var4);
    }
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "ActiveAnimFinishing")) {
        // No-op in Java
    }
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "VaultSprintFallLanded")) {
        var1->dropHandItems();
        var1->fallenOnKnees();
    }
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "FallenOnKnees")) {
        var1->fallenOnKnees();
    }
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "OnFloor")) {
        var3[PARAM_ZOMBIE_ON_FLOOR] = StringUtils::parseBool(var2->m_ParameterValue);
        if (StringUtils::parseBool(var2->m_ParameterValue)) {
            this->setLungeXVars(var4);
            IsoObject* var5 = this->getFence(var1);
            if (this->countZombiesClimbingOver(var5) >= 2) {
                var5->Damage = static_cast<short>(var5->Damage - Rand::Next(7, 12) / (this->isMetalFence(var5) ? 2 : 1));
                if (var5->Damage <= 0) {
                    IsoDirections* var6 = dynamic_cast<IsoDirections*>(var3[PARAM_DIR]);
                    var5->destroyFence(*var6);
                }
            }
            var1->setVariable("ClimbFenceFlopped", true);
        }
    }
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "PlayFenceSound")) {
        if (!SoundManager::instance()->isListenerInRange(var1->getX(), var1->getY(), 10.0f)) {
            return;
        }
        IsoObject* var11 = this->getFence(var1);
        if (!var11) {
            return;
        }
        int var14 = this->getFenceType(var11);
        long var7 = var1->getEmitter()->playSoundImpl(var2->m_ParameterValue, nullptr);
        if (dynamic_cast<IsoPlayer*>(var1)) {
            // Additional IsoPlayer logic if needed
        }
    }
}

void ClimbOverFenceState::getDeltaModifiers(IsoGameCharacter var1, MoveDeltaModifiers var2) {
    // Example: Reduce movement speed when climbing
    if (var1->getVariableBoolean("ClimbFenceStarted")) {
        var2.speed *= 0.5f;
        DebugLog::AI.debug("ClimbOverFenceState::getDeltaModifiers: speed reduced for climbing");
    }
}

bool ClimbOverFenceState::isIgnoreCollide(IsoGameCharacter var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    // Ignore collision if character is vaulting
    bool ignore = var1->getVariableBoolean("VaultOverRun") || var1->getVariableBoolean("VaultOverSprint");
    DebugLog::AI.debug("ClimbOverFenceState::isIgnoreCollide: %s", ignore ? "true" : "false");
    return ignore;
}

void ClimbOverFenceState::slideX(IsoGameCharacter var1, float var2) {
    // Slide character along X axis during climb
    var1->x += var2;
    DebugLog::AI.debug("ClimbOverFenceState::slideX: x=%f", var1->x);
}

void ClimbOverFenceState::slideY(IsoGameCharacter var1, float var2) {
    // Slide character along Y axis during climb
    var1->y += var2;
    DebugLog::AI.debug("ClimbOverFenceState::slideY: y=%f", var1->y);
}

IsoObject ClimbOverFenceState::getFence(IsoGameCharacter var1) {
    // Find fence object at character's position
    IsoGridSquare* square = var1->getCurrentSquare();
    if (!square) return nullptr;
    for (auto obj : square->getObjects()) {
        if (obj->isFence()) {
            DebugLog::AI.debug("ClimbOverFenceState::getFence: found fence");
            return obj;
        }
    }
    DebugLog::AI.debug("ClimbOverFenceState::getFence: no fence found");
    return nullptr;
}

int ClimbOverFenceState::getFenceType(IsoObject var1) {
    // Return fence type based on object properties
    if (!var1) return 0;
    if (var1->isMetalFence()) return 1;
    if (var1->isMetalBars()) return 6;
    return 0;
}

return ClimbOverFenceState::switch() {
    // Placeholder for switch logic
    DebugLog::AI.debug("ClimbOverFenceState::switch: called");
    return nullptr;
}

int ClimbOverFenceState::getTripType(IsoObject var1) {
    // Return trip type based on fence type
    int type = getFenceType(var1);
    switch (type) {
        case 1: return TRIP_METAL;
        case 6: return TRIP_METAL_BARS;
        default: return TRIP_WOOD;
    }
}

return ClimbOverFenceState::switch() {
    // Placeholder for switch logic
    DebugLog::AI.debug("ClimbOverFenceState::switch: called");
    return nullptr;
}

bool ClimbOverFenceState::shouldFallAfterVaultOver(IsoGameCharacter var1) {
    // Fall if running or sprinting and random chance
    if (var1->getVariableBoolean("VaultOverRun") || var1->getVariableBoolean("VaultOverSprint")) {
        bool fall = Rand::Next(0, 100) < 20; // 20% chance
        DebugLog::AI.debug("ClimbOverFenceState::shouldFallAfterVaultOver: %s", fall ? "true" : "false");
        return fall;
    }
    return false;
}

int ClimbOverFenceState::countZombiesClimbingOver(IsoObject var1) {
    // Count zombies climbing over this fence
    int count = 0;
    if (!var1) return 0;
    for (auto chr : var1->getSquare()->getMovingCharacters()) {
        if (chr->isZombie() && chr->getVariableBoolean("ClimbFenceStarted")) {
            ++count;
        }
    }
    DebugLog::AI.debug("ClimbOverFenceState::countZombiesClimbingOver: %d", count);
    return count;
}

int ClimbOverFenceState::countZombiesClimbingOver(IsoObject var1, IsoGridSquare var2) {
    // Count zombies climbing over this fence in a specific square
    int count = 0;
    if (!var1 || !var2) return 0;
    for (auto chr : var2->getMovingCharacters()) {
        if (chr->isZombie() && chr->getVariableBoolean("ClimbFenceStarted")) {
            ++count;
        }
    }
    DebugLog::AI.debug("ClimbOverFenceState::countZombiesClimbingOver (square): %d", count);
    return count;
}

bool ClimbOverFenceState::isMetalFence(IsoObject var1) {
    // Check if fence is metal
    bool metal = var1 && var1->isMetalFence();
    DebugLog::AI.debug("ClimbOverFenceState::isMetalFence: %s", metal ? "true" : "false");
    return metal;
}

void ClimbOverFenceState::setParams(IsoGameCharacter var1, IsoDirections var2) {
    // Set parameters for climbing
    var1->setVariable("ClimbFenceStarted", true);
    var1->setDir(var2);
    DebugLog::AI.debug("ClimbOverFenceState::setParams: started climb, dir=%d", static_cast<int>(var2));
}

} // namespace states
} // namespace ai
} // namespace zombie
