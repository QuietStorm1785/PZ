#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/Vector2.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/Element.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class RVSBurntCar : public RandomizedVehicleStoryBase {
public:
    public RVSBurntCar() {
      this.name = "Burnt Car";
      this.minZoneWidth = 2;
      this.minZoneHeight = 5;
      this.setChance(13);
   }

    void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
   }

    bool initVehicleStorySpawner(Zone var1, IsoChunk var2, bool var3) {
    VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
    Vector2 var5 = IsoDirections.N.ToVector();
    float var6 = (float) (Math.PI / 6);
      if (var3) {
         var6 = 0.0F;
      }

      var5.rotate(Rand.Next(-var6, var6));
      var4.addElement("vehicle1", 0.0F, 0.0F, var5.getDirection(), 2.0F, 5.0F);
      var4.setParameter("zone", var1);
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = var2.z;
    Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
    std::string var6 = var2.id;
    uint8_t var7 = -1;
         switch (var6.hashCode()) {
            case 2014205573:
               if (var6 == "vehicle1")) {
                  var7 = 0;
               }
            default:
               switch (var7) {
                  case 0:
    BaseVehicle var8 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, nullptr, "Base.CarNormal", nullptr, nullptr);
                     if (var8 != nullptr) {
                        var8 = var8.setSmashed("right");
                     }
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
