#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include "zombie/network/ServerMap.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PathFindBehavior2/BehaviorResult.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace ai {
namespace states {


class WalkTowardNetworkState : public State {
public:
    static WalkTowardNetworkState _instance = std::make_shared<WalkTowardNetworkState>();
    static const int PARAM_TICK_COUNT = 2;

    static WalkTowardNetworkState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var2.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
      var1.setVariable("bMoving", true);
      var1.setVariable("bPathfind", false);
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    PathFindBehavior2 var3 = var2.getPathFindBehavior2();
      var2.vectorToTarget.x = var2.networkAI.targetX - var2.x;
      var2.vectorToTarget.y = var2.networkAI.targetY - var2.y;
      var3.walkingOnTheSpot.reset(var2.x, var2.y);
      if (var2.z != var2.networkAI.targetZ || var2.networkAI.predictionType != PredictionTypes.Thump && var2.networkAI.predictionType != PredictionTypes.Climb) {
         if (var2.z == var2.networkAI.targetZ
            && !PolygonalMap2.instance.lineClearCollide(var2.x, var2.y, var2.networkAI.targetX, var2.networkAI.targetY, var2.networkAI.targetZ, nullptr)) {
            if (var2.networkAI.usePathFind) {
               var3.reset();
               var2.setPath2(nullptr);
               var2.networkAI.usePathFind = false;
            }

            var3.moveToPoint(var2.networkAI.targetX, var2.networkAI.targetY, 1.0F);
            var2.setVariable("bMoving", IsoUtils.DistanceManhatten(var2.networkAI.targetX, var2.networkAI.targetY, var2.nx, var2.ny) > 0.5F);
         } else {
            if (!var2.networkAI.usePathFind) {
               var3.pathToLocationF(var2.networkAI.targetX, var2.networkAI.targetY, var2.networkAI.targetZ);
               var3.walkingOnTheSpot.reset(var2.x, var2.y);
               var2.networkAI.usePathFind = true;
            }

    BehaviorResult var4 = var3.update();
            if (var4 == BehaviorResult.Failed) {
               var2.setPathFindIndex(-1);
               return;
            }

            if (var4 == BehaviorResult.Succeeded) {
    int var5 = (int)var2.getPathFindBehavior2().getTargetX();
    int var6 = (int)var2.getPathFindBehavior2().getTargetY();
               IsoChunk var7 = GameServer.bServer
                  ? ServerMap.instance.getChunk(var5 / 10, var6 / 10)
                  : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var5, var6, 0);
               if (var7 == nullptr) {
                  var2.setVariable("bMoving", true);
                  return;
               }

               var2.setPath2(nullptr);
               var2.setVariable("bMoving", true);
               return;
            }
         }
      } else {
         if (var2.networkAI.usePathFind) {
            var3.reset();
            var2.setPath2(nullptr);
            var2.networkAI.usePathFind = false;
         }

         var3.moveToPoint(var2.networkAI.targetX, var2.networkAI.targetY, 1.0F);
         var2.setVariable("bMoving", IsoUtils.DistanceManhatten(var2.networkAI.targetX, var2.networkAI.targetY, var2.nx, var2.ny) > 0.5F);
      }

      if (!((IsoZombie)var1).bCrawling) {
         var1.setOnFloor(false);
      }

    bool var8 = var1.isCollidedWithVehicle();
      if (var2.dynamic_cast<IsoGameCharacter*>(target) != nullptr
         && ((IsoGameCharacter)var2.target).getVehicle() != nullptr
         && ((IsoGameCharacter)var2.target).getVehicle().isCharacterAdjacentTo(var1)) {
         var8 = false;
      }

      if (var1.isCollidedThisFrame() || var8) {
         var2.AllowRepathDelay = 0.0F;
         var2.pathToLocation(var1.getPathTargetX(), var1.getPathTargetY(), var1.getPathTargetZ());
         if (!"true" == var2.getVariableString("bPathfind"))) {
            var2.setVariable("bPathfind", true);
            var2.setVariable("bMoving", false);
         }
      }

    std::unordered_map var9 = var1.getStateMachineParams(this);
    long var10 = (int64_t)var9.get(PARAM_TICK_COUNT);
      if (IngameState.instance.numberTicks - var10 == 2L) {
         var2.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setVariable("bMoving", false);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
