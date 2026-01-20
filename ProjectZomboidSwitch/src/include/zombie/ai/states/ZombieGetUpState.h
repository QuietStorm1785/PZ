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
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieGetUpState : public State {
public:
    static const ZombieGetUpState _instance = std::make_shared<ZombieGetUpState>();
    static const int PARAM_STANDING = 1;
    static const int PARAM_PREV_STATE = 2;

    static ZombieGetUpState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var3.put(PARAM_STANDING, bool.FALSE);
    State var4 = var1.getStateMachine().getPrevious();
      if (var4 == ZombieGetUpFromCrawlState.instance()) {
         var4 = (State)var1.getStateMachineParams(ZombieGetUpFromCrawlState.instance()).get(1);
      }

      var3.put(PARAM_PREV_STATE, var4);
      var2.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.GettingUp);
      if (GameClient.bClient) {
         var1.setKnockedDown(false);
      }
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    bool var3 = var2.get(PARAM_STANDING) == bool.TRUE;
      var1.setOnFloor(!var3);
      ((IsoZombie)var1).setKnockedDown(!var3);
   }

    void exit(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoZombie var3 = (IsoZombie)var1;
      var1.setCollidable(true);
      var1.clearVariable("SprinterTripped");
      var1.clearVariable("ShouldStandUp");
      if (StringUtils.isNullOrEmpty(var1.getHitReaction())) {
         var3.setSitAgainstWall(false);
      }

      var3.setKnockedDown(false);
      var3.AllowRepathDelay = 0.0F;
      if (var2.get(PARAM_PREV_STATE) == PathFindState.instance()) {
         if (var1.getPathFindBehavior2().getTargetChar() == nullptr) {
            var1.setVariable("bPathfind", true);
            var1.setVariable("bMoving", false);
         } else if (var3.isTargetLocationKnown()) {
            var1.pathToCharacter(var1.getPathFindBehavior2().getTargetChar());
         } else if (var3.LastTargetSeenX != -1) {
            var1.pathToLocation(var3.LastTargetSeenX, var3.LastTargetSeenY, var3.LastTargetSeenZ);
         }
      } else if (var2.get(PARAM_PREV_STATE) == WalkTowardState.instance()) {
         var1.setVariable("bPathFind", false);
         var1.setVariable("bMoving", true);
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
    IsoZombie var4 = (IsoZombie)var1;
      if (var2.m_EventName.equalsIgnoreCase("IsAlmostUp")) {
         var3.put(PARAM_STANDING, bool.TRUE);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
