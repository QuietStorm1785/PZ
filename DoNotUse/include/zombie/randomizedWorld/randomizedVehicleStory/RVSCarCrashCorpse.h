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


class RVSCarCrashCorpse : public RandomizedVehicleStoryBase {
public:
    public RVSCarCrashCorpse() {
      this.name = "Basic Car Crash Corpse";
      this.minZoneWidth = 6;
      this.minZoneHeight = 11;
      this.setChance(10);
   }

    void randomizeVehicleStory(Zone var1, IsoChunk var2) {
    float var3 = (float) (Math.PI / 6);
      this.callVehicleStorySpawner(var1, var2, Rand.Next(-var3, var3));
   }

    bool initVehicleStorySpawner(Zone var1, IsoChunk var2, bool var3) {
    VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
    Vector2 var5 = IsoDirections.N.ToVector();
    float var6 = 2.5F;
      var4.addElement("vehicle1", 0.0F, var6, var5.getDirection(), 2.0F, 5.0F);
      var4.addElement("corpse", 0.0F, var6 - (var3 ? 7 : Rand.Next(4, 7)), var5.getDirection() + (float) Math.PI, 1.0F, 2.0F);
      var4.setParameter("zone", var1);
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = var2.z;
    Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
    BaseVehicle var6 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
    std::string var7 = var2.id;
         switch (var7) {
            case "corpse":
               if (var6 != nullptr) {
                  createRandomDeadBody(var2.position.x, var2.position.y, var2.z, var2.direction, false, 35, 30, nullptr);
                  this.addTrailOfBlood(var2.position.x, var2.position.y, var2.z, var2.direction, 15);
               }
               break;
            case "vehicle1":
               var6 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, "bad", nullptr, nullptr, nullptr);
               if (var6 != nullptr) {
                  var6 = var6.setSmashed("Front");
                  var6.setBloodIntensity("Front", 1.0F);
                  var1.setParameter("vehicle1", var6);
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
