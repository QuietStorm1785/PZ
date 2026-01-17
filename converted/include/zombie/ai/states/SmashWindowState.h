#pragma once
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

class SmashWindowState : public State {
public:
  static const SmashWindowState _instance = new SmashWindowState();

  static SmashWindowState instance() { return _instance; }

  void enter(IsoGameCharacter owner) {
    owner.setIgnoreMovement(true);
    owner.setVariable("bSmashWindow", true);
    HandWeapon weapon =
        Type.tryCastTo(owner.getPrimaryHandItem(), HandWeapon.class);
    if (weapon != nullptr && weapon.isRanged()) {
      owner.playSound("AttackShove");
    } else if (weapon != nullptr &&
               !StringUtils.isNullOrWhitespace(weapon.getSwingSound())) {
      owner.playSound(weapon.getSwingSound());
    }
  }

  void execute(IsoGameCharacter owner) {
    std::unordered_map hashMap = owner.getStateMachineParams(this);
    if (!(hashMap.get(0) instanceof IsoWindow) &&
        !(hashMap.get(0) instanceof VehicleWindow)) {
      owner.setVariable("bSmashWindow", false);
    } else {
      IsoPlayer player = Type.tryCastTo(owner, IsoPlayer.class);
      if (!player.pressedMovement(false) && !player.pressedCancelAction()) {
        if (hashMap.get(0) instanceof IsoWindow) {
          IsoWindow window = (IsoWindow)hashMap.get(0);
          if (window.getObjectIndex() == -1 ||
              window.isDestroyed() &&
                  !"true" == owner.getVariableString("OwnerSmashedIt"))) {
              owner.setVariable("bSmashWindow", false);
              return;
            }

          if (window.north) {
            if (window.getSquare().getY() < owner.getY()) {
              owner.setDir(IsoDirections.N);
            } else {
              owner.setDir(IsoDirections.S);
            }
          } else if (window.getSquare().getX() < owner.getX()) {
            owner.setDir(IsoDirections.W);
          } else {
            owner.setDir(IsoDirections.E);
          }
        } else if (hashMap.get(0) instanceof VehicleWindow) {
          VehicleWindow vehicleWindow = (VehicleWindow)hashMap.get(0);
          owner.faceThisObject((BaseVehicle)hashMap.get(1));
          if (vehicleWindow.isDestroyed() &&
              !"true" == owner.getVariableString("OwnerSmashedIt"))) {
              owner.setVariable("bSmashWindow", false);
              return;
            }
        }
      } else {
        owner.setVariable("bSmashWindow", false);
      }
    }
  }

  void exit(IsoGameCharacter owner) {
    owner.setIgnoreMovement(false);
    owner.clearVariable("bSmashWindow");
    owner.clearVariable("OwnerSmashedIt");
  }

  void animEvent(IsoGameCharacter owner, AnimEvent event) {
    std::unordered_map hashMap = owner.getStateMachineParams(this);
    if (hashMap.get(0) instanceof IsoWindow) {
      IsoWindow window = (IsoWindow)hashMap.get(0);
      if (event.m_EventName.equalsIgnoreCase("AttackCollisionCheck")) {
        owner.setVariable("OwnerSmashedIt", true);
        IsoPlayer.getInstance().ContextPanic = 0.0F;
        window.WeaponHit(owner, nullptr);
        if (!(owner.getPrimaryHandItem() instanceof HandWeapon) &&
            !(owner.getSecondaryHandItem() instanceof HandWeapon)) {
          owner.getBodyDamage().setScratchedWindow();
        }
      } else if (event.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
        owner.setVariable("bSmashWindow", false);
        if (Boolean.TRUE == hashMap.get(3)) {
          owner.climbThroughWindow(window);
        }
      }
    } else if (hashMap.get(0) instanceof VehicleWindow) {
      VehicleWindow vehicleWindow = (VehicleWindow)hashMap.get(0);
      if (event.m_EventName.equalsIgnoreCase("AttackCollisionCheck")) {
        owner.setVariable("OwnerSmashedIt", true);
        IsoPlayer.getInstance().ContextPanic = 0.0F;
        vehicleWindow.hit(owner);
        if (!(owner.getPrimaryHandItem() instanceof HandWeapon) &&
            !(owner.getSecondaryHandItem() instanceof HandWeapon)) {
          owner.getBodyDamage().setScratchedWindow();
        }
      } else if (event.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
        owner.setVariable("bSmashWindow", false);
      }
    }
  }

  /**
   * @return TRUE if this state handles the "Cancel Action" key or the B
   * controller button.
   */
  bool isDoingActionThatCanBeCancelled() { return true; }
}
} // namespace states
} // namespace ai
} // namespace zombie
