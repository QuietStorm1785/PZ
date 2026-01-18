#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieGetDownState : public State {
public:
 static const ZombieGetDownState _instance = new ZombieGetDownState();
 static const int PARAM_PREV_STATE = 1;
 static const int PARAM_WAIT_TIME = 2;
 static const int PARAM_START_X = 3;
 static const int PARAM_START_Y = 4;

 static ZombieGetDownState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 hashMap.put(PARAM_PREV_STATE, owner.getStateMachine().getPrevious());
 hashMap.put(PARAM_START_X, owner.getX());
 hashMap.put(PARAM_START_Y, owner.getY());
 owner.setStateEventDelayTimer((Float)hashMap.get(PARAM_WAIT_TIME);
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 }

 void exit(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)owner;
 zombie0.setStateEventDelayTimer(0.0F);
 zombie0.AllowRepathDelay = 0.0F;
 if (hashMap.get(PARAM_PREV_STATE) == PathFindState.instance()) {
 if (owner.getPathFindBehavior2().getTargetChar() == nullptr) {
 owner.setVariable("bPathfind", true);
 owner.setVariable("bMoving", false);
 } else if (zombie0.isTargetLocationKnown()) {
 owner.pathToCharacter(owner.getPathFindBehavior2().getTargetChar());
 } else if (zombie0.LastTargetSeenX != -1) {
 owner.pathToLocation(zombie0.LastTargetSeenX, zombie0.LastTargetSeenY, zombie0.LastTargetSeenZ);
 }
 } else if (hashMap.get(PARAM_PREV_STATE) == WalkTowardState.instance()) {
 owner.setVariable("bPathFind", false);
 owner.setVariable("bMoving", true);
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 IsoZombie zombie0 = (IsoZombie)owner;
 if (event.m_EventName.equalsIgnoreCase("StartCrawling") && !zombie0.isCrawling()) {
 zombie0.toggleCrawling();
 }
 }

 bool isNearStartXY(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 float float0 = (Float)hashMap.get(PARAM_START_X);
 float float1 = (Float)hashMap.get(PARAM_START_Y);
 return float0 != nullptr && float1 != nullptr ? owner.DistToSquared(float0, float1) <= 0.25F : false;
 }

 void setParams(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 hashMap.put(PARAM_WAIT_TIME, Rand.Next(60.0F, 150.0F);
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
