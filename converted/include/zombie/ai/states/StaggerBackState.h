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


class StaggerBackState : public State {
public:
 static const StaggerBackState _instance = new StaggerBackState();

 static StaggerBackState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.setStateEventDelayTimer(this->getMaxStaggerTime(owner);
 }

 void execute(IsoGameCharacter owner) {
 if (owner.hasAnimationPlayer()) {
 owner.getAnimationPlayer().setTargetToAngle();
 }

 owner.getVectorFromDirection(owner.getForwardDirection());
 }

 void exit(IsoGameCharacter owner) {
 if (owner.isZombie()) {
 ((IsoZombie)owner).setStaggerBack(false);
 }

 owner.setShootable(true);
 }

 float getMaxStaggerTime(IsoGameCharacter character) {
 float float0 = 35.0F * character.getHitForce() * character.getStaggerTimeMod();
 if (float0 < 20.0F) {
 return 20.0F;
 } else {
 return float0 > 30.0F ? 30.0F : float0;
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("FallOnFront")) {
 owner.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("SetState")) {
 IsoZombie zombie0 = (IsoZombie)owner;
 zombie0.parameterZombieState.setState(ParameterZombieState.State.Pushed);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
