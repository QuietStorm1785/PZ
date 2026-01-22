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


class RVSCarCrash : public RandomizedVehicleStoryBase {
public:
    public RVSCarCrash() {
      this.name = "Basic Car Crash";
      this.minZoneWidth = 5;
      this.minZoneHeight = 7;
      this.setChance(25);
   }

    void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
   }

    bool initVehicleStorySpawner(Zone var1, IsoChunk var2, bool var3) {
    VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
    float var5 = (float) (Math.PI / 6);
      if (var3) {
         var5 = 0.0F;
      }

    Vector2 var6 = IsoDirections.N.ToVector();
      var6.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle1", 0.0F, 1.0F, var6.getDirection(), 2.0F, 5.0F);
    bool var7 = Rand.NextBool(2);
      var6 = var7 ? IsoDirections.E.ToVector() : IsoDirections.W.ToVector();
      var6.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle2", 0.0F, -2.5F, var6.getDirection(), 2.0F, 5.0F);
      var4.setParameter("zone", var1);
      var4.setParameter("smashed", Rand.NextBool(3));
      var4.setParameter("east", var7);
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = var2.z;
    Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
    bool var6 = var1.getParameterBoolean("smashed");
    bool var7 = var1.getParameterBoolean("east");
    std::string var8 = var2.id;
         switch (var8) {
            case "vehicle1":
            case "vehicle2":
    BaseVehicle var10 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, "bad", nullptr, nullptr, nullptr);
               if (var10 != nullptr) {
                  if (var6) {
    std::string var11 = "Front";
                     if ("vehicle2" == var2.id)) {
                        var11 = var7 ? "Right" : "Left";
                     }

                     var10 = var10.setSmashed(var11);
                     var10.setBloodIntensity(var11, 1.0F);
                  }

                  if ("vehicle1" == var2.id) && Rand.Next(10) < 4) {
                     this.addZombiesOnVehicle(Rand.Next(2, 5), nullptr, nullptr, var10);
                  }
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
