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

class RVSBanditRoad : public RandomizedVehicleStoryBase {
public:
public
  RVSBanditRoad() {
    this.name = "Bandits on Road";
    this.minZoneWidth = 7;
    this.minZoneHeight = 9;
    this.setMinimumDays(30);
    this.setChance(3);
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
    vehicleStorySpawner.addElement("vehicle1", 0.0F, 2.0F,
                                   vector.getDirection(), 2.0F, 5.0F);
    bool boolean0 = Rand.NextBool(2);
    vector = boolean0 ? IsoDirections.E.ToVector() : IsoDirections.W.ToVector();
    vector.rotate(Rand.Next(-float0, float0));
    float float1 = 0.0F;
    float float2 = -1.5F;
    vehicleStorySpawner.addElement("vehicle2", float1, float2,
                                   vector.getDirection(), 2.0F, 5.0F);
    int int0 = Rand.Next(3, 6);

    for (int int1 = 0; int1 < int0; int1++) {
      float float3 = Rand.Next(float1 - 3.0F, float1 + 3.0F);
      float float4 = Rand.Next(float2 - 3.0F, float2 + 3.0F);
      vehicleStorySpawner.addElement("corpse", float3, float4,
                                     Rand.Next(0.0F, (float)(Math.PI * 2)),
                                     1.0F, 2.0F);
    }

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
      switch (string) {
      case "corpse":
        BaseVehicle vehicle2 =
            spawner.getParameter("vehicle1", BaseVehicle.class);
        if (vehicle2 != nullptr) {
          createRandomDeadBody(element.position.x, element.position.y,
                               element.z, element.direction, false, 6, 0,
                               nullptr);
          this.addTrailOfBlood(
              element.position.x, element.position.y, element.z,
              Vector2.getDirection(element.position.x - vehicle2.x,
                                   element.position.y - vehicle2.y),
              15);
        }
        break;
      case "vehicle1":
        BaseVehicle vehicle1 =
            this.addVehicle(zone, element.position.x, element.position.y,
                            float0, element.direction, "bad", null, null, null);
        if (vehicle1 != nullptr) {
          vehicle1 = vehicle1.setSmashed("Front");
          this.addZombiesOnVehicle(Rand.Next(3, 6), "Bandit", nullptr,
                                   vehicle1);
          spawner.setParameter("vehicle1", vehicle1);
        }
        break;
      case "vehicle2":
        BaseVehicle vehicle0 =
            this.addVehicle(zone, element.position.x, element.position.y,
                            float0, element.direction, "bad", null, null, null);
        if (vehicle0 != nullptr) {
          this.addZombiesOnVehicle(Rand.Next(3, 5), nullptr, nullptr, vehicle0);
          spawner.setParameter("vehicle2", vehicle0);
        }
      }
    }
  }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
