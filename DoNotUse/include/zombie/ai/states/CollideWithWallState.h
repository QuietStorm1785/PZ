#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed/MovementType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"

namespace zombie {
namespace ai {
namespace states {


class CollideWithWallState : public State {
public:
    static const CollideWithWallState _instance = std::make_shared<CollideWithWallState>();

    static CollideWithWallState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
         ((IsoPlayer)var1).setIsAiming(false);
      }

      if (var1.isCollidedN()) {
         var1.setDir(IsoDirections.N);
      }

      if (var1.isCollidedS()) {
         var1.setDir(IsoDirections.S);
      }

      if (var1.isCollidedE()) {
         var1.setDir(IsoDirections.E);
      }

      if (var1.isCollidedW()) {
         var1.setDir(IsoDirections.W);
      }

      var1.setCollideType("wall");
   }

    void execute(IsoGameCharacter var1) {
      var1.setLastCollideTime(70.0F);
   }

    void exit(IsoGameCharacter var1) {
      var1.setCollideType(nullptr);
      var1.setIgnoreMovement(false);
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if ("PlayCollideSound".equalsIgnoreCase(var2.m_EventName)) {
    long var3 = var1.playSound(var2.m_ParameterValue);
    ParameterCharacterMovementSpeed var5 = ((IsoPlayer)var1).getParameterCharacterMovementSpeed();
         var1.getEmitter().setParameterValue(var3, var5.getParameterDescription(), MovementType.Sprint.label);
         var1.getEmitter().setParameterValue(var3, FMODManager.instance.getParameterDescription("TripObstacleType"), 7.0F);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
