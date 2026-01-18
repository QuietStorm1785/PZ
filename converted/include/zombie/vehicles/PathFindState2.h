#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/ai/astar/AStarPathFinder.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PathFindState2 : public State {
public:
 static const int PARAM_TICK_COUNT = 0;

 void enter(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 character.setVariable("bPathfind", true);
 character.setVariable("bMoving", false);
 ((IsoZombie)character).networkAI.extraUpdate();
 hashMap.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
 }

 void execute(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 PathFindBehavior2.BehaviorResult behaviorResult = character.getPathFindBehavior2().update();
 if (behaviorResult == PathFindBehavior2.BehaviorResult.Failed) {
 character.setPathFindIndex(-1);
 character.setVariable("bPathfind", false);
 character.setVariable("bMoving", false);
 } else if (behaviorResult == PathFindBehavior2.BehaviorResult.Succeeded) {
 int int0 = (int)character.getPathFindBehavior2().getTargetX();
 int int1 = (int)character.getPathFindBehavior2().getTargetY();
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int0 / 10, int1 / 10)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare(int0, int1, 0);
 if (chunk == nullptr) {
 character.setVariable("bPathfind", false);
 character.setVariable("bMoving", true);
 } else {
 character.setVariable("bPathfind", false);
 character.setVariable("bMoving", false);
 character.setPath2(nullptr);
 }
 } else {
 if (character instanceof IsoZombie) {
 long long0 = (Long)hashMap.get(PARAM_TICK_COUNT);
 if (IngameState.instance.numberTicks - long0 == 2L) {
 ((IsoZombie)character).parameterZombieState.setState(ParameterZombieState.State.Idle);
 }
 }
 }
 }

 void exit(IsoGameCharacter character) {
 if (character instanceof IsoZombie) {
 ((IsoZombie)character).networkAI.extraUpdate();
 ((IsoZombie)character).AllowRepathDelay = 0.0F;
 }

 character.setVariable("bPathfind", false);
 character.setVariable("bMoving", false);
 character.setVariable("ShouldBeCrawling", false);
 PolygonalMap2.instance.cancelRequest(character);
 character.getFinder().progress = AStarPathFinder.PathFindProgress.notrunning;
 character.setPath2(nullptr);
 }

 void animEvent(IsoGameCharacter var1, AnimEvent var2) {
 }

 bool isMoving(IsoGameCharacter character) {
 return character.isMoving();
 }
}
} // namespace vehicles
} // namespace zombie
