#include <string>
#include <vector>
#include "zombie/ai/states/SwipeStatePlayer.h"

namespace zombie {
namespace ai {
namespace states {

SwipeStatePlayer SwipeStatePlayer::instance() {
    // TODO: Implement instance
    return nullptr;
}

void SwipeStatePlayer::WeaponLowerCondition(HandWeapon var0, IsoGameCharacter var1) {
    // TODO: Implement WeaponLowerCondition
}

HandWeapon SwipeStatePlayer::GetWeapon(IsoGameCharacter var0) {
    // TODO: Implement GetWeapon
    return nullptr;
}

void SwipeStatePlayer::doAttack(IsoPlayer var1, float var2, bool var3, const std::string& var4, AttackVars var5) {
    // TODO: Implement doAttack
}

void SwipeStatePlayer::enter(IsoGameCharacter var1) {
    // TODO: Implement enter
}

void SwipeStatePlayer::execute(IsoGameCharacter var1) {
    // TODO: Implement execute
}

int SwipeStatePlayer::DoSwingCollisionBoneCheck(IsoGameCharacter var1, HandWeapon var2, IsoGameCharacter var3, int var4, float var5) {
    // TODO: Implement DoSwingCollisionBoneCheck
    return 0;
}

void SwipeStatePlayer::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    // TODO: Implement animEvent
}

void SwipeStatePlayer::exit(IsoGameCharacter var1) {
    // TODO: Implement exit
}

void SwipeStatePlayer::CalcAttackVars(IsoLivingCharacter var1, AttackVars var2) {
    // TODO: Implement CalcAttackVars
}

void SwipeStatePlayer::calcValidTargets(IsoLivingCharacter var1, HandWeapon var2, bool var3, std::vector<HitInfo> var4, std::vector<HitInfo> var5) {
    // TODO: Implement calcValidTargets
}

bool SwipeStatePlayer::shouldIgnoreProneZombies(IsoGameCharacter var1, std::vector<HitInfo> var2, float var3) {
    // TODO: Implement shouldIgnoreProneZombies
    return false;
}

bool SwipeStatePlayer::isUnhittableTarget(IsoGameCharacter var1, HandWeapon var2, float var3, float var4, HitInfo var5, bool var6) {
    // TODO: Implement isUnhittableTarget
    return false;
}

void SwipeStatePlayer::removeUnhittableTargets(IsoGameCharacter var1, HandWeapon var2, float var3, float var4, bool var5, std::vector<HitInfo> var6) {
    // TODO: Implement removeUnhittableTargets
}

bool SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter var1, HandWeapon var2, IsoMovingObject var3, bool var4, Vector4f var5) {
    // TODO: Implement getNearestTargetPosAndDot
    return false;
}

void SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter var1, Vector3 var2, Vector2 var3, Vector4f var4) {
    // TODO: Implement getNearestTargetPosAndDot
}

void SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter var1, IsoMovingObject var2, const std::string& var3, Vector2 var4, Vector4f var5) {
    // TODO: Implement getNearestTargetPosAndDot
}

void SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter var1, IsoMovingObject var2, Vector4f var3) {
    // TODO: Implement getNearestTargetPosAndDot
}

HitInfo SwipeStatePlayer::calcValidTarget(IsoLivingCharacter var1, HandWeapon var2, IsoMovingObject var3, float var4) {
    // TODO: Implement calcValidTarget
    return nullptr;
}

bool SwipeStatePlayer::isProne(IsoMovingObject var0) {
    // TODO: Implement isProne
    return false;
}

bool SwipeStatePlayer::isStanding(IsoMovingObject var0) {
    // TODO: Implement isStanding
    return false;
}

bool SwipeStatePlayer::isProneTargetBetter(IsoGameCharacter var1, HitInfo var2, HitInfo var3) {
    // TODO: Implement isProneTargetBetter
    return false;
}

bool SwipeStatePlayer::checkPVP(IsoGameCharacter var0, IsoMovingObject var1) {
    // TODO: Implement checkPVP
    return false;
}

void SwipeStatePlayer::CalcHitListShove(IsoGameCharacter var1, bool var2, AttackVars var3, std::vector<HitInfo> var4) {
    // TODO: Implement CalcHitListShove
}

void SwipeStatePlayer::CalcHitListWeapon(IsoGameCharacter var1, bool var2, AttackVars var3, std::vector<HitInfo> var4) {
    // TODO: Implement CalcHitListWeapon
}

void SwipeStatePlayer::CalcHitListWindow(IsoGameCharacter var1, HandWeapon var2, std::vector<HitInfo> var3) {
    // TODO: Implement CalcHitListWindow
}

void SwipeStatePlayer::CalcHitList(IsoGameCharacter var1, bool var2, AttackVars var3, std::vector<HitInfo> var4) {
    // TODO: Implement CalcHitList
}

void SwipeStatePlayer::filterTargetsByZ(IsoGameCharacter var1) {
    // TODO: Implement filterTargetsByZ
}

int SwipeStatePlayer::CalcHitChance(IsoGameCharacter var1, HandWeapon var2, HitInfo var3) {
    // TODO: Implement CalcHitChance
    return 0;
}

Vector3 SwipeStatePlayer::getBoneWorldPos(IsoMovingObject var0, const std::string& var1, Vector3 var2) {
    // TODO: Implement getBoneWorldPos
    return nullptr;
}

void SwipeStatePlayer::ConnectSwing(IsoGameCharacter var1, HandWeapon var2) {
    // TODO: Implement ConnectSwing
}

int SwipeStatePlayer::calcDamageToVehicle(int var1, int var2, bool var3) {
    // TODO: Implement calcDamageToVehicle
    return 0;
}

void SwipeStatePlayer::splash(IsoMovingObject var0, HandWeapon var1, IsoGameCharacter var2) {
    // TODO: Implement splash
}

bool SwipeStatePlayer::checkObjectHit(IsoGameCharacter var1, HandWeapon var2, IsoGridSquare var3, bool var4, bool var5) {
    // TODO: Implement checkObjectHit
    return false;
}

bool SwipeStatePlayer::CheckObjectHit(IsoGameCharacter var1, HandWeapon var2) {
    // TODO: Implement CheckObjectHit
    return false;
}

TestResults SwipeStatePlayer::los(int var1, int var2, int var3, int var4, int var5, LOSVisitor var6) {
    // TODO: Implement los
    return nullptr;
}

IsoWindow SwipeStatePlayer::getWindowBetween(int var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement getWindowBetween
    return nullptr;
}

IsoWindow SwipeStatePlayer::getWindowBetween(IsoMovingObject var1, IsoMovingObject var2) {
    // TODO: Implement getWindowBetween
    return nullptr;
}

bool SwipeStatePlayer::isWindowBetween(IsoMovingObject var1, IsoMovingObject var2) {
    // TODO: Implement isWindowBetween
    return false;
}

void SwipeStatePlayer::smashWindowBetween(IsoGameCharacter var1, IsoMovingObject var2, HandWeapon var3) {
    // TODO: Implement smashWindowBetween
}

void SwipeStatePlayer::changeWeapon(HandWeapon var1, IsoGameCharacter var2) {
    // TODO: Implement changeWeapon
}

void SwipeStatePlayer::setParameterCharacterHitResult(IsoGameCharacter var1, IsoZombie var2, long var3) {
    // TODO: Implement setParameterCharacterHitResult
}

} // namespace states
} // namespace ai
} // namespace zombie
