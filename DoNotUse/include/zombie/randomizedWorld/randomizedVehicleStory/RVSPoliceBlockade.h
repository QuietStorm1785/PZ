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
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class RVSPoliceBlockade : public RandomizedVehicleStoryBase {
public:
    public RVSPoliceBlockade() {
      this.name = "Police Blockade";
      this.minZoneWidth = 8;
      this.minZoneHeight = 8;
      this.setChance(3);
      this.setMaximumDays(30);
   }

    void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
   }

    bool initVehicleStorySpawner(Zone var1, IsoChunk var2, bool var3) {
    VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
    float var5 = (float) (Math.PI / 18);
      if (var3) {
         var5 = 0.0F;
      }

    float var6 = 1.5F;
    float var7 = 1.0F;
      if (this.zoneWidth >= 10) {
         var6 = 2.5F;
         var7 = 0.0F;
      }

    IsoDirections var8 = Rand.NextBool(2) ? IsoDirections.W : IsoDirections.E;
    Vector2 var9 = var8.ToVector();
      var9.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle1", -var6, var7, var9.getDirection(), 2.0F, 5.0F);
      var9 = var8.RotLeft(4).ToVector();
      var9.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle2", var6, -var7, var9.getDirection(), 2.0F, 5.0F);
    std::string var10 = "Base.CarLightsPolice";
      if (Rand.NextBool(3)) {
         var10 = "Base.PickUpVanLightsPolice";
      }

      var4.setParameter("zone", var1);
      var4.setParameter("script", var10);
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = var2.z;
    Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
    std::string var6 = var1.getParameterString("script");
    std::string var7 = var2.id;
         switch (var7) {
            case "vehicle1":
            case "vehicle2":
    BaseVehicle var9 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, nullptr, var6, nullptr, nullptr);
               if (var9 != nullptr) {
                  if (Rand.NextBool(3)) {
                     var9.setHeadlightsOn(true);
                     var9.setLightbarLightsMode(2);
    VehiclePart var10 = var9.getBattery();
                     if (var10 != nullptr) {
                        var10.setLastUpdated(0.0F);
                     }
                  }

                  this.addZombiesOnVehicle(Rand.Next(2, 4), "police", nullptr, var9);
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
