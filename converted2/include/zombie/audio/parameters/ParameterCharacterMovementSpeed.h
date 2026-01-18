#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterCharacterMovementSpeed : public FMODLocalParameter {
public:
  const IsoGameCharacter character;
private
  ParameterCharacterMovementSpeed.MovementType movementType =
      ParameterCharacterMovementSpeed.MovementType.Walk;

public
  ParameterCharacterMovementSpeed(IsoGameCharacter _character) {
    super("CharacterMovementSpeed");
    this.character = _character;
  }

  float calculateCurrentValue() { return this.movementType.label; }

  void
  setMovementType(ParameterCharacterMovementSpeed.MovementType _movementType) {
    this.movementType = _movementType;
  }

public
  static enum MovementType {
    SneakWalk(0), SneakRun(1), Strafe(2), Walk(3), Run(4), Sprint(5);

    const int label;

    private MovementType(int int1){this.label = int1;}
}
} // namespace parameters
} // namespace audio
} // namespace zombie
} // namespace zombie
