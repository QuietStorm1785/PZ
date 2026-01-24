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
      static PlayerGetUpState& instance();
      void enter(IsoGameCharacter* character) override;
      void execute(IsoGameCharacter* character) override;
      void exit(IsoGameCharacter* character) override;
private:
      PlayerGetUpState() = default;

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
