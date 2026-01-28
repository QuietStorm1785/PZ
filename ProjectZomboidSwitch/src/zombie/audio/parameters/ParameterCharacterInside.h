#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterCharacterInside : public OpenALParameterStub {
public:
    const IsoGameCharacter character;

    public ParameterCharacterInside(IsoGameCharacter var1) {
      super("CharacterInside");
      this.character = var1;
   }

    float calculateCurrentValue() {
      if (this.character.getVehicle() == nullptr) {
         return this.character.getCurrentBuilding() == nullptr ? 0.0F : 1.0F;
      } else {
         return 2.0F;
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
