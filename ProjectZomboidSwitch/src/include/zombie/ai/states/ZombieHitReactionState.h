#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieHitReactionState : public State {
public:
    static const ZombieHitReactionState _instance = std::make_shared<ZombieHitReactionState>();
    static const int TURN_TO_PLAYER = 1;
    static const int HIT_REACTION_TIMER = 2;

    static ZombieHitReactionState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var2.collideWhileHit = true;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var3.put(1, bool.FALSE);
      var3.put(2, 0.0F);
      var1.clearVariable("onknees");
      if (var2.isSitAgainstWall()) {
         var1.setHitReaction(nullptr);
      }
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var1.setOnFloor(((IsoZombie)var1).isKnockedDown());
      var2.put(2, (float)var2.get(2) + GameTime.getInstance().getMultiplier());
      if (var2.get(1) == bool.TRUE) {
         if (!var1.isHitFromBehind()) {
            var1.setDir(IsoDirections.reverse(IsoDirections.fromAngle(var1.getHitDir())));
         } else {
            var1.setDir(IsoDirections.fromAngle(var1.getHitDir()));
         }
      } else if (var1.hasAnimationPlayer()) {
         var1.getAnimationPlayer().setTargetToAngle();
      }
   }

    void exit(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var2.collideWhileHit = true;
      if (var2.target != nullptr) {
         var2.AllowRepathDelay = 0.0F;
         var2.spotted(var2.target, true);
      }

      var2.setStaggerBack(false);
      var2.setHitReaction("");
      var2.setEatBodyTarget(nullptr, false);
      var2.setSitAgainstWall(false);
      var2.setShootable(true);
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
    IsoZombie var4 = (IsoZombie)var1;
      if (var2.m_EventName.equalsIgnoreCase("DoDeath") && bool.parseBoolean(var2.m_ParameterValue) && var1.isAlive()) {
         var1.Kill(var1.getAttackedBy());
         if (var4.upKillCount && var1.getAttackedBy() != nullptr) {
            var1.getAttackedBy().setZombieKills(var1.getAttackedBy().getZombieKills() + 1);
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("PlayDeathSound")) {
         var1.setDoDeathSound(false);
         var1.playDeadSound();
      }

      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
      }

      if (var2.m_EventName.equalsIgnoreCase("Collide") && ((IsoZombie)var1).speedType == 1) {
         ((IsoZombie)var1).collideWhileHit = false;
      }

      if (var2.m_EventName.equalsIgnoreCase("ZombieTurnToPlayer")) {
    bool var5 = bool.parseBoolean(var2.m_ParameterValue);
         var3.put(1, var5 ? bool.TRUE : bool.FALSE);
      }

      if (var2.m_EventName.equalsIgnoreCase("CancelKnockDown")) {
    bool var6 = bool.parseBoolean(var2.m_ParameterValue);
         if (var6) {
            ((IsoZombie)var1).setKnockedDown(false);
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("KnockDown")) {
         var1.setOnFloor(true);
         ((IsoZombie)var1).setKnockedDown(true);
      }

      if (var2.m_EventName.equalsIgnoreCase("SplatBlood")) {
         var4.addBlood(nullptr, true, false, false);
         var4.addBlood(nullptr, true, false, false);
         var4.addBlood(nullptr, true, false, false);
         var4.playBloodSplatterSound();

         for (int var7 = 0; var7 < 10; var7++) {
            var4.getCurrentSquare().getChunk().addBloodSplat(var4.x + Rand.Next(-0.5F, 0.5F), var4.y + Rand.Next(-0.5F, 0.5F), var4.z, Rand.Next(8));
            if (Rand.Next(5) == 0) {
               std::make_shared<IsoZombieGiblets>(
                  GibletType.B, var4.getCell(), var4.getX(), var4.getY(), var4.getZ() + 0.3F, Rand.Next(-0.2F, 0.2F) * 1.5F, Rand.Next(-0.2F, 0.2F) * 1.5F
               );
            } else {
               std::make_shared<IsoZombieGiblets>(
                  GibletType.A, var4.getCell(), var4.getX(), var4.getY(), var4.getZ() + 0.3F, Rand.Next(-0.2F, 0.2F) * 1.5F, Rand.Next(-0.2F, 0.2F) * 1.5F
               );
            }
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("SetState") && !var4.isDead()) {
         if (var4.getAttackedBy() != nullptr && var4.getAttackedBy().getVehicle() != nullptr && "Floor" == var4.getHitReaction())) {
            var4.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.RunOver);
            return;
         }

         var4.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Hit);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
