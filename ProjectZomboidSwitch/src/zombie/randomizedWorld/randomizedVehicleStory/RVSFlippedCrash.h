#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/Element.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class RVSFlippedCrash : public RandomizedVehicleStoryBase {
public:
    public RVSFlippedCrash() {
      this.name = "Flipped Crash";
      this.minZoneWidth = 8;
      this.minZoneHeight = 8;
      this.setChance(4);
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
      var4.addElement("vehicle1", 0.0F, 0.0F, var6.getDirection(), 2.0F, 5.0F);
      var4.setParameter("zone", var1);
      var4.setParameter("burnt", Rand.NextBool(5));
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = var2.z;
    Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
    bool var6 = var1.getParameterBoolean("burnt");
    std::string var7 = var2.id;
         switch (var7) {
            case "vehicle1":
               BaseVehicle var9 = this.addVehicleFlipped(
                  var5, var2.position.x, var2.position.y, var4 + 0.25F, var2.direction, var6 ? "normalburnt" : "bad", nullptr, nullptr, nullptr
               );
               if (var9 != nullptr) {
    int var10 = Rand.Next(4);
    std::string var11 = nullptr;
                  switch (var10) {
                     case 0:
                        var11 = "Front";
                        break;
                     case 1:
                        var11 = "Rear";
                        break;
                     case 2:
                        var11 = "Left";
                        break;
                     case 3:
                        var11 = "Right";
                  }

                  var9 = var9.setSmashed(var11);
                  var9.setBloodIntensity("Front", Rand.Next(0.3F, 1.0F));
                  var9.setBloodIntensity("Rear", Rand.Next(0.3F, 1.0F));
                  var9.setBloodIntensity("Left", Rand.Next(0.3F, 1.0F));
                  var9.setBloodIntensity("Right", Rand.Next(0.3F, 1.0F));
    std::vector var12 = this.addZombiesOnVehicle(Rand.Next(2, 4), nullptr, nullptr, var9);
                  if (var12 != nullptr) {
                     for (int var13 = 0; var13 < var12.size(); var13++) {
    IsoZombie var14 = (IsoZombie)var12.get(var13);
                        var14.upKillCount = false;
                        this.addBloodSplat(var14.getSquare(), Rand.Next(10, 20));
                        if (var6) {
                           var14.setSkeleton(true);
                           var14.getHumanVisual().setSkinTextureIndex(0);
                        } else {
                           var14.DoCorpseInventory();
                           if (Rand.NextBool(10)) {
                              var14.setFakeDead(true);
                              var14.bCrawling = true;
                              var14.setCanWalk(false);
                              var14.setCrawlerType(1);
                           }
                        }

    std::make_shared<IsoDeadBody>();
                     }
                  }
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
