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
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieGetDownState : public State {
public:
    static const ZombieGetDownState _instance = std::make_shared<ZombieGetDownState>();
    static const int PARAM_PREV_STATE = 1;
    static const int PARAM_WAIT_TIME = 2;
    static const int PARAM_START_X = 3;
    static const int PARAM_START_Y = 4;

    static ZombieGetDownState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var2.put(PARAM_PREV_STATE, var1.getStateMachine().getPrevious());
      var2.put(PARAM_START_X, var1.getX());
      var2.put(PARAM_START_Y, var1.getY());
      var1.setStateEventDelayTimer((float)var2.get(PARAM_WAIT_TIME));
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
   }

    void exit(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoZombie var3 = (IsoZombie)var1;
      var3.setStateEventDelayTimer(0.0F);
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
    IsoZombie var3 = (IsoZombie)var1;
      if (var2.m_EventName.equalsIgnoreCase("StartCrawling") && !var3.isCrawling()) {
         var3.toggleCrawling();
      }
   }

    bool isNearStartXY(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    float var3 = (float)var2.get(PARAM_START_X);
    float var4 = (float)var2.get(PARAM_START_Y);
      return var3 != nullptr && var4 != nullptr ? var1.DistToSquared(var3, var4) <= 0.25F : false;
   }

    void setParams(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var2.put(PARAM_WAIT_TIME, Rand.Next(60.0F, 150.0F));
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
