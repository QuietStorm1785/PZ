#pragma once
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/Vector2.h"
#include "zombie/util/list/PZArrayUtil.h"
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
 * An utility vehicle (mccoys, fire dept, police, ranger, postal..) with
 * corresponding outfit zeds and sometimes tools
 */
class RVSUtilityVehicle : public RandomizedVehicleStoryBase {
public:
private
  ArrayList<String> tools = nullptr;
private
  ArrayList<String> carpenterTools = nullptr;
private
  RVSUtilityVehicle.Params params = new RVSUtilityVehicle.Params();

public
  RVSUtilityVehicle() {
    this.name = "Utility Vehicle";
    this.minZoneWidth = 8;
    this.minZoneHeight = 9;
    this.setChance(7);
    this.tools = std::make_unique<ArrayList<>>();
    this.tools.add("Base.PickAxe");
    this.tools.add("Base.Shovel");
    this.tools.add("Base.Shovel2");
    this.tools.add("Base.Hammer");
    this.tools.add("Base.LeadPipe");
    this.tools.add("Base.PipeWrench");
    this.tools.add("Base.Sledgehammer");
    this.tools.add("Base.Sledgehammer2");
    this.carpenterTools = std::make_unique<ArrayList<>>();
    this.carpenterTools.add("Base.Hammer");
    this.carpenterTools.add("Base.NailsBox");
    this.carpenterTools.add("Base.Plank");
    this.carpenterTools.add("Base.Plank");
    this.carpenterTools.add("Base.Plank");
    this.carpenterTools.add("Base.Screwdriver");
    this.carpenterTools.add("Base.Saw");
    this.carpenterTools.add("Base.Saw");
    this.carpenterTools.add("Base.Woodglue");
  }

  void randomizeVehicleStory(IsoMetaGrid.Zone zone, IsoChunk chunk) {
    this.callVehicleStorySpawner(zone, chunk, 0.0F);
  }

public
  void doUtilityVehicle(IsoMetaGrid.Zone zone, IsoChunk chunk, String zoneName,
                        String scriptName, String outfits, Integer femaleChance,
                        String vehicleDistrib, ArrayList<String> items,
                        int nbrOfItem, boolean addTrailer) {
    this.params.zoneName = zoneName;
    this.params.scriptName = scriptName;
    this.params.outfits = outfits;
    this.params.femaleChance = femaleChance;
    this.params.vehicleDistrib = vehicleDistrib;
    this.params.items = items;
    this.params.nbrOfItem = nbrOfItem;
    this.params.addTrailer = addTrailer;
  }

  bool initVehicleStorySpawner(IsoMetaGrid.Zone zone, IsoChunk chunk,
                               bool debug) {
    int int0 = Rand.Next(0, 7);
    switch (int0) {
    case 0:
      this.doUtilityVehicle(zone, chunk, nullptr, "Base.PickUpTruck",
                            "ConstructionWorker", 0, "ConstructionWorker",
                            this.tools, Rand.Next(0, 3), true);
      break;
    case 1:
      this.doUtilityVehicle(zone, chunk, "police", nullptr, "Police", nullptr,
                            nullptr, nullptr, 0, false);
      break;
    case 2:
      this.doUtilityVehicle(zone, chunk, "fire", nullptr, "Fireman", nullptr,
                            nullptr, nullptr, 0, false);
      break;
    case 3:
      this.doUtilityVehicle(zone, chunk, "ranger", nullptr, "Ranger", nullptr,
                            nullptr, nullptr, 0, true);
      break;
    case 4:
      this.doUtilityVehicle(zone, chunk, "mccoy", nullptr, "McCoys", 0,
                            "Carpenter", this.carpenterTools, Rand.Next(2, 6),
                            true);
      break;
    case 5:
      this.doUtilityVehicle(zone, chunk, "postal", nullptr, "Postal", nullptr,
                            nullptr, nullptr, 0, false);
      break;
    case 6:
      this.doUtilityVehicle(zone, chunk, "fossoil", nullptr, "Fossoil", nullptr,
                            nullptr, nullptr, 0, false);
    }

    VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
    vehicleStorySpawner.clear();
    Vector2 vector = IsoDirections.N.ToVector();
    float float0 = (float)(Math.PI / 6);
    if (debug) {
      float0 = 0.0F;
    }

    vector.rotate(Rand.Next(-float0, float0));
    float float1 = -2.0F;
    uint8_t byte0 = 5;
    vehicleStorySpawner.addElement("vehicle1", 0.0F, float1,
                                   vector.getDirection(), 2.0F, byte0);
    if (this.params.addTrailer && Rand.NextBool(7)) {
      uint8_t byte1 = 3;
      vehicleStorySpawner.addElement(
          "trailer", 0.0F, float1 + byte0 / 2.0F + 1.0F + byte1 / 2.0F,
          vector.getDirection(), 2.0F, byte1);
    }

    if (this.params.items != nullptr) {
      for (int int1 = 0; int1 < this.params.nbrOfItem; int1++) {
        vehicleStorySpawner.addElement("tool", Rand.Next(-3.5F, 3.5F),
                                       Rand.Next(-3.5F, 3.5F), 0.0F, 1.0F,
                                       1.0F);
      }
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
      BaseVehicle vehicle = spawner.getParameter("vehicle1", BaseVehicle.class);
      std::string string = element.id;
      switch (string) {
      case "tool":
        if (vehicle != nullptr) {
          float float1 = PZMath.max(element.position.x - square.x, 0.001F);
          float float2 = PZMath.max(element.position.y - square.y, 0.001F);
          float float3 = 0.0F;
          square.AddWorldInventoryItem(
              PZArrayUtil.pickRandom(this.params.items), float1, float2,
              float3);
        }
        break;
      case "trailer":
        if (vehicle != nullptr) {
          this.addTrailer(vehicle, zone, square.getChunk(),
                          this.params.zoneName, this.params.vehicleDistrib,
                          Rand.NextBool(1) ? "Base.Trailer"
                                           : "Base.TrailerCover");
        }
        break;
      case "vehicle1":
        vehicle = this.addVehicle(zone, element.position.x, element.position.y,
                                  float0, element.direction,
                                  this.params.zoneName, this.params.scriptName,
                                  nullptr, this.params.vehicleDistrib);
        if (vehicle != nullptr) {
          this.addZombiesOnVehicle(Rand.Next(2, 5), this.params.outfits,
                                   this.params.femaleChance, vehicle);
        }
      }
    }
  }

private
  static final class Params {
    std::string zoneName;
    std::string scriptName;
    std::string outfits;
    int femaleChance;
    std::string vehicleDistrib;
    ArrayList<String> items;
    int nbrOfItem;
    bool addTrailer;
  }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
