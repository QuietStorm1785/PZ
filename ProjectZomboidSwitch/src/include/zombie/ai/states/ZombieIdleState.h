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
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/objects/RainManager.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieIdleState : public State {
public:
    static const ZombieIdleState _instance = std::make_shared<ZombieIdleState>();
    static const int PARAM_TICK_COUNT = 0;

    static ZombieIdleState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      ((IsoZombie)var1).soundSourceTarget = nullptr;
      ((IsoZombie)var1).soundAttract = 0.0F;
      ((IsoZombie)var1).movex = 0.0F;
      ((IsoZombie)var1).movey = 0.0F;
      var1.setStateEventDelayTimer(this.pickRandomWanderInterval());
      if (IngameState.instance == nullptr) {
         var2.put(PARAM_TICK_COUNT, 0L);
      } else {
         var2.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
      }
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var2.movex = 0.0F;
      var2.movey = 0.0F;
      if (Core.bLastStand) {
    IsoPlayer var8 = nullptr;
    float var5 = 1000000.0F;

         for (int var9 = 0; var9 < IsoPlayer.numPlayers; var9++) {
            if (IsoPlayer.players[var9] != nullptr && IsoPlayer.players[var9].DistTo(var1) < var5 && !IsoPlayer.players[var9].isDead()) {
               var5 = IsoPlayer.players[var9].DistTo(var1);
               var8 = IsoPlayer.players[var9];
            }
         }

         if (var8 != nullptr) {
            var2.pathToCharacter(var8);
         }
      } else {
         if (((IsoZombie)var1).bCrawling) {
            var1.setOnFloor(true);
         } else {
            var1.setOnFloor(false);
         }

    long var4 = (int64_t)var3.get(PARAM_TICK_COUNT);
         if (IngameState.instance.numberTicks - var4 == 2L) {
            ((IsoZombie)var1).parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
         }

         if (!var2.bIndoorZombie) {
            if (!var2.isUseless()) {
               if (var2.getStateEventDelayTimer() <= 0.0F) {
                  var1.setStateEventDelayTimer(this.pickRandomWanderInterval());
    int var6 = (int)var1.getX() + (Rand.Next(8) - 4);
    int var7 = (int)var1.getY() + (Rand.Next(8) - 4);
                  if (var1.getCell().getGridSquare(var6, var7, var1.getZ()) != nullptr && var1.getCell().getGridSquare(var6, var7, var1.getZ()).isFree(true)) {
                     var1.pathToLocation(var6, var7, (int)var1.getZ());
                     var2.AllowRepathDelay = 200.0F;
                  }
               }

               var2.networkAI.mindSync.zombieIdleUpdate();
            }
         }
      }
   }

    void exit(IsoGameCharacter var1) {
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }

    float pickRandomWanderInterval() {
    float var1 = Rand.Next(400, 1000);
      if (!RainManager.isRaining()) {
         var1 *= 1.5F;
      }

    return var1;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
