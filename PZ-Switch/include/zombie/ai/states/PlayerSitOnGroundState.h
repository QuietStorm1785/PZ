#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PlayerSitOnGroundState : public State {
public:
 static const PlayerSitOnGroundState _instance = new PlayerSitOnGroundState();
 static const int RAND_EXT = 2500;
 static const int PARAM_FIRE = 0;
 static const int PARAM_SITGROUNDANIM = 1;
 static const int PARAM_CHECK_FIRE = 2;
 static const int PARAM_CHANGE_ANIM = 3;

 static PlayerSitOnGroundState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 hashMap.put(PARAM_FIRE, this->checkFire(owner);
 hashMap.put(PARAM_CHECK_FIRE, System.currentTimeMillis());
 hashMap.put(PARAM_CHANGE_ANIM, 0L);
 owner.setSitOnGround(true);
 if ((owner.getPrimaryHandItem() == nullptr ||
 !(owner.getPrimaryHandItem() instanceof HandWeapon) &&
 (owner.getSecondaryHandItem() == nullptr ||
 !(owner.getSecondaryHandItem() instanceof HandWeapon)) {
 owner.setHideWeaponModel(true);
 }

 if (owner.getStateMachine().getPrevious() == IdleState.instance()) {
 owner.clearVariable("SitGroundStarted");
 owner.clearVariable("forceGetUp");
 owner.clearVariable("SitGroundAnim");
 }
 }

 bool checkFire(IsoGameCharacter character) {
 IsoGridSquare square0 = character.getCurrentSquare();

 for (int int0 = -4; int0 < 4; int0++) {
 for (int int1 = -4; int1 < 4; int1++) {
 IsoGridSquare square1 = square0.getCell().getGridSquare(
 square0.x + int0, square0.y + int1, square0.z);
 if (square1 != nullptr) {
 if (square1.haveFire()) {
 return true;
 }

 for (int int2 = 0; int2 < square1.getObjects().size(); int2++) {
 IsoFireplace fireplace = Type.tryCastTo(
 square1.getObjects().get(int2), IsoFireplace.class);
 if (fireplace != nullptr && fireplace.isLit()) {
 return true;
 }
 }
 }
 }
 }

 return false;
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoPlayer player = (IsoPlayer)owner;
 if (player.pressedMovement(false) {
 owner.StopAllActionQueue();
 owner.setVariable("forceGetUp", true);
 }

 long long0 = System.currentTimeMillis();
 if (long0 > (Long)hashMap.get(PARAM_CHECK_FIRE) + 5000L) {
 hashMap.put(PARAM_FIRE, this->checkFire(owner);
 hashMap.put(PARAM_CHECK_FIRE, long0);
 }

 if (owner.hasTimedActions()) {
 hashMap.put(PARAM_FIRE, false);
 owner.setVariable("SitGroundAnim", "Idle");
 }

 bool boolean0 = (Boolean)hashMap.get(PARAM_FIRE);
 if (boolean0) {
 bool boolean1 = long0 > (Long)hashMap.get(PARAM_CHANGE_ANIM);
 if (boolean1) {
 if ("Idle" == owner.getVariableString("SitGroundAnim"))) {
 owner.setVariable("SitGroundAnim", "WarmHands");
 }
 else if ("WarmHands" == owner.getVariableString("SitGroundAnim"))) {
 owner.setVariable("SitGroundAnim", "Idle");
 }

 hashMap.put(PARAM_CHANGE_ANIM, long0 + Rand.Next(30000, 90000);
 }
 } else if (owner.getVariableBoolean("SitGroundStarted")) {
 owner.clearVariable("FireNear");
 owner.setVariable("SitGroundAnim", "Idle");
 }

 if ("WarmHands" == owner.getVariableString("SitGroundAnim")) && Rand.Next(Rand.AdjustForFramerate(2500) == 0) {
 hashMap.put(PARAM_SITGROUNDANIM,
 owner.getVariableString("SitGroundAnim"));
 owner.setVariable("SitGroundAnim", "rubhands");
 }

 player.setInitiateAttack(false);
 player.attackStarted = false;
 player.setAttackType(nullptr);
 }

 void exit(IsoGameCharacter owner) {
 owner.setHideWeaponModel(false);
 if (StringUtils.isNullOrEmpty(owner.getVariableString("HitReaction"))) {
 owner.clearVariable("SitGroundStarted");
 owner.clearVariable("forceGetUp");
 owner.clearVariable("SitGroundAnim");
 owner.setIgnoreMovement(false);
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("SitGroundStarted")) {
 owner.setVariable("SitGroundStarted", true);
 bool boolean0 =
 (Boolean)owner.getStateMachineParams(this).get(PARAM_FIRE);
 if (boolean0) {
 owner.setVariable("SitGroundAnim", "WarmHands");
 } else {
 owner.setVariable("SitGroundAnim", "Idle");
 }
 }

 if (event.m_EventName.equalsIgnoreCase("ResetSitOnGroundAnim")) {
 owner.setVariable(
 "SitGroundAnim",
 (String)owner.getStateMachineParams(this).get(PARAM_SITGROUNDANIM);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
