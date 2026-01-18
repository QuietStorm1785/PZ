#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
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

class ZombieFallingState : public State {
public:
 static const ZombieFallingState _instance = new ZombieFallingState();

 static ZombieFallingState instance() { return _instance; }

 void enter(IsoGameCharacter character) {
 character.setVariable("bHardFall", false);
 character.clearVariable("bLandAnimFinished");
 }

 void execute(IsoGameCharacter var1) {}

 void exit(IsoGameCharacter character) {
 character.clearVariable("bHardFall");
 character.clearVariable("bLandAnimFinished");
 }

 void animEvent(IsoGameCharacter character, AnimEvent animEvent) {
 if (animEvent.m_EventName.equalsIgnoreCase("FallOnFront")) {
 character.setFallOnFront(
 Boolean.parseBoolean(animEvent.m_ParameterValue);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
