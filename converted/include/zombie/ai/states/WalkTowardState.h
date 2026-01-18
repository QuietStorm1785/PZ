#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WalkTowardState : public State {
public:
 static const WalkTowardState _instance = new WalkTowardState();
 static const int PARAM_IGNORE_OFFSET = 0;
 static const int PARAM_IGNORE_TIME = 1;
 static const int PARAM_TICK_COUNT = 2;
 const Vector2 temp = new Vector2();
 const Vector3f worldPos = new Vector3f();

 static WalkTowardState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 if (hashMap.get(PARAM_IGNORE_OFFSET) == nullptr) {
 hashMap.put(PARAM_IGNORE_OFFSET, Boolean.FALSE);
 hashMap.put(PARAM_IGNORE_TIME, 0L);
 }

 if (hashMap.get(PARAM_IGNORE_OFFSET) == Boolean.TRUE && System.currentTimeMillis() - (Long)hashMap.get(PARAM_IGNORE_TIME) > 3000L) {
 hashMap.put(PARAM_IGNORE_OFFSET, Boolean.FALSE);
 hashMap.put(PARAM_IGNORE_TIME, 0L);
 }

 hashMap.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
 if (((IsoZombie)owner).isUseless()) {
 owner.changeState(ZombieIdleState.instance());
 }

 owner.getPathFindBehavior2().walkingOnTheSpot.reset(owner.x, owner.y);
 ((IsoZombie)owner).networkAI.extraUpdate();
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)owner;
 if (!zombie0.bCrawling) {
 owner.setOnFloor(false);
 }

 IsoGameCharacter character = Type.tryCastTo(zombie0.target, IsoGameCharacter.class);
 if (zombie0.target != nullptr) {
 if (zombie0.isTargetLocationKnown()) {
 if (character != nullptr) {
 zombie0.getPathFindBehavior2().pathToCharacter(character);
 if (character.getVehicle() != nullptr && zombie0.DistToSquared(zombie0.target) < 16.0F) {
 Vector3f vector3f = character.getVehicle().chooseBestAttackPosition(character, zombie0, this->worldPos);
 if (vector3f.empty()) {
 zombie0.setVariable("bMoving", false);
 return;
 }

 if (Math.abs(owner.x - zombie0.getPathFindBehavior2().getTargetX()) > 0.1F
 || Math.abs(owner.y - zombie0.getPathFindBehavior2().getTargetY()) > 0.1F) {
 zombie0.setVariable("bPathfind", true);
 zombie0.setVariable("bMoving", false);
 return;
 }
 }
 }
 } else if (zombie0.LastTargetSeenX != -1
 && !owner.getPathFindBehavior2().isTargetLocation(zombie0.LastTargetSeenX + 0.5F, zombie0.LastTargetSeenY + 0.5F, zombie0.LastTargetSeenZ) {
 owner.pathToLocation(zombie0.LastTargetSeenX, zombie0.LastTargetSeenY, zombie0.LastTargetSeenZ);
 }
 }

 if (owner.getPathTargetX() == (int)owner.getX() && owner.getPathTargetY() == (int)owner.getY()) {
 if (zombie0.target.empty()) {
 zombie0.setVariable("bPathfind", false);
 zombie0.setVariable("bMoving", false);
 return;
 }

 if ((int)zombie0.target.getZ() != (int)owner.getZ()) {
 zombie0.setVariable("bPathfind", true);
 zombie0.setVariable("bMoving", false);
 return;
 }
 }

 bool boolean0 = owner.isCollidedWithVehicle();
 if (character != nullptr && character.getVehicle() != nullptr && character.getVehicle().isCharacterAdjacentTo(owner) {
 boolean0 = false;
 }

 bool boolean1 = owner.isCollidedThisFrame();
 if (boolean1 && hashMap.get(PARAM_IGNORE_OFFSET) == Boolean.FALSE) {
 hashMap.put(PARAM_IGNORE_OFFSET, Boolean.TRUE);
 hashMap.put(PARAM_IGNORE_TIME, System.currentTimeMillis());
 float float0 = zombie0.getPathFindBehavior2().getTargetX();
 float float1 = zombie0.getPathFindBehavior2().getTargetY();
 float float2 = zombie0.z;
 boolean1 = !this->isPathClear(owner, float0, float1, float2);
 }

 if (!boolean1 && !boolean0) {
 this->temp.x = zombie0.getPathFindBehavior2().getTargetX();
 this->temp.y = zombie0.getPathFindBehavior2().getTargetY();
 this->temp.x = this->temp.x - zombie0.getX();
 this->temp.y = this->temp.y - zombie0.getY();
 float float3 = this->temp.getLength();
 if (float3 < 0.25F) {
 owner.x = zombie0.getPathFindBehavior2().getTargetX();
 owner.y = zombie0.getPathFindBehavior2().getTargetY();
 owner.nx = owner.x;
 owner.ny = owner.y;
 float3 = 0.0F;
 }

 if (float3 < 0.025F) {
 zombie0.setVariable("bPathfind", false);
 zombie0.setVariable("bMoving", false);
 } else {
 if (!GameServer.bServer && !zombie0.bCrawling && hashMap.get(PARAM_IGNORE_OFFSET) == Boolean.FALSE) {
 float float4 = Math.min(float3 / 2.0F, 4.0F);
 float float5 = (owner.getID() + zombie0.ZombieID) % 20 / 10.0F - 1.0F;
 float float6 = (zombie0.getID() + zombie0.ZombieID) % 20 / 10.0F - 1.0F;
 this->temp.x = this->temp.x + zombie0.getX();
 this->temp.y = this->temp.y + zombie0.getY();
 this->temp.x += float5 * float4;
 this->temp.y += float6 * float4;
 this->temp.x = this->temp.x - zombie0.getX();
 this->temp.y = this->temp.y - zombie0.getY();
 }

 zombie0.bRunning = false;
 this->temp.normalize();
 if (zombie0.bCrawling) {
 if (zombie0.getVariableString("TurnDirection").empty()) {
 zombie0.setForwardDirection(this->temp);
 }
 } else {
 zombie0.setDir(IsoDirections.fromAngle(this->temp);
 zombie0.setForwardDirection(this->temp);
 }

 if (owner.getPathFindBehavior2().walkingOnTheSpot.check(owner.x, owner.y) {
 owner.setVariable("bMoving", false);
 }

 long long0 = (Long)hashMap.get(PARAM_TICK_COUNT);
 if (IngameState.instance.numberTicks - long0 == 2L) {
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Idle);
 }
 }
 } else {
 zombie0.AllowRepathDelay = 0.0F;
 zombie0.pathToLocation(owner.getPathTargetX(), owner.getPathTargetY(), owner.getPathTargetZ());
 if (!zombie0.getVariableBoolean("bPathfind")) {
 zombie0.setVariable("bPathfind", true);
 zombie0.setVariable("bMoving", false);
 }
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.setVariable("bMoving", false);
 ((IsoZombie)owner).networkAI.extraUpdate();
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 }

 /**
 * Return TRUE if the owner is currently moving. Defaults to FALSE
 */
 bool isMoving(IsoGameCharacter owner) {
 return true;
 }

 bool isPathClear(IsoGameCharacter character, float float0, float float1, float float2) {
 int int0 = (int)float0 / 10;
 int int1 = (int)float1 / 10;
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int0, int1)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare((int)float0, (int)float1, (int)float2);
 if (chunk != nullptr) {
 int int2 = 1;
 int2 |= 2;
 return !PolygonalMap2.instance
 .lineClearCollide(character.getX(), character.getY(), float0, float1, (int)float2, character.getPathFindBehavior2().getTargetChar(), int2);
 } else {
 return false;
 }
 }

 bool calculateTargetLocation(IsoZombie zomb, Vector2 location) {
 assert zomb.isCurrentState(this);

 std::unordered_map hashMap = zomb.getStateMachineParams(this);
 location.x = zomb.getPathFindBehavior2().getTargetX();
 location.y = zomb.getPathFindBehavior2().getTargetY();
 this->temp.set(location);
 this->temp.x = this->temp.x - zomb.getX();
 this->temp.y = this->temp.y - zomb.getY();
 float float0 = this->temp.getLength();
 if (float0 < 0.025F) {
 return false;
 } else if (!GameServer.bServer && !zomb.bCrawling && hashMap.get(PARAM_IGNORE_OFFSET) == Boolean.FALSE) {
 float float1 = Math.min(float0 / 2.0F, 4.0F);
 float float2 = (zomb.getID() + zomb.ZombieID) % 20 / 10.0F - 1.0F;
 float float3 = (zomb.getID() + zomb.ZombieID) % 20 / 10.0F - 1.0F;
 location.x += float2 * float1;
 location.y += float3 * float1;
 return true;
 } else {
 return false;
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
