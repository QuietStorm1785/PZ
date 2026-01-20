#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerSitOnGroundState : public State {
public:
    static const PlayerSitOnGroundState _instance = std::make_shared<PlayerSitOnGroundState>();
    static const int RAND_EXT = 2500;
    static const int PARAM_FIRE = 0;
    static const int PARAM_SITGROUNDANIM = 1;
    static const int PARAM_CHECK_FIRE = 2;
    static const int PARAM_CHANGE_ANIM = 3;

    static PlayerSitOnGroundState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var2.put(PARAM_FIRE, this.checkFire(var1));
      var2.put(PARAM_CHECK_FIRE, System.currentTimeMillis());
      var2.put(PARAM_CHANGE_ANIM, 0L);
      var1.setSitOnGround(true);
      if ((var1.getPrimaryHandItem() == nullptr || !(var1.getPrimaryHandItem() instanceof HandWeapon))
         && (var1.getSecondaryHandItem() == nullptr || !(var1.getSecondaryHandItem() instanceof HandWeapon))) {
         var1.setHideWeaponModel(true);
      }

      if (var1.getStateMachine().getPrevious() == IdleState.instance()) {
         var1.clearVariable("SitGroundStarted");
         var1.clearVariable("forceGetUp");
         var1.clearVariable("SitGroundAnim");
      }
   }

    bool checkFire(IsoGameCharacter var1) {
    IsoGridSquare var2 = var1.getCurrentSquare();

      for (int var3 = -4; var3 < 4; var3++) {
         for (int var4 = -4; var4 < 4; var4++) {
    IsoGridSquare var5 = var2.getCell().getGridSquare(var2.x + var3, var2.y + var4, var2.z);
            if (var5 != nullptr) {
               if (var5.haveFire()) {
    return true;
               }

               for (int var6 = 0; var6 < var5.getObjects().size(); var6++) {
    IsoFireplace var7 = (IsoFireplace)Type.tryCastTo((IsoObject)var5.getObjects().get(var6), IsoFireplace.class);
                  if (var7 != nullptr && var7.isLit()) {
    return true;
                  }
               }
            }
         }
      }

    return false;
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoPlayer var3 = (IsoPlayer)var1;
      if (var3.pressedMovement(false)) {
         var1.StopAllActionQueue();
         var1.setVariable("forceGetUp", true);
      }

    long var4 = System.currentTimeMillis();
      if (var4 > (int64_t)var2.get(PARAM_CHECK_FIRE) + 5000L) {
         var2.put(PARAM_FIRE, this.checkFire(var1));
         var2.put(PARAM_CHECK_FIRE, var4);
      }

      if (var1.hasTimedActions()) {
         var2.put(PARAM_FIRE, false);
         var1.setVariable("SitGroundAnim", "Idle");
      }

    bool var6 = (bool)var2.get(PARAM_FIRE);
      if (var6) {
    bool var7 = var4 > (int64_t)var2.get(PARAM_CHANGE_ANIM);
         if (var7) {
            if ("Idle" == var1.getVariableString("SitGroundAnim"))) {
               var1.setVariable("SitGroundAnim", "WarmHands");
            } else if ("WarmHands" == var1.getVariableString("SitGroundAnim"))) {
               var1.setVariable("SitGroundAnim", "Idle");
            }

            var2.put(PARAM_CHANGE_ANIM, var4 + Rand.Next(30000, 90000));
         }
      } else if (var1.getVariableBoolean("SitGroundStarted")) {
         var1.clearVariable("FireNear");
         var1.setVariable("SitGroundAnim", "Idle");
      }

      if ("WarmHands" == var1.getVariableString("SitGroundAnim")) && Rand.Next(Rand.AdjustForFramerate(2500)) == 0) {
         var2.put(PARAM_SITGROUNDANIM, var1.getVariableString("SitGroundAnim"));
         var1.setVariable("SitGroundAnim", "rubhands");
      }

      var3.setInitiateAttack(false);
      var3.attackStarted = false;
      var3.setAttackType(nullptr);
   }

    void exit(IsoGameCharacter var1) {
      var1.setHideWeaponModel(false);
      if (StringUtils.isNullOrEmpty(var1.getVariableString("HitReaction"))) {
         var1.clearVariable("SitGroundStarted");
         var1.clearVariable("forceGetUp");
         var1.clearVariable("SitGroundAnim");
         var1.setIgnoreMovement(false);
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("SitGroundStarted")) {
         var1.setVariable("SitGroundStarted", true);
    bool var3 = (bool)var1.getStateMachineParams(this).get(PARAM_FIRE);
         if (var3) {
            var1.setVariable("SitGroundAnim", "WarmHands");
         } else {
            var1.setVariable("SitGroundAnim", "Idle");
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("ResetSitOnGroundAnim")) {
         var1.setVariable("SitGroundAnim", (std::string)var1.getStateMachineParams(this).get(PARAM_SITGROUNDANIM));
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
