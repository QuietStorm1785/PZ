#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
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

class FitnessState : public State {
public:
 static const FitnessState _instance = new FitnessState();

 static FitnessState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {
 owner.setIgnoreMovement(true);
 owner.setVariable("FitnessFinished", false);
 owner.clearVariable("ExerciseStarted");
 owner.clearVariable("ExerciseEnded");
 }

 void execute(IsoGameCharacter owner) {}

 void exit(IsoGameCharacter owner) {
 if (GameClient.bClient && owner instanceof
 IsoPlayer && ((IsoPlayer)owner).isLocalPlayer()) {
 GameClient.sendEvent((IsoPlayer)owner, "EventUpdateFitness");
 }

 owner.setIgnoreMovement(false);
 owner.clearVariable("FitnessFinished");
 owner.clearVariable("ExerciseStarted");
 owner.clearVariable("ExerciseHand");
 owner.clearVariable("FitnessStruggle");
 owner.setVariable("ExerciseEnded", true);
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {}
}
} // namespace states
} // namespace ai
} // namespace zombie
