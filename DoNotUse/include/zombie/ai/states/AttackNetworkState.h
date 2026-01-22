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
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {


class AttackNetworkState : public State {
public:
    static const AttackNetworkState s_instance = std::make_shared<AttackNetworkState>();
    std::string attackOutcome;

    static AttackNetworkState instance() {
    return s_instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var3.clear();
      var3.put(0, bool.FALSE);
      this.attackOutcome = var1.getVariableString("AttackOutcome");
      var1.setVariable("AttackOutcome", "start");
      var1.clearVariable("AttackDidDamage");
      var1.clearVariable("ZombieBiteDone");
      var2.setTargetSeenTime(1.0F);
      if (!var2.bCrawling) {
         var2.setVariable("AttackType", "bite");
      }
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
    IsoGameCharacter var4 = (IsoGameCharacter)var2.target;
      if (var4 == nullptr || !"Chainsaw" == var4.getVariableString("ZombieHitReaction"))) {
    std::string var5 = var1.getVariableString("AttackOutcome");
         if ("success" == var5)
            && !var1.getVariableBoolean("bAttack")
            && (var4 == nullptr || !var4.isGodMod())
            && !var1.getVariableBoolean("AttackDidDamage")
            && var1.getVariableString("ZombieBiteDone") != "true") {
            var1.setVariable("AttackOutcome", "interrupted");
         }

         if (var4 == nullptr || var4.isDead()) {
            var2.setTargetSeenTime(10.0F);
         }

         if (var4 != nullptr && var3.get(0) == bool.FALSE && !"started" == var5) && !StringUtils.isNullOrEmpty(var1.getVariableString("PlayerHitReaction"))
            )
          {
            var3.put(0, bool.TRUE);
         }

         var2.setShootable(true);
         if (var2.target != nullptr && !var2.bCrawling) {
            if (!"fail" == var5) && !"interrupted" == var5)) {
               var2.faceThisObject(var2.target);
            }

            var2.setOnFloor(false);
         }

         if (var2.target != nullptr) {
            var2.target.setTimeSinceZombieAttack(0);
            var2.target.setLastTargettedBy(var2);
         }

         if (!var2.bCrawling) {
            var2.setVariable("AttackType", "bite");
         }
      }
   }

    void exit(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var1.clearVariable("AttackOutcome");
      var1.clearVariable("AttackType");
      var1.clearVariable("PlayerHitReaction");
      var1.setStateMachineLocked(false);
      if (var2.target != nullptr && var2.target.isOnFloor()) {
         var2.setEatBodyTarget(var2.target, true);
         var2.setTarget(nullptr);
      }

      var2.AllowRepathDelay = 0.0F;
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    IsoZombie var3 = (IsoZombie)var1;
      if (GameClient.bClient && var3.isRemoteZombie()) {
         if (var2.m_EventName.equalsIgnoreCase("SetAttackOutcome")) {
            var3.setVariable("AttackOutcome", "fail" == this.attackOutcome) ? "fail" : "success");
         }

         if (var2.m_EventName.equalsIgnoreCase("AttackCollisionCheck") && var3.dynamic_cast<IsoPlayer*>(target) != nullptr var4) {
            if (var3.scratch) {
               var3.getEmitter().playSoundImpl("ZombieScratch", var3);
            } else if (var3.laceration) {
               var3.getEmitter().playSoundImpl("ZombieScratch", var3);
            } else {
               var3.getEmitter().playSoundImpl("ZombieBite", var3);
               var4.splatBloodFloorBig();
               var4.splatBloodFloorBig();
               var4.splatBloodFloorBig();
            }
         }

         if (var2.m_EventName.equalsIgnoreCase("EatBody")) {
            var1.setVariable("EatingStarted", true);
            ((IsoZombie)var1).setEatBodyTarget(((IsoZombie)var1).target, true);
            ((IsoZombie)var1).setTarget(nullptr);
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("SetState")) {
         var3.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Attack);
      }
   }

    bool isAttacking(IsoGameCharacter var1) {
    return true;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
