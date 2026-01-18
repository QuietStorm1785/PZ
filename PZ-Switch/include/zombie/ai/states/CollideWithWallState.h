#pragma once
#include "fmod/fmod/FMODManager.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"
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

class CollideWithWallState : public State {
public:
 static const CollideWithWallState _instance = new CollideWithWallState();

 static CollideWithWallState instance() { return _instance; }

 void enter(IsoGameCharacter character) {
 character.setIgnoreMovement(true);
 if (character instanceof IsoPlayer) {
 ((IsoPlayer)character).setIsAiming(false);
 }

 if (character.isCollidedN()) {
 character.setDir(IsoDirections.N);
 }

 if (character.isCollidedS()) {
 character.setDir(IsoDirections.S);
 }

 if (character.isCollidedE()) {
 character.setDir(IsoDirections.E);
 }

 if (character.isCollidedW()) {
 character.setDir(IsoDirections.W);
 }

 character.setCollideType("wall");
 }

 void execute(IsoGameCharacter character) {
 character.setLastCollideTime(70.0F);
 }

 void exit(IsoGameCharacter character) {
 character.setCollideType(nullptr);
 character.setIgnoreMovement(false);
 }

 void animEvent(IsoGameCharacter character, AnimEvent animEvent) {
 if ("PlayCollideSound".equalsIgnoreCase(animEvent.m_EventName) {
 long long0 = character.playSound(animEvent.m_ParameterValue);
 ParameterCharacterMovementSpeed parameterCharacterMovementSpeed =
 ((IsoPlayer)character).getParameterCharacterMovementSpeed();
 character.getEmitter().setParameterValue(
 long0, parameterCharacterMovementSpeed.getParameterDescription(),
 ParameterCharacterMovementSpeed.MovementType.Sprint.label);
 character.getEmitter().setParameterValue(
 long0,
 FMODManager.instance.getParameterDescription("TripObstacleType"),
 7.0F);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
