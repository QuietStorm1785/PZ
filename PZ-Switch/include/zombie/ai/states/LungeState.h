#pragma once
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
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

class LungeState : public State {
public:
 static const LungeState _instance = new LungeState();
 const Vector2 temp = new Vector2();
 static const int PARAM_TICK_COUNT = 0;

 static LungeState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 if (System.currentTimeMillis() - zombie0.LungeSoundTime > 5000L) {
 std::string string = "MaleZombieAttack";
 if (zombie0.isFemale()) {
 string = "FemaleZombieAttack";
 }

 if (GameServer.bServer) {
 GameServer.sendZombieSound(IsoZombie.ZombieSound.Lunge, zombie0);
 }

 zombie0.LungeSoundTime = System.currentTimeMillis();
 }

 zombie0.LungeTimer = 180.0F;
 hashMap.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
 }

 void execute(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 owner.setOnFloor(false);
 owner.setShootable(true);
 if (zombie0.bLunger) {
 zombie0.walkVariantUse = "ZombieWalk3";
 }

 zombie0.LungeTimer =
 zombie0.LungeTimer - GameTime.getInstance().getMultiplier() / 1.6F;
 IsoPlayer player = Type.tryCastTo(zombie0.getTarget(), IsoPlayer.class);
 if (player != nullptr && player.isGhostMode()) {
 zombie0.LungeTimer = 0.0F;
 }

 if (zombie0.LungeTimer < 0.0F) {
 zombie0.LungeTimer = 0.0F;
 }

 if (zombie0.LungeTimer <= 0.0F) {
 zombie0.AllowRepathDelay = 0.0F;
 }

 this->temp.x = zombie0.vectorToTarget.x;
 this->temp.y = zombie0.vectorToTarget.y;
 zombie0.getZombieLungeSpeed();
 this->temp.normalize();
 zombie0.setForwardDirection(this->temp);
 zombie0.DirectionFromVector(this->temp);
 zombie0.getVectorFromDirection(zombie0.getForwardDirection());
 zombie0.setForwardDirection(this->temp);
 if (!zombie0.isTargetLocationKnown() && zombie0.LastTargetSeenX != -1 &&
 !owner.getPathFindBehavior2().isTargetLocation(
 zombie0.LastTargetSeenX + 0.5F, zombie0.LastTargetSeenY + 0.5F,
 zombie0.LastTargetSeenZ) {
 zombie0.LungeTimer = 0.0F;
 owner.pathToLocation(zombie0.LastTargetSeenX, zombie0.LastTargetSeenY,
 zombie0.LastTargetSeenZ);
 }

 long long0 = (Long)hashMap.get(PARAM_TICK_COUNT);
 if (IngameState.instance.numberTicks - long0 == 2L) {
 ((IsoZombie)owner)
 .parameterZombieState.setState(ParameterZombieState.State.LockTarget);
 }
 }

 void exit(IsoGameCharacter chr) {}

 /**
 * Return TRUE if the owner is currently moving. Defaults to FALSE
 */
 bool isMoving(IsoGameCharacter owner) { return true; }
}
} // namespace states
} // namespace ai
} // namespace zombie
