#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/parameters/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial2/FootstepMaterial2.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/objects/IsoBrokenGlass.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterFootstepMaterial2 : public zombie::audio::OpenALParameterStub {
public:
    const IsoGameCharacter character;

    public ParameterFootstepMaterial2(IsoGameCharacter var1) {
      super("FootstepMaterial2");
      this.character = var1;
   }

    float calculateCurrentValue() {
      return this.getMaterial().label;
   }

    FootstepMaterial2 getMaterial() {
      if (this.character.getCurrentSquare() == nullptr) {
         return FootstepMaterial2.None;
      } else {
    IsoBrokenGlass var1 = this.character.getCurrentSquare().getBrokenGlass();
         if (var1 != nullptr) {
            return FootstepMaterial2.BrokenGlass;
         } else {
    float var2 = this.character.getCurrentSquare().getPuddlesInGround();
            if (var2 > 0.5F) {
               return FootstepMaterial2.PuddleDeep;
            } else {
               return var2 > 0.1F ? FootstepMaterial2.PuddleShallow : FootstepMaterial2.None;
            }
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
