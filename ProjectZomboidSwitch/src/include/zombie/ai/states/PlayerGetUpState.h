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
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerGetUpState : public State {
public:
    static const PlayerGetUpState _instance = std::make_shared<PlayerGetUpState>();

    static PlayerGetUpState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var1.setIgnoreMovement(true);
    IsoPlayer var3 = (IsoPlayer)var1;
      var3.setInitiateAttack(false);
      var3.attackStarted = false;
      var3.setAttackType(nullptr);
      var3.setBlockMovement(true);
      var3.setForceRun(false);
      var3.setForceSprint(false);
      var1.setVariable("getUpQuick", var1.getVariableBoolean("pressedRunButton"));
      if (var1.getMoodles().getMoodleLevel(MoodleType.Panic) > 1) {
         var1.setVariable("getUpQuick", true);
      }

      if (var1.getVariableBoolean("pressedMovement")) {
         var1.setVariable("getUpWalk", true);
      }

      if (GameClient.bClient) {
         var1.setKnockedDown(false);
      }
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      var1.clearVariable("getUpWalk");
      if (var1.getVariableBoolean("sitonground")) {
         var1.setHideWeaponModel(false);
      }

      var1.setIgnoreMovement(false);
      var1.setFallOnFront(false);
      var1.setOnFloor(false);
      ((IsoPlayer)var1).setBlockMovement(false);
      var1.setSitOnGround(false);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
