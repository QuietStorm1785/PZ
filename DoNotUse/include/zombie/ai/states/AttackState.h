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
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {


class AttackState : public State {
public:
    static const AttackState s_instance = std::make_shared<AttackState>();
    static const std::string frontStr = "FRONT";
    static const std::string backStr = "BEHIND";
    static const std::string rightStr = "LEFT";
    static const std::string leftStr = "RIGHT";

    static AttackState instance() {
    return s_instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var3.clear();
      var3.put(0, bool.FALSE);
      var1.setVariable("AttackOutcome", "start");
      var1.clearVariable("AttackDidDamage");
      var1.clearVariable("ZombieBiteDone");
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoZombie var3 = (IsoZombie)var1;
    IsoGameCharacter var4 = (IsoGameCharacter)var3.target;
      if (var4 == nullptr || !"Chainsaw" == var4.getVariableString("ZombieHitReaction"))) {
    std::string var5 = var1.getVariableString("AttackOutcome");
         if ("success" == var5) && var1.getVariableBoolean("bAttack") && var1.isVariable("targethitreaction", "EndDeath")) {
            var5 = "enddeath";
            var1.setVariable("AttackOutcome", var5);
         }

         if ("success" == var5)
            && !var1.getVariableBoolean("bAttack")
            && !var1.getVariableBoolean("AttackDidDamage")
            && var1.getVariableString("ZombieBiteDone") == nullptr) {
            var1.setVariable("AttackOutcome", "interrupted");
         }

         if (var4 == nullptr || var4.isDead()) {
            var3.setTargetSeenTime(10.0F);
         }

         if (var4 != nullptr && var2.get(0) == bool.FALSE && !"started" == var5) && !StringUtils.isNullOrEmpty(var1.getVariableString("PlayerHitReaction"))
            )
          {
            var2.put(0, bool.TRUE);
            var4.testDefense(var3);
         }

         var3.setShootable(true);
         if (var3.target != nullptr && !var3.bCrawling) {
            if (!"fail" == var5) && !"interrupted" == var5)) {
               var3.faceThisObject(var3.target);
            }

            var3.setOnFloor(false);
         }

    bool var6 = var3.speedType == 1;
         if (var3.target != nullptr && var6 && ("start" == var5) || "success" == var5))) {
    IsoGameCharacter var7 = (IsoGameCharacter)var3.target;
    float var8 = var7.getSlowFactor();
            if (var7.getSlowFactor() <= 0.0F) {
               var7.setSlowTimer(30.0F);
            }

            var7.setSlowTimer(var7.getSlowTimer() + GameTime.instance.getMultiplier());
            if (var7.getSlowTimer() > 60.0F) {
               var7.setSlowTimer(60.0F);
            }

            var7.setSlowFactor(var7.getSlowFactor() + 0.03F);
            if (var7.getSlowFactor() >= 0.5F) {
               var7.setSlowFactor(0.5F);
            }

            if (GameServer.bServer && var8 != var7.getSlowFactor()) {
               GameServer.sendSlowFactor(var7);
            }
         }

         if (var3.target != nullptr) {
            var3.target.setTimeSinceZombieAttack(0);
            var3.target.setLastTargettedBy(var3);
         }

         if (!var3.bCrawling) {
            var3.setVariable("AttackType", "bite");
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
      if (var2.m_EventName.equalsIgnoreCase("SetAttackOutcome")) {
         if (var3.getVariableBoolean("bAttack")) {
            var3.setVariable("AttackOutcome", "success");
         } else {
            var3.setVariable("AttackOutcome", "fail");
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("AttackCollisionCheck") && !var3.isNoTeeth()) {
    IsoGameCharacter var4 = (IsoGameCharacter)var3.target;
         if (var4 == nullptr) {
            return;
         }

         var4.setHitFromBehind(var3.isBehind(var4));
    std::string var5 = var4.testDotSide(var3);
    bool var6 = var5 == "FRONT");
         if (var6 && !var4.isAimAtFloor() && !StringUtils.isNullOrEmpty(var4.getVariableString("AttackType"))) {
            return;
         }

         if ("KnifeDeath" == var4.getVariableString("ZombieHitReaction"))) {
    int var7 = var4.getPerkLevel(Perks.SmallBlade) + 1;
    int var8 = Math.max(0, 9 - var7 * 2);
            if (Rand.NextBool(var8)) {
               return;
            }
         }

         this.triggerPlayerReaction(var1.getVariableString("PlayerHitReaction"), var1);
    Vector2 var9 = var3.getHitDir();
         var9.x = var3.getX();
         var9.y = var3.getY();
         var9.x = var9.x - var4.getX();
         var9.y = var9.y - var4.getY();
         var9.normalize();
         if (GameClient.bClient && !var3.isRemoteZombie()) {
            GameClient.sendHitCharacter(var3, var4, nullptr, 0.0F, false, 1.0F, false, false, false);
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("EatBody")) {
         var1.setVariable("EatingStarted", true);
         ((IsoZombie)var1).setEatBodyTarget(((IsoZombie)var1).target, true);
         ((IsoZombie)var1).setTarget(nullptr);
      }

      if (var2.m_EventName.equalsIgnoreCase("SetState")) {
         var3.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Attack);
      }
   }

    bool isAttacking(IsoGameCharacter var1) {
    return true;
   }

    void triggerPlayerReaction(const std::string& var1, IsoGameCharacter var2) {
    IsoZombie var3 = (IsoZombie)var2;
    IsoGameCharacter var4 = (IsoGameCharacter)var3.target;
      if (var4 != nullptr) {
         if (!(var3.DistTo(var4) > 1.0F) || var3.bCrawling) {
            if (!var3.isFakeDead() && !var3.bCrawling || !(var3.DistTo(var4) > 1.3F)) {
               if ((!var4.isDead() || var4.getHitReaction() == "EndDeath")) && !var4.isOnFloor()) {
                  if (!var4.isDead()) {
                     var4.setHitFromBehind(var3.isBehind(var4));
    std::string var5 = var4.testDotSide(var3);
    bool var6 = var5 == "FRONT");
    bool var7 = var5 == "BEHIND");
                     if (var5 == "RIGHT")) {
                        var1 = var1 + "LEFT";
                     }

                     if (var5 == "LEFT")) {
                        var1 = var1 + "RIGHT";
                     }

                     if (!((IsoPlayer)var4).bDoShove || !var6 || var4.isAimAtFloor()) {
                        if (!((IsoPlayer)var4).bDoShove || var6 || var7 || Rand.Next(100) <= 75) {
                           if (!(Math.abs(var3.z - var4.z) >= 0.2F)) {
                              TestResults var8 = LosUtil.lineClear(
                                 var3.getCell(),
                                 (int)var3.getX(),
                                 (int)var3.getY(),
                                 (int)var3.getZ(),
                                 (int)var4.getX(),
                                 (int)var4.getY(),
                                 (int)var4.getZ(),
                                 false
                              );
                              if (var8 != TestResults.Blocked && var8 != TestResults.ClearThroughClosedDoor) {
                                 if (!var4.getSquare().isSomethingTo(var3.getCurrentSquare())) {
                                    var4.setAttackedBy(var3);
    bool var9 = false;
                                    if (!GameClient.bClient && !GameServer.bServer || GameClient.bClient && !var3.isRemoteZombie()) {
                                       var9 = var4.getBodyDamage().AddRandomDamageFromZombie(var3, var1);
                                    }

                                    var2.setVariable("AttackDidDamage", var9);
                                    var4.getBodyDamage().Update();
                                    if (var4.isDead()) {
                                       var4.setHealth(0.0F);
                                       var3.setEatBodyTarget(var4, true);
                                       var3.setTarget(nullptr);
                                    } else if (var4.isAsleep()) {
                                       if (GameServer.bServer) {
                                          var4.sendObjectChange("wakeUp");
                                       } else {
                                          var4.forceAwake();
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               } else {
                  var3.setEatBodyTarget(var4, true);
               }
            }
         }
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
