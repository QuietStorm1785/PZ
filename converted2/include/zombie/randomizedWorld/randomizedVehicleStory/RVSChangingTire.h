#pragma once
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/inventory/InventoryItem.h"
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
 * Good car with a couple changing its tire
 */
class RVSChangingTire : public RandomizedVehicleStoryBase {
public:
public
  RVSChangingTire() {
    this.name = "Changing Tire";
    this.minZoneWidth = 5;
    this.minZoneHeight = 5;
    this.setChance(3);
  }

  void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
    float float0 = (float)(Math.PI / 6);
    this.callVehicleStorySpawner(zone, chunk, Rand.Next(-float0, float0));
  }

  bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk,
                               bool debug) {
    VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
    vehicleStorySpawner.clear();
    bool boolean0 = Rand.NextBool(2);
    if (debug) {
      boolean0 = true;
    }

    int int0 = boolean0 ? 1 : -1;
    Vector2 vector = IsoDirections.N.ToVector();
    vehicleStorySpawner.addElement("vehicle1", int0 * -1.5F, 0.0F,
                                   vector.getDirection(), 2.0F, 5.0F);
    vehicleStorySpawner.addElement("tire1", int0 * 0.0F, 0.0F, 0.0F, 1.0F,
                                   1.0F);
    vehicleStorySpawner.addElement("tool1", int0 * 0.8F, -0.2F, 0.0F, 1.0F,
                                   1.0F);
    vehicleStorySpawner.addElement("tool2", int0 * 1.2F, 0.2F, 0.0F, 1.0F,
                                   1.0F);
    vehicleStorySpawner.addElement("tire2", int0 * 2.0F, 0.0F, 0.0F, 1.0F,
                                   1.0F);
    vehicleStorySpawner.setParameter("zone", zone);
    vehicleStorySpawner.setParameter("removeRightWheel", boolean0);
    return true;
  }

  void spawnElement(VehicleStorySpawner spawner,
                    VehicleStorySpawner.Element element) {
    IsoGridSquare square = element.square;
    if (square != nullptr) {
      float float0 = PZMath.max(element.position.x - square.x, 0.001F);
      float float1 = PZMath.max(element.position.y - square.y, 0.001F);
      float float2 = 0.0F;
      float float3 = element.z;
      IsoMetaGrid.Zone zone =
          spawner.getParameter("zone", IsoMetaGrid.Zone.class);
      bool boolean0 = spawner.getParameterBoolean("removeRightWheel");
      BaseVehicle vehicle = spawner.getParameter("vehicle1", BaseVehicle.class);
      std::string string = element.id;
      switch (string) {
      case "tire1":
        if (vehicle != nullptr) {
          InventoryItem item1 = square.AddWorldInventoryItem(
              "Base.ModernTire" + vehicle.getScript().getMechanicType(), float0,
              float1, float2);
          if (item1 != nullptr) {
            item1.setItemCapacity(item1.getMaxCapacity());
          }

          this.addBloodSplat(square, Rand.Next(10, 20));
        }
        break;
      case "tire2":
        if (vehicle != nullptr) {
          InventoryItem item0 = square.AddWorldInventoryItem(
              "Base.OldTire" + vehicle.getScript().getMechanicType(), float0,
              float1, float2);
          if (item0 != nullptr) {
            item0.setCondition(0);
          }
        }
        break;
      case "tool1":
        square.AddWorldInventoryItem("Base.LugWrench", float0, float1, float2);
        break;
      case "tool2":
        square.AddWorldInventoryItem("Base.Jack", float0, float1, float2);
        break;
      case "vehicle1":
        vehicle = this.addVehicle(zone, element.position.x, element.position.y,
                                  float3, element.direction, "good", nullptr,
                                  nullptr, nullptr);
        if (vehicle != nullptr) {
          vehicle.setGeneralPartCondition(0.7F, 40.0F);
          vehicle.setRust(0.0F);
          VehiclePart part =
              vehicle.getPartById(boolean0 ? "TireRearRight" : "TireRearLeft");
          vehicle.setTireRemoved(part.getWheelIndex(), true);
          part.setModelVisible("InflatedTirePlusWheel", false);
          part.setInventoryItem(nullptr);
          this.addZombiesOnVehicle(2, nullptr, nullptr, vehicle);
          spawner.setParameter("vehicle1", vehicle);
        }
      }
    }
  }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
