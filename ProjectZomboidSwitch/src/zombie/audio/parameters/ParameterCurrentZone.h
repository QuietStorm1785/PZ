#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/parameters/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterCurrentZone/Zone.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterCurrentZone : public zombie::audio::OpenALParameterStub {
public:
    const IsoObject object;
   private zombie.iso.IsoMetaGrid.Zone metaZone;
    Zone zone = Zone.None;

    public ParameterCurrentZone(IsoObject var1) {
      super("CurrentZone");
      this.object = var1;
   }

    float calculateCurrentValue() {
    IsoGridSquare var1 = this.object.getSquare();
      if (var1 == nullptr) {
         this.zone = Zone.None;
         return this.zone.label;
      } else if (var1.zone == this.metaZone) {
         return this.zone.label;
      } else {
         this.metaZone = var1.zone;
         if (this.metaZone == nullptr) {
            this.zone = Zone.None;
            return this.zone.label;
         } else {
    std::string var2 = this.metaZone.type;

            this.zone = switch (var2) {
               case "DeepForest" -> Zone.DeepForest;
               case "Farm" -> Zone.Farm;
               case "Forest" -> Zone.Forest;
               case "Nav" -> Zone.Nav;
               case "TownZone" -> Zone.Town;
               case "TrailerPark" -> Zone.TrailerPark;
               case "Vegitation" -> Zone.Vegetation;
               default -> Zone.None;
            };
            return this.zone.label;
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
