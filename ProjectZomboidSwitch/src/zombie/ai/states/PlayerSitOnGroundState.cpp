#include "zombie/ai/states/PlayerSitOnGroundState.h"

namespace zombie {
namespace ai {
namespace states {

PlayerSitOnGroundState PlayerSitOnGroundState::instance() {
    static PlayerSitOnGroundState _instance;
    return _instance;
}

void PlayerSitOnGroundState::enter(IsoGameCharacter* var1) {
    auto& var2 = var1->getStateMachineParams(this);
    var2[PARAM_FIRE] = this->checkFire(var1);
    var2[PARAM_CHECK_FIRE] = static_cast<long>(time(nullptr)) * 1000;
    var2[PARAM_CHANGE_ANIM] = 0L;
    var1->setSitOnGround(true);
    if ((var1->getPrimaryHandItem() == nullptr || !dynamic_cast<HandWeapon*>(var1->getPrimaryHandItem())) &&
        (var1->getSecondaryHandItem() == nullptr || !dynamic_cast<HandWeapon*>(var1->getSecondaryHandItem()))) {
        var1->setHideWeaponModel(true);
    }
    if (var1->getStateMachine()->getPrevious() == IdleState::instance()) {
        var1->clearVariable("SitGroundStarted");
        var1->clearVariable("forceGetUp");
        var1->clearVariable("SitGroundAnim");
    }
}

bool PlayerSitOnGroundState::checkFire(IsoGameCharacter* var1) {
    IsoGridSquare* var2 = var1->getCurrentSquare();
    for (int var3 = -4; var3 < 4; ++var3) {
        for (int var4 = -4; var4 < 4; ++var4) {
            IsoGridSquare* var5 = var2->getCell()->getGridSquare(var2->x + var3, var2->y + var4, var2->z);
            if (var5) {
                if (var5->haveFire()) {
                    return true;
                }
                for (size_t var6 = 0; var6 < var5->getObjects().size(); ++var6) {
                    IsoFireplace* var7 = dynamic_cast<IsoFireplace*>(var5->getObjects()[var6]);
                    if (var7 && var7->isLit()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void PlayerSitOnGroundState::execute(IsoGameCharacter* var1) {
    auto& var2 = var1->getStateMachineParams(this);
    IsoPlayer* var3 = dynamic_cast<IsoPlayer*>(var1);
    if (var3 && var3->pressedMovement(false)) {
        var1->StopAllActionQueue();
        var1->setVariable("forceGetUp", true);
    }
    long var4 = static_cast<long>(time(nullptr)) * 1000;
    if (var4 > static_cast<long>(var2[PARAM_CHECK_FIRE]) + 5000L) {
        var2[PARAM_FIRE] = this->checkFire(var1);
        var2[PARAM_CHECK_FIRE] = var4;
    }
    if (var1->hasTimedActions()) {
        var2[PARAM_FIRE] = false;
        var1->setVariable("SitGroundAnim", "Idle");
    }
    bool var6 = static_cast<bool>(var2[PARAM_FIRE]);
    if (var6) {
        bool var7 = var4 > static_cast<long>(var2[PARAM_CHANGE_ANIM]);
        if (var7) {
            if (var1->getVariableString("SitGroundAnim") == "Idle") {
                var1->setVariable("SitGroundAnim", "WarmHands");
            } else if (var1->getVariableString("SitGroundAnim") == "WarmHands") {
                var1->setVariable("SitGroundAnim", "Idle");
            }
            var2[PARAM_CHANGE_ANIM] = var4 + Rand::Next(30000, 90000);
        }
    } else if (var1->getVariableBoolean("SitGroundStarted")) {
        var1->clearVariable("FireNear");
        var1->setVariable("SitGroundAnim", "Idle");
    }
    if (var1->getVariableString("SitGroundAnim") == "WarmHands" && Rand::Next(Rand::AdjustForFramerate(2500)) == 0) {
        var2[PARAM_SITGROUNDANIM] = var1->getVariableString("SitGroundAnim");
        var1->setVariable("SitGroundAnim", "rubhands");
    }
    if (var3) {
        var3->setInitiateAttack(false);
        var3->attackStarted = false;
        var3->setAttackType(nullptr);
    }
}

void PlayerSitOnGroundState::exit(IsoGameCharacter* var1) {
    var1->setHideWeaponModel(false);
    if (StringUtils::isNullOrEmpty(var1->getVariableString("HitReaction"))) {
        var1->clearVariable("SitGroundStarted");
        var1->clearVariable("forceGetUp");
        var1->clearVariable("SitGroundAnim");
        var1->setIgnoreMovement(false);
    }
}

void PlayerSitOnGroundState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "SitGroundStarted")) {
        var1->setVariable("SitGroundStarted", true);
        bool var3 = static_cast<bool>(var1->getStateMachineParams(this)[PARAM_FIRE]);
        if (var3) {
            var1->setVariable("SitGroundAnim", "WarmHands");
        } else {
            var1->setVariable("SitGroundAnim", "Idle");
        }
    }
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "ResetSitOnGroundAnim")) {
        var1->setVariable("SitGroundAnim", static_cast<std::string>(var1->getStateMachineParams(this)[PARAM_SITGROUNDANIM]));
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
