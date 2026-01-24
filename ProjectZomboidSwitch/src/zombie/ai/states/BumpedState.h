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
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace ai {
namespace states {


class BumpedState : public State {
public:
   static BumpedState& instance();
   void enter(IsoGameCharacter* character) override;
   void execute(IsoGameCharacter* character) override;
   void exit(IsoGameCharacter* character) override;
   void animEvent(IsoGameCharacter* character, AnimEvent* event) override;
private:
   void setCharacterBlockMovement(IsoGameCharacter* character, bool block);
   BumpedState() = default;
         if (var5 == nullptr) {
            var5 = "zombie";
         }

         var1.clearVariable("TripObstacleType");
    uint8_t var8 = -1;
         switch (var5.hashCode()) {
            case 3568542:
               if (var5 == "tree")) {
                  var8 = 0;
               }
            default:
               byte var6 = switch (var8) {
                  case 0 -> 5;
                  default -> 6;
               };
               var1.getEmitter().setParameterValue(var2, FMODManager.instance.getParameterDescription("TripObstacleType"), var6);
         }
      }
   }

    void execute(IsoGameCharacter var1) {
    bool var2 = var1.isBumpFall() || var1.isBumpStaggered();
      this.setCharacterBlockMovement(var1, var2);
   }

    void setCharacterBlockMovement(IsoGameCharacter var1, bool var2) {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (var3 != nullptr) {
         var3.setBlockMovement(var2);
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.clearVariable("BumpFallType");
      var1.clearVariable("BumpFallAnimFinished");
      var1.clearVariable("BumpAnimFinished");
      var1.setBumpType("");
      var1.setBumpedChr(nullptr);
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (var2 != nullptr) {
         var2.setInitiateAttack(false);
         var2.attackStarted = false;
         var2.setAttackType(nullptr);
      }

      if (var2 != nullptr && var1.isBumpFall()) {
         var1.fallenOnKnees();
      }

      var1.setOnFloor(false);
      var1.setBumpFall(false);
      this.setCharacterBlockMovement(var1, false);
      if (dynamic_cast<IsoZombie*>(var1) != nullptr && ((IsoZombie)var1).target != nullptr) {
         var1.pathToLocation((int)((IsoZombie)var1).target.getX(), (int)((IsoZombie)var1).target.getY(), (int)((IsoZombie)var1).target.getZ());
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
         var1.setOnFloor(var1.isFallOnFront());
      }

      if (var2.m_EventName.equalsIgnoreCase("FallOnBack")) {
         var1.setOnFloor(bool.parseBoolean(var2.m_ParameterValue));
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
