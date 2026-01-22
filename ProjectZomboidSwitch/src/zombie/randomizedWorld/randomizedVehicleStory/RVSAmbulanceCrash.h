#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoZombie.h"
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


class RVSAmbulanceCrash : public RandomizedVehicleStoryBase {
public:
    public RVSAmbulanceCrash() {
      this.name = "Ambulance Crash";
      this.minZoneWidth = 5;
      this.minZoneHeight = 7;
      this.setChance(5);
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
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = var2.z;
    Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
    std::string var6 = var2.id;
         switch (var6) {
            case "vehicle1":
    BaseVehicle var12 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, nullptr, "Base.VanAmbulance", nullptr, nullptr);
               if (var12 != nullptr) {
                  this.addZombiesOnVehicle(Rand.Next(1, 3), "AmbulanceDriver", nullptr, var12);
    std::vector var9 = this.addZombiesOnVehicle(Rand.Next(1, 3), "HospitalPatient", nullptr, var12);

                  for (int var10 = 0; var10 < var9.size(); var10++) {
                     for (int var11 = 0; var11 < 7; var11++) {
                        if (Rand.NextBool(2)) {
                           ((IsoZombie)var9.get(var10)).addVisualBandage(BodyPartType.getRandom(), true);
                        }
                     }
                  }
               }
               break;
            case "vehicle2":
    BaseVehicle var8 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, "bad", nullptr, nullptr, nullptr);
               if (var8 == nullptr) {
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
