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

namespace zombie {
namespace ai {
namespace states {


class ZombieGetUpFromCrawlState : public State {
public:
    static const ZombieGetUpFromCrawlState _instance = std::make_shared<ZombieGetUpFromCrawlState>();

    static ZombieGetUpFromCrawlState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoZombie var3 = (IsoZombie)var1;
      var2.put(1, var1.getStateMachine().getPrevious());
      if (var3.isCrawling()) {
         var3.toggleCrawling();
         var3.setOnFloor(true);
      }
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoZombie var3 = (IsoZombie)var1;
      var3.AllowRepathDelay = 0.0F;
      if (var2.get(1) == PathFindState.instance()) {
         if (var1.getPathFindBehavior2().getTargetChar() == nullptr) {
            var1.setVariable("bPathfind", true);
            var1.setVariable("bMoving", false);
         } else if (var3.isTargetLocationKnown()) {
            var1.pathToCharacter(var1.getPathFindBehavior2().getTargetChar());
         } else if (var3.LastTargetSeenX != -1) {
            var1.pathToLocation(var3.LastTargetSeenX, var3.LastTargetSeenY, var3.LastTargetSeenZ);
         }
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
