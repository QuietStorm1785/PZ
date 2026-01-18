#pragma once
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/iso/IsoMetaGrid.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RZSFishingTrip : public RandomizedZoneStoryBase {
public:
public
  RZSFishingTrip() {
    this.name = "Fishing Trip";
    this.chance = 10;
    this.minZoneHeight = 8;
    this.minZoneWidth = 8;
    this.zoneType.add(RandomizedZoneStoryBase.ZoneType.Beach.toString());
    this.zoneType.add(RandomizedZoneStoryBase.ZoneType.Lake.toString());
  }

public
  static ArrayList<String> getFishes() {
    std::vector arrayList = new ArrayList();
    arrayList.add("Base.Catfish");
    arrayList.add("Base.Bass");
    arrayList.add("Base.Perch");
    arrayList.add("Base.Crappie");
    arrayList.add("Base.Panfish");
    arrayList.add("Base.Pike");
    arrayList.add("Base.Trout");
    arrayList.add("Base.BaitFish");
    return arrayList;
  }

public
  static ArrayList<String> getFishingTools() {
    std::vector arrayList = new ArrayList();
    arrayList.add("Base.FishingTackle");
    arrayList.add("Base.FishingTackle");
    arrayList.add("Base.FishingTackle2");
    arrayList.add("Base.FishingTackle2");
    arrayList.add("Base.FishingLine");
    arrayList.add("Base.FishingLine");
    arrayList.add("Base.FishingNet");
    arrayList.add("Base.Worm");
    arrayList.add("Base.Worm");
    arrayList.add("Base.Worm");
    arrayList.add("Base.Worm");
    return arrayList;
  }

  void randomizeZoneStory(IsoMetaGrid.Zone zone) {
    std::vector arrayList0 = getFishes();
    std::vector arrayList1 = getFishingTools();
    this.cleanAreaForStory(this, zone);
    this.addVehicle(zone, this.getSq(zone.x, zone.y, zone.z), nullptr, nullptr,
                    "Base.PickUpTruck", nullptr, nullptr, "Fisherman");
    int int0 = Rand.Next(1, 3);

    for (int int1 = 0; int1 < int0; int1++) {
      this.addTileObject(this.getRandomFreeSquare(this, zone),
                         "furniture_seating_outdoor_01_" + Rand.Next(16, 20));
    }

    InventoryContainer inventoryContainer0 =
        (InventoryContainer)InventoryItemFactory.CreateItem("Base.Cooler");
    int int2 = Rand.Next(4, 10);

    for (int int3 = 0; int3 < int2; int3++) {
      inventoryContainer0.getItemContainer().AddItem(
          (String)arrayList0.get(Rand.Next(arrayList0.size())));
    }

    this.addItemOnGround(this.getRandomFreeSquare(this, zone),
                         inventoryContainer0);
    InventoryContainer inventoryContainer1 =
        (InventoryContainer)InventoryItemFactory.CreateItem("Base.Toolbox");
    int2 = Rand.Next(3, 8);

    for (int int4 = 0; int4 < int2; int4++) {
      inventoryContainer1.getItemContainer().AddItem(
          (String)arrayList1.get(Rand.Next(arrayList1.size())));
    }

    this.addItemOnGround(this.getRandomFreeSquare(this, zone),
                         inventoryContainer1);
    int2 = Rand.Next(2, 5);

    for (int int5 = 0; int5 < int2; int5++) {
      this.addItemOnGround(this.getRandomFreeSquare(this, zone), "FishingRod");
    }

    this.addZombiesOnSquare(Rand.Next(2, 5), "Fisherman", 0,
                            this.getRandomFreeSquare(this, zone));
  }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
