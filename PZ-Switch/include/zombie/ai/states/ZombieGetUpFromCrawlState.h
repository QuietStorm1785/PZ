#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
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

class ZombieGetUpFromCrawlState : public State {
public:
 static const ZombieGetUpFromCrawlState _instance =
 new ZombieGetUpFromCrawlState();

 static ZombieGetUpFromCrawlState instance() { return _instance; }

 void enter(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)character;
 hashMap.put(1, character.getStateMachine().getPrevious());
 if (zombie0.isCrawling()) {
 zombie0.toggleCrawling();
 zombie0.setOnFloor(true);
 }
 }

 void execute(IsoGameCharacter var1) {}

 void exit(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 IsoZombie zombie0 = (IsoZombie)character;
 zombie0.AllowRepathDelay = 0.0F;
 if (hashMap.get(1) == PathFindState.instance()) {
 if (character.getPathFindBehavior2().getTargetChar() == nullptr) {
 character.setVariable("bPathfind", true);
 character.setVariable("bMoving", false);
 } else if (zombie0.isTargetLocationKnown()) {
 character.pathToCharacter(
 character.getPathFindBehavior2().getTargetChar());
 } else if (zombie0.LastTargetSeenX != -1) {
 character.pathToLocation(zombie0.LastTargetSeenX,
 zombie0.LastTargetSeenY,
 zombie0.LastTargetSeenZ);
 }
 }
 }

 void animEvent(IsoGameCharacter var1, AnimEvent var2) {}
}
} // namespace states
} // namespace ai
} // namespace zombie
