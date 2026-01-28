#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterEquippedBaggageContainer/ContainerType.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterEquippedBaggageContainer : public OpenALParameterStub {
public:
    const IsoGameCharacter character;
    ContainerType containerType = ContainerType.None;

    public ParameterEquippedBaggageContainer(IsoGameCharacter var1) {
      super("EquippedBaggageContainer");
      this.character = var1;
   }

    float calculateCurrentValue() {
      return this.containerType.label;
   }

    void setContainerType(ContainerType var1) {
      this.containerType = var1;
   }

    void setContainerType(const std::string& var1) {
      if (var1 != nullptr) {
         try {
            this.containerType = ContainerType.valueOf(var1);
         } catch (IllegalArgumentException var3) {
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
