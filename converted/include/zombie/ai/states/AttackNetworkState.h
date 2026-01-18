#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AttackNetworkState : public State {
public:
 static const AttackNetworkState s_instance = new AttackNetworkState();
 std::string attackOutcome;

 static AttackNetworkState instance() {
 return s_instance;
 }

 void enter(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 std::unordered_map hashMap = character.getStateMachineParams(this);
 hashMap.clear();
 hashMap.put(0, Boolean.FALSE);
 this->attackOutcome = character.getVariableString("AttackOutcome");
 character.setVariable("AttackOutcome", "start");
 character.clearVariable("AttackDidDamage");
 character.clearVariable("ZombieBiteDone");
 zombie0.setTargetSeenTime(1.0F);
 if (!zombie0.bCrawling) {
 zombie0.setVariable("AttackType", "bite");
 }
 }

 void execute(IsoGameCharacter character0) {
 IsoZombie zombie0 = (IsoZombie)character0;
 std::unordered_map hashMap = character0.getStateMachineParams(this);
 IsoGameCharacter character1 = (IsoGameCharacter)zombie0.target;
 if (character1 == nullptr || !"Chainsaw" == character1.getVariableString("ZombieHitReaction"))) {
 std::string string = character0.getVariableString("AttackOutcome");
 if ("success" == string)
 && !character0.getVariableBoolean("bAttack")
 && (character1 == nullptr || !character1.isGodMod())
 && !character0.getVariableBoolean("AttackDidDamage")
 && character0.getVariableString("ZombieBiteDone") != "true") {
 character0.setVariable("AttackOutcome", "interrupted");
 }

 if (character1 == nullptr || character1.isDead()) {
 zombie0.setTargetSeenTime(10.0F);
 }

 if (character1 != nullptr
 && hashMap.get(0) == Boolean.FALSE
 && !"started" == string)
 && !StringUtils.isNullOrEmpty(character0.getVariableString("PlayerHitReaction"))) {
 hashMap.put(0, Boolean.TRUE);
 }

 zombie0.setShootable(true);
 if (zombie0.target != nullptr && !zombie0.bCrawling) {
 if (!"fail" == string) && !"interrupted" == string) {
 zombie0.faceThisObject(zombie0.target);
 }

 zombie0.setOnFloor(false);
 }

 if (zombie0.target != nullptr) {
 zombie0.target.setTimeSinceZombieAttack(0);
 zombie0.target.setLastTargettedBy(zombie0);
 }

 if (!zombie0.bCrawling) {
 zombie0.setVariable("AttackType", "bite");
 }
 }
 }

 void exit(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 character.clearVariable("AttackOutcome");
 character.clearVariable("AttackType");
 character.clearVariable("PlayerHitReaction");
 character.setStateMachineLocked(false);
 if (zombie0.target != nullptr && zombie0.target.isOnFloor()) {
 zombie0.setEatBodyTarget(zombie0.target, true);
 zombie0.setTarget(nullptr);
 }

 zombie0.AllowRepathDelay = 0.0F;
 }

 void animEvent(IsoGameCharacter character, AnimEvent animEvent) {
 IsoZombie zombie0 = (IsoZombie)character;
 if (GameClient.bClient && zombie0.isRemoteZombie()) {
 if (animEvent.m_EventName.equalsIgnoreCase("SetAttackOutcome")) {
 zombie0.setVariable("AttackOutcome", "fail" == this->attackOutcome) ? "fail" : "success");
 }

 if (animEvent.m_EventName.equalsIgnoreCase("AttackCollisionCheck") && zombie0.target instanceof IsoPlayer player) {
 if (zombie0.scratch) {
 zombie0.getEmitter().playSoundImpl("ZombieScratch", zombie0);
 } else if (zombie0.laceration) {
 zombie0.getEmitter().playSoundImpl("ZombieScratch", zombie0);
 } else {
 zombie0.getEmitter().playSoundImpl("ZombieBite", zombie0);
 player.splatBloodFloorBig();
 player.splatBloodFloorBig();
 player.splatBloodFloorBig();
 }
 }

 if (animEvent.m_EventName.equalsIgnoreCase("EatBody")) {
 character.setVariable("EatingStarted", true);
 ((IsoZombie)character).setEatBodyTarget(((IsoZombie)character).target, true);
 ((IsoZombie)character).setTarget(nullptr);
 }
 }

 if (animEvent.m_EventName.equalsIgnoreCase("SetState")) {
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Attack);
 }
 }

 bool isAttacking(IsoGameCharacter var1) {
 return true;
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
