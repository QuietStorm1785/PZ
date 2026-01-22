#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/ai/astar/AStarPathFinder/PathFindProgress.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/vehicles/PathFindBehavior2/BehaviorResult.h"

namespace zombie {
namespace vehicles {


class PathFindState2 : public State {
public:
    static const int PARAM_TICK_COUNT = 0;

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var1.setVariable("bPathfind", true);
      var1.setVariable("bMoving", false);
      ((IsoZombie)var1).networkAI.extraUpdate();
      var2.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    BehaviorResult var3 = var1.getPathFindBehavior2().update();
      if (var3 == BehaviorResult.Failed) {
         var1.setPathFindIndex(-1);
         var1.setVariable("bPathfind", false);
         var1.setVariable("bMoving", false);
      } else if (var3 == BehaviorResult.Succeeded) {
    int var7 = (int)var1.getPathFindBehavior2().getTargetX();
    int var5 = (int)var1.getPathFindBehavior2().getTargetY();
         IsoChunk var6 = GameServer.bServer
            ? ServerMap.instance.getChunk(var7 / 10, var5 / 10)
            : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var7, var5, 0);
         if (var6 == nullptr) {
            var1.setVariable("bPathfind", false);
            var1.setVariable("bMoving", true);
         } else {
            var1.setVariable("bPathfind", false);
            var1.setVariable("bMoving", false);
            var1.setPath2(nullptr);
         }
      } else {
         if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
    long var4 = (int64_t)var2.get(PARAM_TICK_COUNT);
            if (IngameState.instance.numberTicks - var4 == 2L) {
               ((IsoZombie)var1).parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
            }
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
         ((IsoZombie)var1).networkAI.extraUpdate();
         ((IsoZombie)var1).AllowRepathDelay = 0.0F;
      }

      var1.setVariable("bPathfind", false);
      var1.setVariable("bMoving", false);
      var1.setVariable("ShouldBeCrawling", false);
      PolygonalMap2.instance.cancelRequest(var1);
      var1.getFinder().progress = PathFindProgress.notrunning;
      var1.setPath2(nullptr);
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }

    bool isMoving(IsoGameCharacter var1) {
      return var1.isMoving();
   }
}
} // namespace vehicles
} // namespace zombie
