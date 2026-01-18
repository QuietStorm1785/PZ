#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/Vector2.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"
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
 * Police barricading a road, 2 police cars, some zombies police
 */
class RVSPoliceBlockade : public RandomizedVehicleStoryBase {
public:
public
  RVSPoliceBlockade() {
    this.name = "Police Blockade";
    this.minZoneWidth = 8;
    this.minZoneHeight = 8;
    this.setChance(3);
    this.setMaximumDays(30);
  }

  void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
    this.callVehicleStorySpawner(zone, chunk, 0.0F);
  }

  bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk,
                               bool debug) {
    VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
    vehicleStorySpawner.clear();
    float float0 = (float)(Math.PI / 18);
    if (debug) {
      float0 = 0.0F;
    }

    float float1 = 1.5F;
    float float2 = 1.0F;
    if (this.zoneWidth >= 10) {
      float1 = 2.5F;
      float2 = 0.0F;
    }

    IsoDirections directions =
        Rand.NextBool(2) ? IsoDirections.W : IsoDirections.E;
    Vector2 vector = directions.ToVector();
    vector.rotate(Rand.Next(-float0, float0));
    vehicleStorySpawner.addElement("vehicle1", -float1, float2,
                                   vector.getDirection(), 2.0F, 5.0F);
    vector = directions.RotLeft(4).ToVector();
    vector.rotate(Rand.Next(-float0, float0));
    vehicleStorySpawner.addElement("vehicle2", float1, -float2,
                                   vector.getDirection(), 2.0F, 5.0F);
    std::string string = "Base.CarLightsPolice";
    if (Rand.NextBool(3)) {
      string = "Base.PickUpVanLightsPolice";
    }

    vehicleStorySpawner.setParameter("zone", zone);
    vehicleStorySpawner.setParameter("script", string);
    return true;
  }

  void spawnElement(VehicleStorySpawner spawner,
                    VehicleStorySpawner.Element element) {
    IsoGridSquare square = element.square;
    if (square != nullptr) {
      float float0 = element.z;
      IsoMetaGrid.Zone zone =
          spawner.getParameter("zone", IsoMetaGrid.Zone.class);
      std::string string0 = spawner.getParameterString("script");
      std::string string1 = element.id;
      switch (string1) {
      case "vehicle1":
      case "vehicle2":
        BaseVehicle vehicle = this.addVehicle(
            zone, element.position.x, element.position.y, float0,
            element.direction, null, string0, null, null);
        if (vehicle != nullptr) {
          if (Rand.NextBool(3)) {
            vehicle.setHeadlightsOn(true);
            vehicle.setLightbarLightsMode(2);
            VehiclePart part = vehicle.getBattery();
            if (part != nullptr) {
              part.setLastUpdated(0.0F);
            }
          }

          this.addZombiesOnVehicle(Rand.Next(2, 4), "police", nullptr, vehicle);
        }
      }
    }
  }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
