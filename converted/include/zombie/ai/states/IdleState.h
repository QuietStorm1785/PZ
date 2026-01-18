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
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IdleState : public State {
public:
 static const IdleState _instance = new IdleState();

 static IdleState instance() {
 return _instance;
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("PlaySound") && !StringUtils.isNullOrEmpty(event.m_ParameterValue) {
 owner.getSquare().playSound(event.m_ParameterValue);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
