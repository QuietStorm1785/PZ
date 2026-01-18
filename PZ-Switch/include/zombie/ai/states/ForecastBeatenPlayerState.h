#pragma once
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
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

class ForecastBeatenPlayerState : public State {
public:
 static const ForecastBeatenPlayerState _instance =
 new ForecastBeatenPlayerState();

 static ForecastBeatenPlayerState instance() { return _instance; }

 void enter(IsoGameCharacter character) {
 character.setIgnoreMovement(true);
 character.setReanimateTimer(30.0F);
 }

 void execute(IsoGameCharacter character) {
 if (character.getCurrentSquare() != nullptr) {
 character.setReanimateTimer(character.getReanimateTimer() -
 GameTime.getInstance().getMultiplier() /
 1.6F);
 if (character.getReanimateTimer() <= 0.0F) {
 character.setReanimateTimer(0.0F);
 character.setVariable("bKnockedDown", true);
 }
 }
 }

 void exit(IsoGameCharacter character) { character.setIgnoreMovement(false); }
}
} // namespace states
} // namespace ai
} // namespace zombie
