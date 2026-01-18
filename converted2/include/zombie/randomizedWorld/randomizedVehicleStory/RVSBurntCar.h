#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/Vector2.h"
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
 * Just a burnt car with 0, 1 or 2 burnt corpses near it
 */
class RVSBurntCar : public RandomizedVehicleStoryBase {
public:
public
  RVSBurntCar() {
    this.name = "Burnt Car";
    this.minZoneWidth = 2;
    this.minZoneHeight = 5;
    this.setChance(13);
  }

  void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
    this.callVehicleStorySpawner(zone, chunk, 0.0F);
  }

  bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk,
                               bool debug) {
    VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
    vehicleStorySpawner.clear();
    Vector2 vector = IsoDirections.N.ToVector();
    float float0 = (float)(Math.PI / 6);
    if (debug) {
      float0 = 0.0F;
    }

    vector.rotate(Rand.Next(-float0, float0));
    vehicleStorySpawner.addElement("vehicle1", 0.0F, 0.0F,
                                   vector.getDirection(), 2.0F, 5.0F);
    vehicleStorySpawner.setParameter("zone", zone);
    return true;
  }

  void spawnElement(VehicleStorySpawner spawner,
                    VehicleStorySpawner.Element element) {
    IsoGridSquare square = element.square;
    if (square != nullptr) {
      float float0 = element.z;
      IsoMetaGrid.Zone zone =
          spawner.getParameter("zone", IsoMetaGrid.Zone.class);
      std::string string = element.id;
      uint8_t byte0 = -1;
      switch (string.hashCode()) {
      case 2014205573:
        if (string == "vehicle1")) {
                        byte0 = 0;
                    }
      default:
        switch (byte0) {
        case 0:
          BaseVehicle vehicle = this.addVehicle(
              zone, element.position.x, element.position.y, float0,
              element.direction, nullptr, "Base.CarNormal", nullptr, nullptr);
          if (vehicle != nullptr) {
            vehicle = vehicle.setSmashed("right");
          }
        }
      }
    }
  }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
