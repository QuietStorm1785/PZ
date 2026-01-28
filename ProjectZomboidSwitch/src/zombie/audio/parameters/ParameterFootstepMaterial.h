#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

#include "zombie/audio/parameters/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial/FootstepMaterial.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/util/list/PZArrayList.h"

namespace zombie {
namespace audio {
namespace parameters {


// OpenAL stub for ParameterFootstepMaterial
class ParameterFootstepMaterial : public zombie::audio::OpenALParameterStub {
public:
      ParameterFootstepMaterial(void* /*character*/) : OpenALParameterStub("FootstepMaterial") {}
      float calculateCurrentValue() override { return 0.0f; }
};
    IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != nullptr && var2 != this.character && !var2.Traits.Deaf.isSet()) {
               if ((int)var2.getZ() < (int)this.character.getZ()) {
                  return FootstepMaterial.Upstairs;
               }
               break;
            }
         }
      }

    void* var9 = nullptr;
    IsoObject var10 = nullptr;
    IsoGridSquare var3 = this.character.getCurrentSquare();
      if (var3 != nullptr) {
    PZArrayList var4 = var3.getObjects();

         for (int var5 = 0; var5 < var4.size(); var5++) {
    IsoObject var6 = (IsoObject)var4.get(var5);
            if (!(dynamic_cast<IsoWorldInventoryObject*>(var6) != nullptr)) {
    PropertyContainer var7 = var6.getProperties();
               if (var7 != nullptr) {
                  if (var7.Is(IsoFlagType.solidfloor)) {
                     ;
                  }

                  if (var7.Is("FootstepMaterial")) {
                     var10 = var6;
                  }
               }
            }
         }
      }

      if (var10 != nullptr) {
         try {
    std::string var11 = var10.getProperties().Val("FootstepMaterial");
            return FootstepMaterial.valueOf(var11);
         } catch (IllegalArgumentException var8) {
    bool var12 = true;
         }
      }

      return FootstepMaterial.Concrete;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
