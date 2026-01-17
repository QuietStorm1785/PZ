#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
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

class ZombieTurnAlerted : public State {
public:
  static const ZombieTurnAlerted _instance = new ZombieTurnAlerted();
  static const int PARAM_TARGET_ANGLE = 0;

  static ZombieTurnAlerted instance() { return _instance; }

  void enter(IsoGameCharacter character) {
    std::unordered_map hashMap = character.getStateMachineParams(this);
    float float0 = (Float)hashMap.get(PARAM_TARGET_ANGLE);
    character.getAnimationPlayer().setTargetAngle(float0);
  }

  void execute(IsoGameCharacter var1) {}

  void exit(IsoGameCharacter character) {
    character.pathToSound(character.getPathTargetX(),
                          character.getPathTargetY(),
                          character.getPathTargetZ());
    ((IsoZombie)character).alerted = false;
  }

  void setParams(IsoGameCharacter character, float float0) {
    std::unordered_map hashMap = character.getStateMachineParams(this);
    hashMap.clear();
    hashMap.put(PARAM_TARGET_ANGLE, float0);
  }
}
} // namespace states
} // namespace ai
} // namespace zombie
