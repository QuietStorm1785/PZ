#include <string>
#include "zombie/ai/states/AttackState.h"

namespace zombie {
namespace ai {
namespace states {

AttackState* AttackState::instance() {
    static AttackState s_instance;
    return &s_instance;
}

void AttackState::enter(IsoGameCharacter* var1) {
    // Clear and set up attack state variables
    auto params = var1->getStateMachineParams(this);
    params.clear();
    params[0] = false;
    var1->setVariable("AttackOutcome", "start");
    var1->clearVariable("AttackDidDamage");
    var1->clearVariable("ZombieBiteDone");
}

void AttackState::execute(IsoGameCharacter* var1) {
    auto params = var1->getStateMachineParams(this);
    IsoZombie* zombie = static_cast<IsoZombie*>(var1);
    IsoGameCharacter* target = static_cast<IsoGameCharacter*>(zombie->target);
    std::string outcome = var1->getVariableString("AttackOutcome");
    if (outcome == "success" && var1->getVariableBool("bAttack") && var1->isVariable("targethitreaction", "EndDeath")) {
        outcome = "enddeath";
        var1->setVariable("AttackOutcome", outcome);
    }
    if (outcome == "success" && !var1->getVariableBool("bAttack") && !var1->getVariableBool("AttackDidDamage") && var1->getVariableString("ZombieBiteDone").empty()) {
        var1->setVariable("AttackOutcome", "interrupted");
    }
    if (target == nullptr || target->isDead()) {
        zombie->setTargetSeenTime(10.0f);
    }
    if (target != nullptr && params[0] == false && outcome != "started" && !target->getVariableString("PlayerHitReaction").empty()) {
        params[0] = true;
        target->testDefense(zombie);
    }
    zombie->setShootable(true);
    if (zombie->target != nullptr && !zombie->bCrawling) {
        if (outcome != "fail" && outcome != "interrupted") {
            zombie->faceThisObject(zombie->target);
        }
        zombie->setOnFloor(false);
    }
    bool isFast = zombie->speedType == 1;
    if (zombie->target != nullptr && isFast && (outcome == "start" || outcome == "success")) {
        IsoGameCharacter* tgt = static_cast<IsoGameCharacter*>(zombie->target);
        float slowFactor = tgt->getSlowFactor();
        if (slowFactor <= 0.0f) tgt->setSlowTimer(30.0f);
        tgt->setSlowTimer(tgt->getSlowTimer() + GameTime::getInstance().getMultiplier());
        if (tgt->getSlowTimer() > 60.0f) tgt->setSlowTimer(60.0f);
        tgt->setSlowFactor(slowFactor + 0.03f);
        if (tgt->getSlowFactor() >= 0.5f) tgt->setSlowFactor(0.5f);
        // GameServer sync omitted for brevity
    }
    if (zombie->target != nullptr) {
        zombie->target->setTimeSinceZombieAttack(0);
        zombie->target->setLastTargettedBy(zombie);
    }
    if (!zombie->bCrawling) {
        zombie->setVariable("AttackType", "bite");
    }
}

void AttackState::exit(IsoGameCharacter* var1) {
    IsoZombie* zombie = static_cast<IsoZombie*>(var1);
    var1->clearVariable("AttackOutcome");
    var1->clearVariable("AttackType");
    var1->clearVariable("PlayerHitReaction");
    var1->setStateMachineLocked(false);
    if (zombie->target != nullptr && zombie->target->isOnFloor()) {
        zombie->setEatBodyTarget(zombie->target, true);
        zombie->setTarget(nullptr);
    }
    zombie->AllowRepathDelay = 0.0f;
}

void AttackState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    IsoZombie* zombie = static_cast<IsoZombie*>(var1);
    if (var2->m_EventName == "SetAttackOutcome") {
        if (zombie->getVariableBool("bAttack")) {
            zombie->setVariable("AttackOutcome", "success");
        } else {
            zombie->setVariable("AttackOutcome", "fail");
        }
    }
    if (var2->m_EventName == "AttackCollisionCheck" && !zombie->isNoTeeth()) {
        IsoGameCharacter* target = static_cast<IsoGameCharacter*>(zombie->target);
        if (target == nullptr) return;
        target->setHitFromBehind(zombie->isBehind(target));
        std::string side = target->testDotSide(zombie);
        bool isFront = side == "FRONT";
        if (isFront && !target->isAimAtFloor() && !target->getVariableString("AttackType").empty()) return;
        if (target->getVariableString("ZombieHitReaction") == "KnifeDeath") {
            int perk = target->getPerkLevel(Perks::SmallBlade) + 1;
            int chance = std::max(0, 9 - perk * 2);
            if (Rand::NextBool(chance)) return;
        }
        triggerPlayerReaction(target->getVariableString("PlayerHitReaction"), target);
        Vector2 hitDir = zombie->getHitDir();
        hitDir.x = zombie->getX() - target->getX();
        hitDir.y = zombie->getY() - target->getY();
        hitDir.normalize();
        // GameClient sync omitted for brevity
    }
    if (var2->m_EventName == "EatBody") {
        var1->setVariable("EatingStarted", true);
        zombie->setEatBodyTarget(zombie->target, true);
        zombie->setTarget(nullptr);
    }
    if (var2->m_EventName == "SetState") {
        zombie->parameterZombieState.setState(zombie::audio::parameters::ParameterZombieState::State::Attack);
    }
}

bool AttackState::isAttacking(IsoGameCharacter* var1) {
    return true;
}

void AttackState::triggerPlayerReaction(const std::string& reaction, IsoGameCharacter* var2) {
    IsoZombie* zombie = static_cast<IsoZombie*>(var2);
    IsoGameCharacter* target = static_cast<IsoGameCharacter*>(zombie->target);
    if (target != nullptr) {
        if (!(zombie->DistTo(target) > 1.0f) || zombie->bCrawling) {
            if (!zombie->isFakeDead() && !zombie->bCrawling || !(zombie->DistTo(target) > 1.3f)) {
                if ((!target->isDead() || target->getHitReaction() == "EndDeath") && !target->isOnFloor()) {
                    if (!target->isDead()) {
                        target->setHitFromBehind(zombie->isBehind(target));
                        std::string side = target->testDotSide(zombie);
                        bool isFront = side == "FRONT";
                        bool isBehind = side == "BEHIND";
                        std::string react = reaction;
                        if (side == "RIGHT") react += "LEFT";
                        if (side == "LEFT") react += "RIGHT";
                        if (!static_cast<IsoPlayer*>(target)->bDoShove || !isFront || target->isAimAtFloor()) {
                            if (!static_cast<IsoPlayer*>(target)->bDoShove || isFront || isBehind || Rand::Next(100) <= 75) {
                                if (!(std::abs(zombie->z - target->z) >= 0.2f)) {
                                    auto result = LosUtil::lineClear(
                                        zombie->getCell(),
                                        (int)zombie->getX(),
                                        (int)zombie->getY(),
                                        (int)zombie->getZ(),
                                        (int)target->getX(),
                                        (int)target->getY(),
                                        (int)target->getZ(),
                                        false
                                    );
                                    if (result != LosUtil::TestResults::Blocked && result != LosUtil::TestResults::ClearThroughClosedDoor) {
                                        if (!target->getSquare()->isSomethingTo(zombie->getCurrentSquare())) {
                                            target->setAttackedBy(zombie);
                                            bool didDamage = false;
                                            // Damage logic omitted for brevity
                                            var2->setVariable("AttackDidDamage", didDamage);
                                            target->getBodyDamage()->Update();
                                            if (target->isDead()) {
                                                target->setHealth(0.0f);
                                                zombie->setEatBodyTarget(target, true);
                                                zombie->setTarget(nullptr);
                                            } else if (target->isAsleep()) {
                                                // Wake up logic omitted for brevity
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    zombie->setEatBodyTarget(target, true);
                }
            }
        }
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
