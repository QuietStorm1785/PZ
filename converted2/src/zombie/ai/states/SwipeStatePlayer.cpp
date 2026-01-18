#include "zombie/ai/states/SwipeStatePlayer.h"

namespace zombie {
namespace ai {
namespace states {

SwipeStatePlayer SwipeStatePlayer::instance() {
  // TODO: Implement instance
  return nullptr;
}

void SwipeStatePlayer::WeaponLowerCondition(HandWeapon weapon,
                                            IsoGameCharacter owner) {
  // TODO: Implement WeaponLowerCondition
}

HandWeapon SwipeStatePlayer::GetWeapon(IsoGameCharacter character) {
  // TODO: Implement GetWeapon
  return nullptr;
}

void SwipeStatePlayer::doAttack(IsoPlayer player, float float0, bool boolean0,
                                const std::string &string,
                                AttackVars attackVars) {
  // TODO: Implement doAttack
}

void SwipeStatePlayer::enter(IsoGameCharacter owner) {
  // TODO: Implement enter
}

void SwipeStatePlayer::execute(IsoGameCharacter owner) {
  // TODO: Implement execute
}

int SwipeStatePlayer::DoSwingCollisionBoneCheck(IsoGameCharacter character0,
                                                HandWeapon weapon,
                                                IsoGameCharacter character1,
                                                int int0, float float2) {
  // TODO: Implement DoSwingCollisionBoneCheck
  return 0;
}

void SwipeStatePlayer::animEvent(IsoGameCharacter owner, AnimEvent event) {
  // TODO: Implement animEvent
}

void SwipeStatePlayer::exit(IsoGameCharacter owner) {
  // TODO: Implement exit
}

void SwipeStatePlayer::CalcAttackVars(IsoLivingCharacter owner,
                                      AttackVars vars) {
  // TODO: Implement CalcAttackVars
}

bool SwipeStatePlayer::shouldIgnoreProneZombies(IsoGameCharacter character,
                                                ArrayList<HitInfo> arrayList,
                                                float float0) {
  // TODO: Implement shouldIgnoreProneZombies
  return false;
}

bool SwipeStatePlayer::isUnhittableTarget(IsoGameCharacter character,
                                          HandWeapon weapon, float float1,
                                          float float0, HitInfo hitInfo,
                                          bool boolean0) {
  // TODO: Implement isUnhittableTarget
  return false;
}

bool SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter character0,
                                                 HandWeapon weapon,
                                                 IsoMovingObject movingObject,
                                                 bool boolean0,
                                                 Vector4f vector4f) {
  // TODO: Implement getNearestTargetPosAndDot
  return false;
}

void SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter character,
                                                 Vector3 vector0,
                                                 Vector2 vector1,
                                                 Vector4f vector4f) {
  // TODO: Implement getNearestTargetPosAndDot
}

void SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter character,
                                                 IsoMovingObject movingObject,
                                                 const std::string &string,
                                                 Vector2 vector1,
                                                 Vector4f vector4f) {
  // TODO: Implement getNearestTargetPosAndDot
}

void SwipeStatePlayer::getNearestTargetPosAndDot(IsoGameCharacter character1,
                                                 IsoMovingObject movingObject,
                                                 Vector4f vector4f) {
  // TODO: Implement getNearestTargetPosAndDot
}

HitInfo SwipeStatePlayer::calcValidTarget(IsoLivingCharacter livingCharacter,
                                          HandWeapon weapon,
                                          IsoMovingObject movingObject,
                                          float float3) {
  // TODO: Implement calcValidTarget
  return nullptr;
}

bool SwipeStatePlayer::isProne(IsoMovingObject obj) {
  // TODO: Implement isProne
  return false;
}

bool SwipeStatePlayer::isStanding(IsoMovingObject obj) {
  // TODO: Implement isStanding
  return false;
}

bool SwipeStatePlayer::isProneTargetBetter(IsoGameCharacter owner,
                                           HitInfo bestStanding,
                                           HitInfo bestProne) {
  // TODO: Implement isProneTargetBetter
  return false;
}

bool SwipeStatePlayer::checkPVP(IsoGameCharacter owner, IsoMovingObject obj) {
  // TODO: Implement checkPVP
  return false;
}

void SwipeStatePlayer::CalcHitListShove(IsoGameCharacter character0,
                                        bool boolean1, AttackVars attackVars,
                                        ArrayList<HitInfo> arrayList1) {
  // TODO: Implement CalcHitListShove
}

void SwipeStatePlayer::CalcHitListWeapon(IsoGameCharacter character0,
                                         bool boolean1, AttackVars attackVars,
                                         ArrayList<HitInfo> arrayList1) {
  // TODO: Implement CalcHitListWeapon
}

void SwipeStatePlayer::CalcHitListWindow(IsoGameCharacter character,
                                         HandWeapon weapon,
                                         ArrayList<HitInfo> arrayList1) {
  // TODO: Implement CalcHitListWindow
}

void SwipeStatePlayer::CalcHitList(IsoGameCharacter owner, bool extraRange,
                                   AttackVars attackVars,
                                   ArrayList<HitInfo> hitList) {
  // TODO: Implement CalcHitList
}

void SwipeStatePlayer::filterTargetsByZ(IsoGameCharacter character) {
  // TODO: Implement filterTargetsByZ
}

int SwipeStatePlayer::CalcHitChance(IsoGameCharacter owner, HandWeapon weapon,
                                    HitInfo hitInfo) {
  // TODO: Implement CalcHitChance
  return 0;
}

Vector3 SwipeStatePlayer::getBoneWorldPos(IsoMovingObject target,
                                          const std::string &boneName,
                                          Vector3 bonePos) {
  // TODO: Implement getBoneWorldPos
  return nullptr;
}

void SwipeStatePlayer::ConnectSwing(IsoGameCharacter owner, HandWeapon weapon) {
  // TODO: Implement ConnectSwing
}

int SwipeStatePlayer::calcDamageToVehicle(int int0, int int2, bool boolean0) {
  // TODO: Implement calcDamageToVehicle
  return 0;
}

void SwipeStatePlayer::splash(IsoMovingObject obj, HandWeapon weapon,
                              IsoGameCharacter owner) {
  // TODO: Implement splash
}

bool SwipeStatePlayer::checkObjectHit(IsoGameCharacter character,
                                      HandWeapon weapon, IsoGridSquare square,
                                      bool boolean1, bool boolean0) {
  // TODO: Implement checkObjectHit
  return false;
}

bool SwipeStatePlayer::CheckObjectHit(IsoGameCharacter character,
                                      HandWeapon weapon) {
  // TODO: Implement CheckObjectHit
  return false;
}

IsoWindow SwipeStatePlayer::getWindowBetween(int int0, int int1, int int2,
                                             int int3, int int4) {
  // TODO: Implement getWindowBetween
  return nullptr;
}

IsoWindow SwipeStatePlayer::getWindowBetween(IsoMovingObject movingObject0,
                                             IsoMovingObject movingObject1) {
  // TODO: Implement getWindowBetween
  return nullptr;
}

bool SwipeStatePlayer::isWindowBetween(IsoMovingObject movingObject0,
                                       IsoMovingObject movingObject1) {
  // TODO: Implement isWindowBetween
  return false;
}

void SwipeStatePlayer::smashWindowBetween(IsoGameCharacter character,
                                          IsoMovingObject movingObject,
                                          HandWeapon weapon) {
  // TODO: Implement smashWindowBetween
}

void SwipeStatePlayer::changeWeapon(HandWeapon weapon, IsoGameCharacter owner) {
  // TODO: Implement changeWeapon
}

void SwipeStatePlayer::setParameterCharacterHitResult(
    IsoGameCharacter character, IsoZombie zombie0, long long0) {
  // TODO: Implement setParameterCharacterHitResult
}

int SwipeStatePlayer::compare(HitInfo hitInfo0, HitInfo hitInfo1) {
  // TODO: Implement compare
  return 0;
}

bool SwipeStatePlayer::visit(IsoGridSquare var1, IsoGridSquare var2) {
  // TODO: Implement visit
  return false;
}

void SwipeStatePlayer::init() {
  // TODO: Implement init
}

bool SwipeStatePlayer::visit(IsoGridSquare square1, IsoGridSquare square0) {
  // TODO: Implement visit
  return false;
}

bool SwipeStatePlayer::isHittable(IsoWindow windowx) {
  // TODO: Implement isHittable
  return false;
}

} // namespace states
} // namespace ai
} // namespace zombie
