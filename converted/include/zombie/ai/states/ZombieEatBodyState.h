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
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieEatBodyState : public State {
public:
 static const ZombieEatBodyState _instance = new ZombieEatBodyState();

 static ZombieEatBodyState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 zombie0.setStateEventDelayTimer(Rand.Next(1800.0F, 3600.0F);
 zombie0.setVariable("onknees", Rand.Next(3) != 0);
 if (zombie0.getEatBodyTarget() instanceof IsoDeadBody) {
 IsoDeadBody deadBody = (IsoDeadBody)zombie0.eatBodyTarget;
 if (!zombie0.isEatingOther(deadBody) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 hashMap.put(0, deadBody);
 deadBody.getEatingZombies().add(zombie0);
 }

 if (GameClient.bClient && zombie0.isLocal()) {
 GameClient.sendEatBody(zombie0, zombie0.getEatBodyTarget());
 }
 } else if (zombie0.getEatBodyTarget() instanceof IsoPlayer && GameClient.bClient && zombie0.isLocal()) {
 GameClient.sendEatBody(zombie0, zombie0.getEatBodyTarget());
 }
 }

 void execute(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 IsoMovingObject movingObject = zombie0.getEatBodyTarget();
 if (zombie0.getStateEventDelayTimer() <= 0.0F) {
 zombie0.setEatBodyTarget(nullptr, false);
 } else if (!GameServer.bServer && !Core.SoundDisabled && Rand.Next(Rand.AdjustForFramerate(15) == 0) {
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Eating);
 }

 zombie0.TimeSinceSeenFlesh = 0.0F;
 if (movingObject != nullptr) {
 zombie0.faceThisObject(movingObject);
 }

 if (Rand.Next(Rand.AdjustForFramerate(450) == 0) {
 zombie0.getCurrentSquare()
 .getChunk()
 .addBloodSplat(zombie0.x + Rand.Next(-0.5F, 0.5F), zombie0.y + Rand.Next(-0.5F, 0.5F), zombie0.z, Rand.Next(8);
 if (Rand.Next(6) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.B,
 zombie0.getCell(),
 zombie0.getX(),
 zombie0.getY(),
 zombie0.getZ() + 0.3F,
 Rand.Next(-0.2F, 0.2F) * 1.5F,
 Rand.Next(-0.2F, 0.2F) * 1.5F
 );
 } else {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 zombie0.getCell(),
 zombie0.getX(),
 zombie0.getY(),
 zombie0.getZ() + 0.3F,
 Rand.Next(-0.2F, 0.2F) * 1.5F,
 Rand.Next(-0.2F, 0.2F) * 1.5F
 );
 }

 if (Rand.Next(4) == 0) {
 zombie0.addBlood(nullptr, true, false, false);
 }
 }
 }

 void exit(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 std::unordered_map hashMap = character.getStateMachineParams(this);
 if (hashMap.get(0) instanceof IsoDeadBody) {
 ((IsoDeadBody)hashMap.get(0).getEatingZombies().remove(zombie0);
 }

 if (zombie0.parameterZombieState.isState(ParameterZombieState.State.Eating) {
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Idle);
 }

 if (GameClient.bClient && zombie0.isLocal()) {
 GameClient.sendEatBody(zombie0, nullptr);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
