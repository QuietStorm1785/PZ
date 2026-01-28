#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterVehicleRoadMaterial/Material.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleRoadMaterial : public OpenALParameterStub {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleRoadMaterial(BaseVehicle var1) {
      super("VehicleRoadMaterial");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
      if (!this.vehicle.isEngineRunning()) {
         return float.isNaN(this.getCurrentValue()) ? 0.0F : this.getCurrentValue();
      } else {
         return this.getMaterial().label;
      }
   }

    Material getMaterial() {
    IsoGridSquare var1 = this.vehicle.getCurrentSquare();
      if (var1 == nullptr) {
         return Material.Concrete;
      } else {
    IsoObject var2 = this.vehicle.getCurrentSquare().getFloor();
         if (var2 != nullptr && var2.getSprite() != nullptr && var2.getSprite().getName() != nullptr) {
    std::string var3 = var2.getSprite().getName();
            if (var3.endsWith("blends_natural_01_5")
               || var3.endsWith("blends_natural_01_6")
               || var3.endsWith("blends_natural_01_7")
               || var3.endsWith("blends_natural_01_0")) {
               return Material.Sand;
            } else if (var3.endsWith("blends_natural_01_64")
               || var3.endsWith("blends_natural_01_69")
               || var3.endsWith("blends_natural_01_70")
               || var3.endsWith("blends_natural_01_71")) {
               return Material.Dirt;
            } else if (var3.startsWith("blends_natural_01")) {
               return Material.Grass;
            } else if (var3.endsWith("blends_street_01_48")
               || var3.endsWith("blends_street_01_53")
               || var3.endsWith("blends_street_01_54")
               || var3.endsWith("blends_street_01_55")) {
               return Material.Gravel;
            } else if (var3.startsWith("floors_interior_tilesandwood_01_")) {
    int var5 = int.parseInt(var3.replaceFirst("floors_interior_tilesandwood_01_", ""));
               return var5 > 40 && var5 < 48 ? Material.Wood : Material.Concrete;
            } else if (var3.startsWith("carpentry_02_")) {
               return Material.Wood;
            } else if (var3.contains("interior_carpet_")) {
               return Material.Carpet;
            } else {
    float var4 = var1.getPuddlesInGround();
               return var4 > 0.1 ? Material.Puddle : Material.Concrete;
            }
         } else {
            return Material.Concrete;
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
