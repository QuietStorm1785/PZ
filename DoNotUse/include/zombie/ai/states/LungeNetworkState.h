#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/Vector2.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace ai {
namespace states {


class LungeNetworkState : public State {
public:
    static LungeNetworkState _instance = std::make_shared<LungeNetworkState>();
    Vector2 temp = std::make_shared<Vector2>();
    const Vector3f worldPos = std::make_shared<Vector3f>();
    static const int PARAM_TICK_COUNT = 0;

    static LungeNetworkState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      WalkTowardNetworkState.instance().enter(var1);
    IsoZombie var3 = (IsoZombie)var1;
      var3.LungeTimer = 180.0F;
      var2.put(PARAM_TICK_COUNT, IngameState.instance.numberTicks);
   }

    void execute(IsoGameCharacter var1) {
      WalkTowardNetworkState.instance().execute(var1);
    IsoZombie var2 = (IsoZombie)var1;
      var1.setOnFloor(false);
      var1.setShootable(true);
      if (var2.bLunger) {
         var2.walkVariantUse = "ZombieWalk3";
      }

      var2.LungeTimer = var2.LungeTimer - GameTime.getInstance().getMultiplier() / 1.6F;
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var2.getTarget(), IsoPlayer.class);
      if (var3 != nullptr && var3.isGhostMode()) {
         var2.LungeTimer = 0.0F;
      }

      if (var2.LungeTimer < 0.0F) {
         var2.LungeTimer = 0.0F;
      }

      if (var2.LungeTimer <= 0.0F) {
         var2.AllowRepathDelay = 0.0F;
      }

    std::unordered_map var4 = var1.getStateMachineParams(this);
    long var5 = (int64_t)var4.get(PARAM_TICK_COUNT);
      if (IngameState.instance.numberTicks - var5 == 2L) {
         ((IsoZombie)var1).parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.LockTarget);
      }
   }

    void exit(IsoGameCharacter var1) {
      WalkTowardNetworkState.instance().exit(var1);
   }

    bool isMoving(IsoGameCharacter var1) {
    return true;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
