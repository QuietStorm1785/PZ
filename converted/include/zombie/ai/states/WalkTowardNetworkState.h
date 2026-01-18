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
#include "zombie/characters/IsoZombie.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables.h"
#include "zombie/network/ServerMap.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WalkTowardNetworkState : public State {
public:
 static WalkTowardNetworkState _instance = std::make_unique<WalkTowardNetworkState>();
 static const int PARAM_TICK_COUNT = 2;

 static WalkTowardNetworkState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 hashMap.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
 character.setVariable("bMoving", true);
 character.setVariable("bPathfind", false);
 }

 void execute(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 PathFindBehavior2 pathFindBehavior2 = zombie0.getPathFindBehavior2();
 zombie0.vectorToTarget.x = zombie0.networkAI.targetX - zombie0.x;
 zombie0.vectorToTarget.y = zombie0.networkAI.targetY - zombie0.y;
 pathFindBehavior2.walkingOnTheSpot.reset(zombie0.x, zombie0.y);
 if (zombie0.z != zombie0.networkAI.targetZ
 || zombie0.networkAI.predictionType != NetworkVariables.PredictionTypes.Thump
 && zombie0.networkAI.predictionType != NetworkVariables.PredictionTypes.Climb) {
 if (zombie0.z == zombie0.networkAI.targetZ
 && !PolygonalMap2.instance
 .lineClearCollide(zombie0.x, zombie0.y, zombie0.networkAI.targetX, zombie0.networkAI.targetY, zombie0.networkAI.targetZ, nullptr) {
 if (zombie0.networkAI.usePathFind) {
 pathFindBehavior2.reset();
 zombie0.setPath2(nullptr);
 zombie0.networkAI.usePathFind = false;
 }

 pathFindBehavior2.moveToPoint(zombie0.networkAI.targetX, zombie0.networkAI.targetY, 1.0F);
 zombie0.setVariable("bMoving", IsoUtils.DistanceManhatten(zombie0.networkAI.targetX, zombie0.networkAI.targetY, zombie0.nx, zombie0.ny) > 0.5F);
 } else {
 if (!zombie0.networkAI.usePathFind) {
 pathFindBehavior2.pathToLocationF(zombie0.networkAI.targetX, zombie0.networkAI.targetY, zombie0.networkAI.targetZ);
 pathFindBehavior2.walkingOnTheSpot.reset(zombie0.x, zombie0.y);
 zombie0.networkAI.usePathFind = true;
 }

 PathFindBehavior2.BehaviorResult behaviorResult = pathFindBehavior2.update();
 if (behaviorResult == PathFindBehavior2.BehaviorResult.Failed) {
 zombie0.setPathFindIndex(-1);
 return;
 }

 if (behaviorResult == PathFindBehavior2.BehaviorResult.Succeeded) {
 int int0 = (int)zombie0.getPathFindBehavior2().getTargetX();
 int int1 = (int)zombie0.getPathFindBehavior2().getTargetY();
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int0 / 10, int1 / 10)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare(int0, int1, 0);
 if (chunk == nullptr) {
 zombie0.setVariable("bMoving", true);
 return;
 }

 zombie0.setPath2(nullptr);
 zombie0.setVariable("bMoving", true);
 return;
 }
 }
 } else {
 if (zombie0.networkAI.usePathFind) {
 pathFindBehavior2.reset();
 zombie0.setPath2(nullptr);
 zombie0.networkAI.usePathFind = false;
 }

 pathFindBehavior2.moveToPoint(zombie0.networkAI.targetX, zombie0.networkAI.targetY, 1.0F);
 zombie0.setVariable("bMoving", IsoUtils.DistanceManhatten(zombie0.networkAI.targetX, zombie0.networkAI.targetY, zombie0.nx, zombie0.ny) > 0.5F);
 }

 if (!((IsoZombie)character).bCrawling) {
 character.setOnFloor(false);
 }

 bool boolean0 = character.isCollidedWithVehicle();
 if (zombie0.target instanceof IsoGameCharacter
 && ((IsoGameCharacter)zombie0.target).getVehicle() != nullptr
 && ((IsoGameCharacter)zombie0.target).getVehicle().isCharacterAdjacentTo(character) {
 boolean0 = false;
 }

 if (character.isCollidedThisFrame() || boolean0) {
 zombie0.AllowRepathDelay = 0.0F;
 zombie0.pathToLocation(character.getPathTargetX(), character.getPathTargetY(), character.getPathTargetZ());
 if (!"true" == zombie0.getVariableString("bPathfind"))) {
 zombie0.setVariable("bPathfind", true);
 zombie0.setVariable("bMoving", false);
 }
 }

 std::unordered_map hashMap = character.getStateMachineParams(this);
 long long0 = (Long)hashMap.get(PARAM_TICK_COUNT);
 if (IngameState.instance.numberTicks - long0 == 2L) {
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Idle);
 }
 }

 void exit(IsoGameCharacter character) {
 character.setVariable("bMoving", false);
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
