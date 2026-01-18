#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieReanimateState : public State {
public:
 static const ZombieReanimateState _instance = new ZombieReanimateState();

 static ZombieReanimateState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 zombie0.clearVariable("ReanimateAnim");
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Idle);
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 zombie0.clearVariable("ReanimateAnim");
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 IsoZombie zombie0 = (IsoZombie)owner;
 if (event.m_EventName.equalsIgnoreCase("FallOnFront")) {
 owner.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("ReanimateAnimFinishing")) {
 zombie0.setReanimate(false);
 zombie0.setFallOnFront(true);
 }

 if (event.m_EventName.equalsIgnoreCase("FallOnFront")) {
 owner.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
