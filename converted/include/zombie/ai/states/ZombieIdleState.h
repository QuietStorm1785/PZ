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
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/objects/RainManager.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieIdleState : public State {
public:
 static const ZombieIdleState _instance = new ZombieIdleState();
 static const int PARAM_TICK_COUNT = 0;

 static ZombieIdleState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 ((IsoZombie)owner).soundSourceTarget = nullptr;
 ((IsoZombie)owner).soundAttract = 0.0F;
 ((IsoZombie)owner).movex = 0.0F;
 ((IsoZombie)owner).movey = 0.0F;
 owner.setStateEventDelayTimer(this->pickRandomWanderInterval());
 if (IngameState.instance == nullptr) {
 hashMap.put(PARAM_TICK_COUNT, 0L);
 } else {
 hashMap.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
 }
 }

 void execute(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 zombie0.movex = 0.0F;
 zombie0.movey = 0.0F;
 if (Core.bLastStand) {
 IsoPlayer player = nullptr;
 float float0 = 1000000.0F;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 if (IsoPlayer.players[int0] != nullptr && IsoPlayer.players[int0].DistTo(owner) < float0 && !IsoPlayer.players[int0].isDead()) {
 float0 = IsoPlayer.players[int0].DistTo(owner);
 player = IsoPlayer.players[int0];
 }
 }

 if (player != nullptr) {
 zombie0.pathToCharacter(player);
 }
 } else {
 if (((IsoZombie)owner).bCrawling) {
 owner.setOnFloor(true);
 } else {
 owner.setOnFloor(false);
 }

 long long0 = (Long)hashMap.get(PARAM_TICK_COUNT);
 if (IngameState.instance.numberTicks - long0 == 2L) {
 ((IsoZombie)owner).parameterZombieState.setState(ParameterZombieState.State.Idle);
 }

 if (!zombie0.bIndoorZombie) {
 if (!zombie0.isUseless()) {
 if (zombie0.getStateEventDelayTimer() <= 0.0F) {
 owner.setStateEventDelayTimer(this->pickRandomWanderInterval());
 int int1 = (int)owner.getX() + (Rand.Next(8) - 4);
 int int2 = (int)owner.getY() + (Rand.Next(8) - 4);
 if (owner.getCell().getGridSquare((double)int1, (double)int2, (double)owner.getZ()) != nullptr
 && owner.getCell().getGridSquare((double)int1, (double)int2, (double)owner.getZ()).isFree(true) {
 owner.pathToLocation(int1, int2, (int)owner.getZ());
 zombie0.AllowRepathDelay = 200.0F;
 }
 }

 zombie0.networkAI.mindSync.zombieIdleUpdate();
 }
 }
 }
 }

 void exit(IsoGameCharacter owner) {
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 }

 float pickRandomWanderInterval() {
 float float0 = Rand.Next(400, 1000);
 if (!RainManager.isRaining()) {
 float0 *= 1.5F;
 }

 return float0;
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
