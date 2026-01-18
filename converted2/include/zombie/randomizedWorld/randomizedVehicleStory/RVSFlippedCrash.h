#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Flipped car with bodies & blood near it, can be burnt
 */
class RVSFlippedCrash : public RandomizedVehicleStoryBase {
public:
public
  RVSFlippedCrash() {
    this.name = "Flipped Crash";
    this.minZoneWidth = 8;
    this.minZoneHeight = 8;
    this.setChance(4);
  }

  void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
    this.callVehicleStorySpawner(zone, chunk, 0.0F);
  }

  bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk,
                               bool debug) {
    VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
    vehicleStorySpawner.clear();
    float float0 = (float)(Math.PI / 6);
    if (debug) {
      float0 = 0.0F;
    }

    Vector2 vector = IsoDirections.N.ToVector();
    vector.rotate(Rand.Next(-float0, float0));
    vehicleStorySpawner.addElement("vehicle1", 0.0F, 0.0F,
                                   vector.getDirection(), 2.0F, 5.0F);
    vehicleStorySpawner.setParameter("zone", zone);
    vehicleStorySpawner.setParameter("burnt", Rand.NextBool(5));
    return true;
  }

  void spawnElement(VehicleStorySpawner spawner,
                    VehicleStorySpawner.Element element) {
    IsoGridSquare square = element.square;
    if (square != nullptr) {
      float float0 = element.z;
      IsoMetaGrid.Zone zone =
          spawner.getParameter("zone", IsoMetaGrid.Zone.class);
      bool boolean0 = spawner.getParameterBoolean("burnt");
      std::string string0 = element.id;
      switch (string0) {
      case "vehicle1":
        BaseVehicle vehicle = this.addVehicleFlipped(
            zone, element.position.x, element.position.y, float0 + 0.25F,
            element.direction, boolean0 ? "normalburnt" : "bad", nullptr,
            nullptr, nullptr);
        if (vehicle != nullptr) {
          int int0 = Rand.Next(4);
          std::string string1 = null;
          switch (int0) {
          case 0:
            string1 = "Front";
            break;
          case 1:
            string1 = "Rear";
            break;
          case 2:
            string1 = "Left";
            break;
          case 3:
            string1 = "Right";
          }

          vehicle = vehicle.setSmashed(string1);
          vehicle.setBloodIntensity("Front", Rand.Next(0.3F, 1.0F));
          vehicle.setBloodIntensity("Rear", Rand.Next(0.3F, 1.0F));
          vehicle.setBloodIntensity("Left", Rand.Next(0.3F, 1.0F));
          vehicle.setBloodIntensity("Right", Rand.Next(0.3F, 1.0F));
          std::vector arrayList =
              this.addZombiesOnVehicle(Rand.Next(2, 4), null, null, vehicle);
          if (arrayList != nullptr) {
            for (int int1 = 0; int1 < arrayList.size(); int1++) {
              IsoZombie zombie0 = (IsoZombie)arrayList.get(int1);
              zombie0.upKillCount = false;
              this.addBloodSplat(zombie0.getSquare(), Rand.Next(10, 20));
              if (boolean0) {
                zombie0.setSkeleton(true);
                zombie0.getHumanVisual().setSkinTextureIndex(0);
              } else {
                zombie0.DoCorpseInventory();
                if (Rand.NextBool(10)) {
                  zombie0.setFakeDead(true);
                  zombie0.bCrawling = true;
                  zombie0.setCanWalk(false);
                  zombie0.setCrawlerType(1);
                }
              }

              new IsoDeadBody();
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
