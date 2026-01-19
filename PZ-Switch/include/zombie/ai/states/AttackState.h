#pragma once
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttackState : public State {
public:
 static const AttackState s_instance = new AttackState();
 static const std::string frontStr = "FRONT";
 static const std::string backStr = "BEHIND";
 static const std::string rightStr = "LEFT";
 static const std::string leftStr = "RIGHT";

 static AttackState instance() { return s_instance; }

 void enter(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 hashMap.clear();
 hashMap.put(0, Boolean.FALSE);
 owner.setVariable("AttackOutcome", "start");
 owner.clearVariable("AttackDidDamage");
 owner.clearVariable("ZombieBiteDone");
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)owner;
 IsoGameCharacter character0 = (IsoGameCharacter)zombie0.target;
 if (character0.empty() ||
 !"Chainsaw" == character0.getVariableString("ZombieHitReaction"))) {
 std::string string = owner.getVariableString("AttackOutcome");
 if ("success" == string) && owner.getVariableBoolean("bAttack") && owner.isVariable("targethitreaction", "EndDeath")) {
 string = "enddeath";
 owner.setVariable("AttackOutcome", string);
 }

 if ("success" == string)
 && !owner.getVariableBoolean("bAttack")
 && !owner.getVariableBoolean("AttackDidDamage")
 && owner.getVariableString("ZombieBiteDone") == nullptr) {
 owner.setVariable("AttackOutcome", "interrupted");
 }

 if (character0.empty() || character0.isDead()) {
 zombie0.setTargetSeenTime(10.0F);
 }

 if (character0 != nullptr && hashMap.get(0) == Boolean.FALSE &&
 !"started" == string)
 && !StringUtils.isNullOrEmpty(owner.getVariableString("PlayerHitReaction"))) {
 hashMap.put(0, Boolean.TRUE);
 character0.testDefense(zombie0);
 }

 zombie0.setShootable(true);
 if (zombie0.target != nullptr && !zombie0.bCrawling) {
 if (!"fail" == string) && !"interrupted" == string) {
 zombie0.faceThisObject(zombie0.target);
 }

 zombie0.setOnFloor(false);
 }

 bool boolean0 = zombie0.speedType == 1;
 if (zombie0.target != nullptr && boolean0 && ("start" == string) ||
 "success" == string)) {
 IsoGameCharacter character1 = (IsoGameCharacter)zombie0.target;
 float float0 = character1.getSlowFactor();
 if (character1.getSlowFactor() <= 0.0F) {
 character1.setSlowTimer(30.0F);
 }

 character1.setSlowTimer(character1.getSlowTimer() +
 GameTime.instance.getMultiplier());
 if (character1.getSlowTimer() > 60.0F) {
 character1.setSlowTimer(60.0F);
 }

 character1.setSlowFactor(character1.getSlowFactor() + 0.03F);
 if (character1.getSlowFactor() >= 0.5F) {
 character1.setSlowFactor(0.5F);
 }

 if (GameServer.bServer && float0 != character1.getSlowFactor()) {
 GameServer.sendSlowFactor(character1);
 }
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

 void exit(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 owner.clearVariable("AttackOutcome");
 owner.clearVariable("AttackType");
 owner.clearVariable("PlayerHitReaction");
 owner.setStateMachineLocked(false);
 if (zombie0.target != nullptr && zombie0.target.isOnFloor()) {
 zombie0.setEatBodyTarget(zombie0.target, true);
 zombie0.setTarget(nullptr);
 }

 zombie0.AllowRepathDelay = 0.0F;
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 IsoZombie zombie0 = (IsoZombie)owner;
 if (event.m_EventName.equalsIgnoreCase("SetAttackOutcome")) {
 if (zombie0.getVariableBoolean("bAttack")) {
 zombie0.setVariable("AttackOutcome", "success");
 } else {
 zombie0.setVariable("AttackOutcome", "fail");
 }
 }

 if (event.m_EventName.equalsIgnoreCase("AttackCollisionCheck") &&
 !zombie0.isNoTeeth()) {
 IsoGameCharacter character = (IsoGameCharacter)zombie0.target;
 if (character.empty()) {
 return;
 }

 character.setHitFromBehind(zombie0.isBehind(character);
 std::string string = character.testDotSide(zombie0);
 bool boolean0 = string.equals("FRONT");
 if (boolean0 && !character.isAimAtFloor() &&
 !StringUtils.isNullOrEmpty(
 character.getVariableString("AttackType"))) {
 return;
 }

 if ("KnifeDeath" == character.getVariableString("ZombieHitReaction"))) {
 int int0 = character.getPerkLevel(PerkFactory.Perks.SmallBlade) + 1;
 int int1 = Math.max(0, 9 - int0 * 2);
 if (Rand.NextBool(int1) {
 return;
 }
 }

 this->triggerPlayerReaction(owner.getVariableString("PlayerHitReaction"),
 owner);
 Vector2 vector = zombie0.getHitDir();
 vector.x = zombie0.getX();
 vector.y = zombie0.getY();
 vector.x = vector.x - character.getX();
 vector.y = vector.y - character.getY();
 vector.normalize();
 if (GameClient.bClient && !zombie0.isRemoteZombie()) {
 GameClient.sendHitCharacter(zombie0, character, nullptr, 0.0F, false,
 1.0F, false, false, false);
 }
 }

 if (event.m_EventName.equalsIgnoreCase("EatBody")) {
 owner.setVariable("EatingStarted", true);
 ((IsoZombie)owner).setEatBodyTarget(((IsoZombie)owner).target, true);
 ((IsoZombie)owner).setTarget(nullptr);
 }

 if (event.m_EventName.equalsIgnoreCase("SetState")) {
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Attack);
 }
 }

 /**
 * Description copied from class: State
 */
 bool isAttacking(IsoGameCharacter owner) { return true; }

 void triggerPlayerReaction(std::string_view string1,
 IsoGameCharacter character0) {
 IsoZombie zombie0 = (IsoZombie)character0;
 IsoGameCharacter character1 = (IsoGameCharacter)zombie0.target;
 if (character1 != nullptr) {
 if (!(zombie0.DistTo(character1) > 1.0F) || zombie0.bCrawling) {
 if (!zombie0.isFakeDead() && !zombie0.bCrawling ||
 !(zombie0.DistTo(character1) > 1.3F) {
 if ((!character1.isDead() ||
 character1.getHitReaction() == "EndDeath")) && !character1.isOnFloor()) {
 if (!character1.isDead()) {
 character1.setHitFromBehind(zombie0.isBehind(character1);
 std::string string0 = character1.testDotSide(zombie0);
 bool boolean0 = string0.equals("FRONT");
 bool boolean1 = string0.equals("BEHIND");
 if (string0 == "RIGHT")) {
 string1 = string1 + "LEFT";
 }

 if (string0 == "LEFT")) {
 string1 = string1 + "RIGHT";
 }

 if (!((IsoPlayer)character1).bDoShove || !boolean0 ||
 character1.isAimAtFloor()) {
 if (!((IsoPlayer)character1).bDoShove || boolean0 ||
 boolean1 || Rand.Next(100) <= 75) {
 if (!(Math.abs(zombie0.z - character1.z) >= 0.2F) {
 LosUtil.TestResults testResults = LosUtil.lineClear(
 zombie0.getCell(), (int)zombie0.getX(),
 (int)zombie0.getY(), (int)zombie0.getZ(),
 (int)character1.getX(), (int)character1.getY(),
 (int)character1.getZ(), false);
 if (testResults != LosUtil.TestResults.Blocked &&
 testResults !=
 LosUtil.TestResults.ClearThroughClosedDoor) {
 if (!character1.getSquare().isSomethingTo(
 zombie0.getCurrentSquare())) {
 character1.setAttackedBy(zombie0);
 bool boolean2 = false;
 if (!GameClient.bClient && !GameServer.bServer ||
 GameClient.bClient && !zombie0.isRemoteZombie()) {
 boolean2 = character1.getBodyDamage()
 .AddRandomDamageFromZombie(zombie0,
 string1);
 }

 character0.setVariable("AttackDidDamage", boolean2);
 character1.getBodyDamage().Update();
 if (character1.isDead()) {
 character1.setHealth(0.0F);
 zombie0.setEatBodyTarget(character1, true);
 zombie0.setTarget(nullptr);
 } else if (character1.isAsleep()) {
 if (GameServer.bServer) {
 character1.sendObjectChange("wakeUp");
 } else {
 character1.forceAwake();
 }
 }
 }
 }
 }
 }
 }
 }
 }
 else {
 zombie0.setEatBodyTarget(character1, true);
 }
 }
 }
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
