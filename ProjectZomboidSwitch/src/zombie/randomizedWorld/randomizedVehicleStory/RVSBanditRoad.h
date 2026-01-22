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


class RVSBanditRoad : public RandomizedVehicleStoryBase {
public:
    public RVSBanditRoad() {
      this.name = "Bandits on Road";
      this.minZoneWidth = 7;
      this.minZoneHeight = 9;
      this.setMinimumDays(30);
      this.setChance(3);
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
      var4.addElement("vehicle1", 0.0F, 2.0F, var6.getDirection(), 2.0F, 5.0F);
    bool var7 = Rand.NextBool(2);
      var6 = var7 ? IsoDirections.E.ToVector() : IsoDirections.W.ToVector();
      var6.rotate(Rand.Next(-var5, var5));
    float var8 = 0.0F;
    float var9 = -1.5F;
      var4.addElement("vehicle2", var8, var9, var6.getDirection(), 2.0F, 5.0F);
    int var10 = Rand.Next(3, 6);

      for (int var11 = 0; var11 < var10; var11++) {
    float var12 = Rand.Next(var8 - 3.0F, var8 + 3.0F);
    float var13 = Rand.Next(var9 - 3.0F, var9 + 3.0F);
         var4.addElement("corpse", var12, var13, Rand.Next(0.0F, (float) (Math.PI * 2)), 1.0F, 2.0F);
      }

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
            case "corpse":
    BaseVehicle var11 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
               if (var11 != nullptr) {
                  createRandomDeadBody(var2.position.x, var2.position.y, var2.z, var2.direction, false, 6, 0, nullptr);
                  this.addTrailOfBlood(var2.position.x, var2.position.y, var2.z, Vector2.getDirection(var2.position.x - var11.x, var2.position.y - var11.y), 15);
               }
               break;
            case "vehicle1":
    BaseVehicle var9 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, "bad", nullptr, nullptr, nullptr);
               if (var9 != nullptr) {
                  var9 = var9.setSmashed("Front");
                  this.addZombiesOnVehicle(Rand.Next(3, 6), "Bandit", nullptr, var9);
                  var1.setParameter("vehicle1", var9);
               }
               break;
            case "vehicle2":
    BaseVehicle var8 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, "bad", nullptr, nullptr, nullptr);
               if (var8 != nullptr) {
                  this.addZombiesOnVehicle(Rand.Next(3, 5), nullptr, nullptr, var8);
                  var1.setParameter("vehicle2", var8);
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
