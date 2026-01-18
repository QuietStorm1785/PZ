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

class PlayerExtState : public State {
public:
 static const PlayerExtState _instance = new PlayerExtState();

 static PlayerExtState instance() { return _instance; }

 void enter(IsoGameCharacter owner) { owner.setVariable("ExtPlaying", true); }

 void execute(IsoGameCharacter owner) {}

 void exit(IsoGameCharacter owner) { owner.clearVariable("ExtPlaying"); }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if ("ExtFinishing".equalsIgnoreCase(event.m_EventName) {
 owner.setVariable("ExtPlaying", false);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
