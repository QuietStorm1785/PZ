#pragma once
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/StringUtils.h"
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

class ZombieGetUpState : public State {
public:
 static const ZombieGetUpState _instance = new ZombieGetUpState();
 static const int PARAM_STANDING = 1;
 static const int PARAM_PREV_STATE = 2;

 static ZombieGetUpState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 hashMap.put(PARAM_STANDING, Boolean.FALSE);
 State state = owner.getStateMachine().getPrevious();
 if (state == ZombieGetUpFromCrawlState.instance()) {
 state = (State)owner
 .getStateMachineParams(ZombieGetUpFromCrawlState.instance())
 .get(1);
 }

 hashMap.put(PARAM_PREV_STATE, state);
 zombie0.parameterZombieState.setState(ParameterZombieState.State.GettingUp);
 if (GameClient.bClient) {
 owner.setKnockedDown(false);
 }
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 bool boolean0 = hashMap.get(PARAM_STANDING) == Boolean.TRUE;
 owner.setOnFloor(!boolean0);
 ((IsoZombie)owner).setKnockedDown(!boolean0);
 }

 void exit(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)owner;
 owner.setCollidable(true);
 owner.clearVariable("SprinterTripped");
 owner.clearVariable("ShouldStandUp");
 if (StringUtils.isNullOrEmpty(owner.getHitReaction())) {
 zombie0.setSitAgainstWall(false);
 }

 zombie0.setKnockedDown(false);
 zombie0.AllowRepathDelay = 0.0F;
 if (hashMap.get(PARAM_PREV_STATE) == PathFindState.instance()) {
 if (owner.getPathFindBehavior2().getTargetChar() == nullptr) {
 owner.setVariable("bPathfind", true);
 owner.setVariable("bMoving", false);
 } else if (zombie0.isTargetLocationKnown()) {
 owner.pathToCharacter(owner.getPathFindBehavior2().getTargetChar());
 } else if (zombie0.LastTargetSeenX != -1) {
 owner.pathToLocation(zombie0.LastTargetSeenX, zombie0.LastTargetSeenY,
 zombie0.LastTargetSeenZ);
 }
 } else if (hashMap.get(PARAM_PREV_STATE) == WalkTowardState.instance()) {
 owner.setVariable("bPathFind", false);
 owner.setVariable("bMoving", true);
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)owner;
 if (event.m_EventName.equalsIgnoreCase("IsAlmostUp")) {
 hashMap.put(PARAM_STANDING, Boolean.TRUE);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
