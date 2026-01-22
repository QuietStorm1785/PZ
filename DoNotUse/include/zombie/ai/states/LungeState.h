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
#include "zombie/characters/IsoZombie/ZombieSound.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace ai {
namespace states {


class LungeState : public State {
public:
    static const LungeState _instance = std::make_shared<LungeState>();
    const Vector2 temp = std::make_shared<Vector2>();
    static const int PARAM_TICK_COUNT = 0;

    static LungeState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      if (System.currentTimeMillis() - var2.LungeSoundTime > 5000L) {
    std::string var4 = "MaleZombieAttack";
         if (var2.isFemale()) {
            var4 = "FemaleZombieAttack";
         }

         if (GameServer.bServer) {
            GameServer.sendZombieSound(ZombieSound.Lunge, var2);
         }

         var2.LungeSoundTime = System.currentTimeMillis();
      }

      var2.LungeTimer = 180.0F;
      var3.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var1.setOnFloor(false);
      var1.setShootable(true);
      if (var2.bLunger) {
         var2.walkVariantUse = "ZombieWalk3";
      }

      var2.LungeTimer = var2.LungeTimer - GameTime.getInstance().getMultiplier() / 1.6F;
    IsoPlayer var4 = (IsoPlayer)Type.tryCastTo(var2.getTarget(), IsoPlayer.class);
      if (var4 != nullptr && var4.isGhostMode()) {
         var2.LungeTimer = 0.0F;
      }

      if (var2.LungeTimer < 0.0F) {
         var2.LungeTimer = 0.0F;
      }

      if (var2.LungeTimer <= 0.0F) {
         var2.AllowRepathDelay = 0.0F;
      }

      this.temp.x = var2.vectorToTarget.x;
      this.temp.y = var2.vectorToTarget.y;
      var2.getZombieLungeSpeed();
      this.temp.normalize();
      var2.setForwardDirection(this.temp);
      var2.DirectionFromVector(this.temp);
      var2.getVectorFromDirection(var2.getForwardDirection());
      var2.setForwardDirection(this.temp);
      if (!var2.isTargetLocationKnown()
         && var2.LastTargetSeenX != -1
         && !var1.getPathFindBehavior2().isTargetLocation(var2.LastTargetSeenX + 0.5F, var2.LastTargetSeenY + 0.5F, var2.LastTargetSeenZ)) {
         var2.LungeTimer = 0.0F;
         var1.pathToLocation(var2.LastTargetSeenX, var2.LastTargetSeenY, var2.LastTargetSeenZ);
      }

    long var5 = (int64_t)var3.get(PARAM_TICK_COUNT);
      if (IngameState.instance.numberTicks - var5 == 2L) {
         ((IsoZombie)var1).parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.LockTarget);
      }
   }

    void exit(IsoGameCharacter var1) {
   }

    bool isMoving(IsoGameCharacter var1) {
    return true;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
