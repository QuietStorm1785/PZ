#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerGetUpState : public State {
public:
 static const PlayerGetUpState _instance = new PlayerGetUpState();

 static PlayerGetUpState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 owner.setIgnoreMovement(true);
 IsoPlayer player = (IsoPlayer)owner;
 player.setInitiateAttack(false);
 player.attackStarted = false;
 player.setAttackType(nullptr);
 player.setBlockMovement(true);
 player.setForceRun(false);
 player.setForceSprint(false);
 owner.setVariable("getUpQuick", owner.getVariableBoolean("pressedRunButton"));
 if (owner.getMoodles().getMoodleLevel(MoodleType.Panic) > 1) {
 owner.setVariable("getUpQuick", true);
 }

 if (owner.getVariableBoolean("pressedMovement")) {
 owner.setVariable("getUpWalk", true);
 }

 if (GameClient.bClient) {
 owner.setKnockedDown(false);
 }
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 owner.clearVariable("getUpWalk");
 if (owner.getVariableBoolean("sitonground")) {
 owner.setHideWeaponModel(false);
 }

 owner.setIgnoreMovement(false);
 owner.setFallOnFront(false);
 owner.setOnFloor(false);
 ((IsoPlayer)owner).setBlockMovement(false);
 owner.setSitOnGround(false);
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
