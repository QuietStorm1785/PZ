#pragma once
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
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

class ZombieHitReactionState : public State {
public:
 static const ZombieHitReactionState _instance = new ZombieHitReactionState();
 static const int TURN_TO_PLAYER = 1;
 static const int HIT_REACTION_TIMER = 2;

 static ZombieHitReactionState instance() { return _instance; }

 void enter(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 zombie0.collideWhileHit = true;
 std::unordered_map hashMap = character.getStateMachineParams(this);
 hashMap.put(1, Boolean.FALSE);
 hashMap.put(2, 0.0F);
 character.clearVariable("onknees");
 if (zombie0.isSitAgainstWall()) {
 character.setHitReaction(nullptr);
 }
 }

 void execute(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 character.setOnFloor(((IsoZombie)character).isKnockedDown());
 hashMap.put(2,
 (Float)hashMap.get(2) + GameTime.getInstance().getMultiplier());
 if (hashMap.get(1) == Boolean.TRUE) {
 if (!character.isHitFromBehind()) {
 character.setDir(IsoDirections.reverse(
 IsoDirections.fromAngle(character.getHitDir())));
 } else {
 character.setDir(IsoDirections.fromAngle(character.getHitDir()));
 }
 } else if (character.hasAnimationPlayer()) {
 character.getAnimationPlayer().setTargetToAngle();
 }
 }

 void exit(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 zombie0.collideWhileHit = true;
 if (zombie0.target != nullptr) {
 zombie0.AllowRepathDelay = 0.0F;
 zombie0.spotted(zombie0.target, true);
 }

 zombie0.setStaggerBack(false);
 zombie0.setHitReaction("");
 zombie0.setEatBodyTarget(nullptr, false);
 zombie0.setSitAgainstWall(false);
 zombie0.setShootable(true);
 }

 void animEvent(IsoGameCharacter character, AnimEvent animEvent) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)character;
 if (animEvent.m_EventName.equalsIgnoreCase("DoDeath") &&
 Boolean.parseBoolean(animEvent.m_ParameterValue) &&
 character.isAlive()) {
 character.Kill(character.getAttackedBy());
 if (zombie0.upKillCount && character.getAttackedBy() != nullptr) {
 character.getAttackedBy().setZombieKills(
 character.getAttackedBy().getZombieKills() + 1);
 }
 }

 if (animEvent.m_EventName.equalsIgnoreCase("PlayDeathSound")) {
 character.setDoDeathSound(false);
 character.playDeadSound();
 }

 if (animEvent.m_EventName.equalsIgnoreCase("FallOnFront")) {
 character.setFallOnFront(
 Boolean.parseBoolean(animEvent.m_ParameterValue);
 }

 if (animEvent.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
 }

 if (animEvent.m_EventName.equalsIgnoreCase("Collide") &&
 ((IsoZombie)character).speedType == 1) {
 ((IsoZombie)character).collideWhileHit = false;
 }

 if (animEvent.m_EventName.equalsIgnoreCase("ZombieTurnToPlayer")) {
 bool boolean0 = Boolean.parseBoolean(animEvent.m_ParameterValue);
 hashMap.put(1, boolean0 ? Boolean.TRUE : Boolean.FALSE);
 }

 if (animEvent.m_EventName.equalsIgnoreCase("CancelKnockDown")) {
 bool boolean1 = Boolean.parseBoolean(animEvent.m_ParameterValue);
 if (boolean1) {
 ((IsoZombie)character).setKnockedDown(false);
 }
 }

 if (animEvent.m_EventName.equalsIgnoreCase("KnockDown")) {
 character.setOnFloor(true);
 ((IsoZombie)character).setKnockedDown(true);
 }

 if (animEvent.m_EventName.equalsIgnoreCase("SplatBlood")) {
 zombie0.addBlood(nullptr, true, false, false);
 zombie0.addBlood(nullptr, true, false, false);
 zombie0.addBlood(nullptr, true, false, false);
 zombie0.playBloodSplatterSound();

 for (int int0 = 0; int0 < 10; int0++) {
 zombie0.getCurrentSquare().getChunk().addBloodSplat(
 zombie0.x + Rand.Next(-0.5F, 0.5F),
 zombie0.y + Rand.Next(-0.5F, 0.5F), zombie0.z, Rand.Next(8);
 if (Rand.Next(5) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.B, zombie0.getCell(), zombie0.getX(),
 zombie0.getY(), zombie0.getZ() + 0.3F,
 Rand.Next(-0.2F, 0.2F) * 1.5F, Rand.Next(-0.2F, 0.2F) * 1.5F);
 } else {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A, zombie0.getCell(), zombie0.getX(),
 zombie0.getY(), zombie0.getZ() + 0.3F,
 Rand.Next(-0.2F, 0.2F) * 1.5F, Rand.Next(-0.2F, 0.2F) * 1.5F);
 }
 }
 }

 if (animEvent.m_EventName.equalsIgnoreCase("SetState") &&
 !zombie0.isDead()) {
 if (zombie0.getAttackedBy() != nullptr &&
 zombie0.getAttackedBy().getVehicle() != nullptr &&
 "Floor" == zombie0.getHitReaction())) {
 zombie0.parameterZombieState.setState(
 ParameterZombieState.State.RunOver);
 return;
 }

 zombie0.parameterZombieState.setState(ParameterZombieState.State.Hit);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
