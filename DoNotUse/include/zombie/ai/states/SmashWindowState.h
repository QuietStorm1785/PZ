#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleWindow.h"

namespace zombie {
namespace ai {
namespace states {


class SmashWindowState : public State {
public:
    static const SmashWindowState _instance = std::make_shared<SmashWindowState>();

    static SmashWindowState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      var1.setVariable("bSmashWindow", true);
    HandWeapon var2 = (HandWeapon)Type.tryCastTo(var1.getPrimaryHandItem(), HandWeapon.class);
      if (var2 != nullptr && var2.isRanged()) {
         var1.playSound("AttackShove");
      } else if (var2 != nullptr && !StringUtils.isNullOrWhitespace(var2.getSwingSound())) {
         var1.playSound(var2.getSwingSound());
      }
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      if (!(var2.get(0) instanceof IsoWindow) && !(var2.get(0) instanceof VehicleWindow)) {
         var1.setVariable("bSmashWindow", false);
      } else {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
         if (!var3.pressedMovement(false) && !var3.pressedCancelAction()) {
            if (var2.get(0) instanceof IsoWindow) {
    IsoWindow var4 = (IsoWindow)var2.get(0);
               if (var4.getObjectIndex() == -1 || var4.isDestroyed() && !"true" == var1.getVariableString("OwnerSmashedIt"))) {
                  var1.setVariable("bSmashWindow", false);
                  return;
               }

               if (var4.north) {
                  if (var4.getSquare().getY() < var1.getY()) {
                     var1.setDir(IsoDirections.N);
                  } else {
                     var1.setDir(IsoDirections.S);
                  }
               } else if (var4.getSquare().getX() < var1.getX()) {
                  var1.setDir(IsoDirections.W);
               } else {
                  var1.setDir(IsoDirections.E);
               }
            } else if (var2.get(0) instanceof VehicleWindow) {
    VehicleWindow var5 = (VehicleWindow)var2.get(0);
               var1.faceThisObject((BaseVehicle)var2.get(1));
               if (var5.isDestroyed() && !"true" == var1.getVariableString("OwnerSmashedIt"))) {
                  var1.setVariable("bSmashWindow", false);
                  return;
               }
            }
         } else {
            var1.setVariable("bSmashWindow", false);
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
      var1.clearVariable("bSmashWindow");
      var1.clearVariable("OwnerSmashedIt");
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
      if (var3.get(0) instanceof IsoWindow) {
    IsoWindow var4 = (IsoWindow)var3.get(0);
         if (var2.m_EventName.equalsIgnoreCase("AttackCollisionCheck")) {
            var1.setVariable("OwnerSmashedIt", true);
            IsoPlayer.getInstance().ContextPanic = 0.0F;
            var4.WeaponHit(var1, nullptr);
            if (!(var1.getPrimaryHandItem() instanceof HandWeapon) && !(var1.getSecondaryHandItem() instanceof HandWeapon)) {
               var1.getBodyDamage().setScratchedWindow();
            }
         } else if (var2.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
            var1.setVariable("bSmashWindow", false);
            if (bool.TRUE == var3.get(3)) {
               var1.climbThroughWindow(var4);
            }
         }
      } else if (var3.get(0) instanceof VehicleWindow) {
    VehicleWindow var5 = (VehicleWindow)var3.get(0);
         if (var2.m_EventName.equalsIgnoreCase("AttackCollisionCheck")) {
            var1.setVariable("OwnerSmashedIt", true);
            IsoPlayer.getInstance().ContextPanic = 0.0F;
            var5.hit(var1);
            if (!(var1.getPrimaryHandItem() instanceof HandWeapon) && !(var1.getSecondaryHandItem() instanceof HandWeapon)) {
               var1.getBodyDamage().setScratchedWindow();
            }
         } else if (var2.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
            var1.setVariable("bSmashWindow", false);
         }
      }
   }

    bool isDoingActionThatCanBeCancelled() {
    return true;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
