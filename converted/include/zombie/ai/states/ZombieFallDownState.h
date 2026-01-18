#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieFallDownState : public State {
public:
 static const ZombieFallDownState _instance = new ZombieFallDownState();

 static ZombieFallDownState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.blockTurning = true;
 owner.setHitReaction("");
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 owner.blockTurning = false;
 owner.setOnFloor(true);
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("FallOnFront")) {
 owner.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("PlayDeathSound")) {
 owner.setDoDeathSound(false);
 owner.playDeadSound();
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
