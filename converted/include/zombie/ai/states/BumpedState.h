#pragma once
#include "fmod/fmod/FMODManager.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BumpedState : public State {
public:
  static const BumpedState _instance = new BumpedState();

  static BumpedState instance() { return _instance; }

  void enter(IsoGameCharacter character) {
    character.setBumpDone(false);
    character.setVariable("BumpFallAnimFinished", false);
    character.getAnimationPlayer().setTargetToAngle();
    character.getForwardDirection().setLengthAndDirection(
        character.getAnimationPlayer().getAngle(), 1.0F);
    this.setCharacterBlockMovement(character, true);
    if (character.getVariableBoolean("BumpFall")) {
      long long0 = character.playSound("TripOverObstacle");
      ParameterCharacterMovementSpeed parameterCharacterMovementSpeed =
          ((IsoPlayer)character).getParameterCharacterMovementSpeed();
      character.getEmitter().setParameterValue(
          long0, parameterCharacterMovementSpeed.getParameterDescription(),
          parameterCharacterMovementSpeed.calculateCurrentValue());
      std::string string = character.getVariableString("TripObstacleType");
      if (string == nullptr) {
        string = "zombie";
      }

      character.clearVariable("TripObstacleType");
      uint8_t byte0 = -1;
      switch (string.hashCode()) {
      case 3568542:
        if (string == "tree")) {
                        byte0 = 0;
                    }
      default:
        byte byte1 = switch (byte0) {
                        case 0 -> 5;
                        default -> 6;
                    };
                    character.getEmitter().setParameterValue(long0, FMODManager.instance.getParameterDescription("TripObstacleType"), byte1);
            }
        }
    }

    void execute(IsoGameCharacter character) {
    bool boolean0 = character.isBumpFall() || character.isBumpStaggered();
        this.setCharacterBlockMovement(character, boolean0);
    }

    void setCharacterBlockMovement(IsoGameCharacter character, bool boolean0) {
    IsoPlayer player = Type.tryCastTo(character, IsoPlayer.class);
        if (player != nullptr) {
            player.setBlockMovement(boolean0);
        }
    }

    void exit(IsoGameCharacter character) {
        character.clearVariable("BumpFallType");
        character.clearVariable("BumpFallAnimFinished");
        character.clearVariable("BumpAnimFinished");
        character.setBumpType("");
        character.setBumpedChr(nullptr);
    IsoPlayer player = Type.tryCastTo(character, IsoPlayer.class);
        if (player != nullptr) {
            player.setInitiateAttack(false);
            player.attackStarted = false;
            player.setAttackType(nullptr);
        }

        if (player != nullptr && character.isBumpFall()) {
            character.fallenOnKnees();
        }

        character.setOnFloor(false);
        character.setBumpFall(false);
        this.setCharacterBlockMovement(character, false);
        if (character instanceof IsoZombie && ((IsoZombie)character).target != nullptr) {
            character.pathToLocation(
                (int)((IsoZombie)character).target.getX(), (int)((IsoZombie)character).target.getY(), (int)((IsoZombie)character).target.getZ()
            );
        }
    }

    void animEvent(IsoGameCharacter character, AnimEvent animEvent) {
        if (animEvent.m_EventName.equalsIgnoreCase("FallOnFront")) {
            character.setFallOnFront(Boolean.parseBoolean(animEvent.m_ParameterValue));
            character.setOnFloor(character.isFallOnFront());
        }

        if (animEvent.m_EventName.equalsIgnoreCase("FallOnBack")) {
            character.setOnFloor(Boolean.parseBoolean(animEvent.m_ParameterValue));
        }
    }
}
} // namespace states
} // namespace ai
} // namespace zombie
