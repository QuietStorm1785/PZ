#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace ai {
namespace states {


class WalkTowardState : public State {
public:
    static const WalkTowardState _instance = std::make_shared<WalkTowardState>();
    static const int PARAM_IGNORE_OFFSET = 0;
    static const int PARAM_IGNORE_TIME = 1;
    static const int PARAM_TICK_COUNT = 2;
    const Vector2 temp = std::make_shared<Vector2>();
    const Vector3f worldPos = std::make_shared<Vector3f>();

    static WalkTowardState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      if (var2.get(PARAM_IGNORE_OFFSET) == nullptr) {
         var2.put(PARAM_IGNORE_OFFSET, bool.FALSE);
         var2.put(PARAM_IGNORE_TIME, 0L);
      }

      if (var2.get(PARAM_IGNORE_OFFSET) == bool.TRUE && System.currentTimeMillis() - (int64_t)var2.get(PARAM_IGNORE_TIME) > 3000L) {
         var2.put(PARAM_IGNORE_OFFSET, bool.FALSE);
         var2.put(PARAM_IGNORE_TIME, 0L);
      }

      var2.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
      if (((IsoZombie)var1).isUseless()) {
         var1.changeState(ZombieIdleState.instance());
      }

      var1.getPathFindBehavior2().walkingOnTheSpot.reset(var1.x, var1.y);
      ((IsoZombie)var1).networkAI.extraUpdate();
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoZombie var3 = (IsoZombie)var1;
      if (!var3.bCrawling) {
         var1.setOnFloor(false);
      }

    IsoGameCharacter var4 = (IsoGameCharacter)Type.tryCastTo(var3.target, IsoGameCharacter.class);
      if (var3.target != nullptr) {
         if (var3.isTargetLocationKnown()) {
            if (var4 != nullptr) {
               var3.getPathFindBehavior2().pathToCharacter(var4);
               if (var4.getVehicle() != nullptr && var3.DistToSquared(var3.target) < 16.0F) {
    Vector3f var5 = var4.getVehicle().chooseBestAttackPosition(var4, var3, this.worldPos);
                  if (var5 == nullptr) {
                     var3.setVariable("bMoving", false);
                     return;
                  }

                  if (Math.abs(var1.x - var3.getPathFindBehavior2().getTargetX()) > 0.1F || Math.abs(var1.y - var3.getPathFindBehavior2().getTargetY()) > 0.1F) {
                     var3.setVariable("bPathfind", true);
                     var3.setVariable("bMoving", false);
                     return;
                  }
               }
            }
         } else if (var3.LastTargetSeenX != -1
            && !var1.getPathFindBehavior2().isTargetLocation(var3.LastTargetSeenX + 0.5F, var3.LastTargetSeenY + 0.5F, var3.LastTargetSeenZ)) {
            var1.pathToLocation(var3.LastTargetSeenX, var3.LastTargetSeenY, var3.LastTargetSeenZ);
         }
      }

      if (var1.getPathTargetX() == (int)var1.getX() && var1.getPathTargetY() == (int)var1.getY()) {
         if (var3.target == nullptr) {
            var3.setVariable("bPathfind", false);
            var3.setVariable("bMoving", false);
            return;
         }

         if ((int)var3.target.getZ() != (int)var1.getZ()) {
            var3.setVariable("bPathfind", true);
            var3.setVariable("bMoving", false);
            return;
         }
      }

    bool var11 = var1.isCollidedWithVehicle();
      if (var4 != nullptr && var4.getVehicle() != nullptr && var4.getVehicle().isCharacterAdjacentTo(var1)) {
         var11 = false;
      }

    bool var6 = var1.isCollidedThisFrame();
      if (var6 && var2.get(PARAM_IGNORE_OFFSET) == bool.FALSE) {
         var2.put(PARAM_IGNORE_OFFSET, bool.TRUE);
         var2.put(PARAM_IGNORE_TIME, System.currentTimeMillis());
    float var7 = var3.getPathFindBehavior2().getTargetX();
    float var8 = var3.getPathFindBehavior2().getTargetY();
    float var9 = var3.z;
         var6 = !this.isPathClear(var1, var7, var8, var9);
      }

      if (!var6 && !var11) {
         this.temp.x = var3.getPathFindBehavior2().getTargetX();
         this.temp.y = var3.getPathFindBehavior2().getTargetY();
         this.temp.x = this.temp.x - var3.getX();
         this.temp.y = this.temp.y - var3.getY();
    float var12 = this.temp.getLength();
         if (var12 < 0.25F) {
            var1.x = var3.getPathFindBehavior2().getTargetX();
            var1.y = var3.getPathFindBehavior2().getTargetY();
            var1.nx = var1.x;
            var1.ny = var1.y;
            var12 = 0.0F;
         }

         if (var12 < 0.025F) {
            var3.setVariable("bPathfind", false);
            var3.setVariable("bMoving", false);
         } else {
            if (!GameServer.bServer && !var3.bCrawling && var2.get(PARAM_IGNORE_OFFSET) == bool.FALSE) {
    float var13 = Math.min(var12 / 2.0F, 4.0F);
    float var15 = (var1.getID() + var3.ZombieID) % 20 / 10.0F - 1.0F;
    float var10 = (var3.getID() + var3.ZombieID) % 20 / 10.0F - 1.0F;
               this.temp.x = this.temp.x + var3.getX();
               this.temp.y = this.temp.y + var3.getY();
               this.temp.x += var15 * var13;
               this.temp.y += var10 * var13;
               this.temp.x = this.temp.x - var3.getX();
               this.temp.y = this.temp.y - var3.getY();
            }

            var3.bRunning = false;
            this.temp.normalize();
            if (var3.bCrawling) {
               if (var3.getVariableString("TurnDirection").empty()) {
                  var3.setForwardDirection(this.temp);
               }
            } else {
               var3.setDir(IsoDirections.fromAngle(this.temp));
               var3.setForwardDirection(this.temp);
            }

            if (var1.getPathFindBehavior2().walkingOnTheSpot.check(var1.x, var1.y)) {
               var1.setVariable("bMoving", false);
            }

    long var14 = (int64_t)var2.get(PARAM_TICK_COUNT);
            if (IngameState.instance.numberTicks - var14 == 2L) {
               var3.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
            }
         }
      } else {
         var3.AllowRepathDelay = 0.0F;
         var3.pathToLocation(var1.getPathTargetX(), var1.getPathTargetY(), var1.getPathTargetZ());
         if (!var3.getVariableBoolean("bPathfind")) {
            var3.setVariable("bPathfind", true);
            var3.setVariable("bMoving", false);
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setVariable("bMoving", false);
      ((IsoZombie)var1).networkAI.extraUpdate();
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }

    bool isMoving(IsoGameCharacter var1) {
    return true;
   }

    bool isPathClear(IsoGameCharacter var1, float var2, float var3, float var4) {
    int var5 = (int)var2 / 10;
    int var6 = (int)var3 / 10;
      IsoChunk var7 = GameServer.bServer
         ? ServerMap.instance.getChunk(var5, var6)
         : IsoWorld.instance.CurrentCell.getChunkForGridSquare((int)var2, (int)var3, (int)var4);
      if (var7 != nullptr) {
    int var8 = 1;
         var8 |= 2;
         return !PolygonalMap2.instance.lineClearCollide(var1.getX(), var1.getY(), var2, var3, (int)var4, var1.getPathFindBehavior2().getTargetChar(), var8);
      } else {
    return false;
      }
   }

    bool calculateTargetLocation(IsoZombie var1, Vector2 var2) {
      assert var1.isCurrentState(this);

    std::unordered_map var3 = var1.getStateMachineParams(this);
      var2.x = var1.getPathFindBehavior2().getTargetX();
      var2.y = var1.getPathFindBehavior2().getTargetY();
      this.temp.set(var2);
      this.temp.x = this.temp.x - var1.getX();
      this.temp.y = this.temp.y - var1.getY();
    float var4 = this.temp.getLength();
      if (var4 < 0.025F) {
    return false;
      } else if (!GameServer.bServer && !var1.bCrawling && var3.get(PARAM_IGNORE_OFFSET) == bool.FALSE) {
    float var5 = Math.min(var4 / 2.0F, 4.0F);
    float var6 = (var1.getID() + var1.ZombieID) % 20 / 10.0F - 1.0F;
    float var7 = (var1.getID() + var1.ZombieID) % 20 / 10.0F - 1.0F;
         var2.x += var6 * var5;
         var2.y += var7 * var5;
    return true;
      } else {
    return false;
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
