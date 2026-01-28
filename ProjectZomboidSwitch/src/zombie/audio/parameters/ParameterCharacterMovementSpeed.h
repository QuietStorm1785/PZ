#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed/MovementType.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterCharacterMovementSpeed : public OpenALParameterStub {
public:
    const IsoGameCharacter character;
    MovementType movementType = MovementType.Walk;

    public ParameterCharacterMovementSpeed(IsoGameCharacter var1) {
      super("CharacterMovementSpeed");
      this.character = var1;
   }

    float calculateCurrentValue() {
      return this.movementType.label;
   }

    void setMovementType(MovementType var1) {
      this.movementType = var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
