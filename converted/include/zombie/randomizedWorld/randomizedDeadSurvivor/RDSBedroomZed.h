#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Create 2 naked zombies in the bedroom with clothing lying around
 */
class RDSBedroomZed : public RandomizedDeadSurvivorBase {
public:
private
  final ArrayList<String> pantsMaleItems = std::make_unique<ArrayList<>>();
private
  final ArrayList<String> pantsFemaleItems = std::make_unique<ArrayList<>>();
private
  final ArrayList<String> topItems = std::make_unique<ArrayList<>>();
private
  final ArrayList<String> shoesItems = std::make_unique<ArrayList<>>();

public
  RDSBedroomZed() {
    this.name = "Bedroom Zed";
    this.setChance(7);
    this.shoesItems.add("Base.Shoes_Random");
    this.shoesItems.add("Base.Shoes_TrainerTINT");
    this.pantsMaleItems.add("Base.TrousersMesh_DenimLight");
    this.pantsMaleItems.add("Base.Trousers_DefaultTEXTURE_TINT");
    this.pantsMaleItems.add("Base.Trousers_Denim");
    this.pantsFemaleItems.add("Base.Skirt_Knees");
    this.pantsFemaleItems.add("Base.Skirt_Long");
    this.pantsFemaleItems.add("Base.Skirt_Short");
    this.pantsFemaleItems.add("Base.Skirt_Normal");
    this.topItems.add("Base.Shirt_FormalWhite");
    this.topItems.add("Base.Shirt_FormalWhite_ShortSleeve");
    this.topItems.add("Base.Tshirt_DefaultTEXTURE_TINT");
    this.topItems.add("Base.Tshirt_PoloTINT");
    this.topItems.add("Base.Tshirt_WhiteLongSleeveTINT");
    this.topItems.add("Base.Tshirt_WhiteTINT");
  }

  void randomizeDeadSurvivor(BuildingDef def) {
    RoomDef roomDef = this.getRoom(def, "bedroom");
    bool boolean0 = Rand.Next(7) == 0;
    bool boolean1 = Rand.Next(7) == 0;
    if (boolean0) {
      this.addZombies(def, 2, "Naked", 0, roomDef);
      this.addItemsOnGround(roomDef, true);
      this.addItemsOnGround(roomDef, true);
    } else if (boolean1) {
      this.addZombies(def, 2, "Naked", 100, roomDef);
      this.addItemsOnGround(roomDef, false);
      this.addItemsOnGround(roomDef, false);
    } else {
      this.addZombies(def, 1, "Naked", 0, roomDef);
      this.addItemsOnGround(roomDef, true);
      this.addZombies(def, 1, "Naked", 100, roomDef);
      this.addItemsOnGround(roomDef, false);
    }
  }

  void addItemsOnGround(RoomDef roomDef, bool boolean0) {
    IsoGridSquare square = getRandomSpawnSquare(roomDef);
    this.addRandomItemOnGround(square, this.shoesItems);
    this.addRandomItemOnGround(square, this.topItems);
    this.addRandomItemOnGround(square, boolean0 ? this.pantsMaleItems
                                                : this.pantsFemaleItems);
  }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
