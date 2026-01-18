#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerFallingState : public State {
public:
 static const PlayerFallingState _instance = new PlayerFallingState();

 static PlayerFallingState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.setVariable("bHardFall", false);
 owner.clearVariable("bLandAnimFinished");
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 owner.clearVariable("bHardFall");
 owner.clearVariable("bLandAnimFinished");
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
