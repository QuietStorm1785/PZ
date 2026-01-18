#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/Vector2.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LungeNetworkState : public State {
public:
 static LungeNetworkState _instance = std::make_unique<LungeNetworkState>();
 Vector2 temp = new Vector2();
 const Vector3f worldPos = new Vector3f();
 static const int PARAM_TICK_COUNT = 0;

 static LungeNetworkState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 WalkTowardNetworkState.instance().enter(character);
 IsoZombie zombie0 = (IsoZombie)character;
 zombie0.LungeTimer = 180.0F;
 hashMap.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
 }

 void execute(IsoGameCharacter character) {
 WalkTowardNetworkState.instance().execute(character);
 IsoZombie zombie0 = (IsoZombie)character;
 character.setOnFloor(false);
 character.setShootable(true);
 if (zombie0.bLunger) {
 zombie0.walkVariantUse = "ZombieWalk3";
 }

 zombie0.LungeTimer = zombie0.LungeTimer - GameTime.getInstance().getMultiplier() / 1.6F;
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

 std::unordered_map hashMap = character.getStateMachineParams(this);
 long long0 = (Long)hashMap.get(PARAM_TICK_COUNT);
 if (IngameState.instance.numberTicks - long0 == 2L) {
 ((IsoZombie)character).parameterZombieState.setState(ParameterZombieState.State.LockTarget);
 }
 }

 void exit(IsoGameCharacter character) {
 WalkTowardNetworkState.instance().exit(character);
 }

 bool isMoving(IsoGameCharacter var1) {
 return true;
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
