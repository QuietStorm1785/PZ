#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface/Material.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterMeleeHitSurface : public FMODLocalParameter {
public:
    const IsoGameCharacter character;
    Material material = Material.Default;

    public ParameterMeleeHitSurface(IsoGameCharacter var1) {
      super("MeleeHitSurface");
      this.character = var1;
   }

    float calculateCurrentValue() {
      return this.getMaterial().label;
   }

    Material getMaterial() {
      return this.material;
   }

    void setMaterial(Material var1) {
      this.material = var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
