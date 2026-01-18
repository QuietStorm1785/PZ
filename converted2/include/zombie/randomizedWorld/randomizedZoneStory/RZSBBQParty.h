#pragma once
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
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

class RZSBBQParty : public RandomizedZoneStoryBase {
public:
public
  RZSBBQParty() {
    this.name = "BBQ Party";
    this.chance = 10;
    this.minZoneHeight = 12;
    this.minZoneWidth = 12;
    this.zoneType.add(RandomizedZoneStoryBase.ZoneType.Beach.toString());
    this.zoneType.add(RandomizedZoneStoryBase.ZoneType.Lake.toString());
  }

public
  static ArrayList<String> getBeachClutter() {
    std::vector arrayList = new ArrayList();
    arrayList.add("Base.Crisps");
    arrayList.add("Base.Crisps3");
    arrayList.add("Base.MuttonChop");
    arrayList.add("Base.PorkChop");
    arrayList.add("Base.Steak");
    arrayList.add("Base.Pop");
    arrayList.add("Base.BeerBottle");
    arrayList.add("Base.BeerBottle");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    return arrayList;
  }

  void randomizeZoneStory(IsoMetaGrid.Zone zone) {
    int int0 = zone.pickedXForZoneStory;
    int int1 = zone.pickedYForZoneStory;
    std::vector arrayList0 = getBeachClutter();
    std::vector arrayList1 = RZSForestCamp.getCoolerClutter();
    IsoGridSquare square = this.getSq(int0, int1, zone.z);
    IsoBarbecue barbecue = new IsoBarbecue(
        IsoWorld.instance.getCell(), square,
        IsoSpriteManager.instance.NamedMap.get("appliances_cooking_01_35"));
    square.getObjects().add(barbecue);
    int int2 = Rand.Next(1, 4);

    for (int int3 = 0; int3 < int2; int3++) {
      this.addTileObject(this.getRandomFreeSquare(this, zone),
                         "furniture_seating_outdoor_01_" + Rand.Next(16, 20));
    }

    InventoryContainer inventoryContainer =
        (InventoryContainer)InventoryItemFactory.CreateItem("Base.Cooler");
    int int4 = Rand.Next(4, 8);

    for (int int5 = 0; int5 < int4; int5++) {
      inventoryContainer.getItemContainer().AddItem(
          (String)arrayList1.get(Rand.Next(arrayList1.size())));
    }

    this.addItemOnGround(this.getRandomFreeSquare(this, zone),
                         inventoryContainer);
    int4 = Rand.Next(3, 7);

    for (int int6 = 0; int6 < int4; int6++) {
      this.addItemOnGround(
          this.getRandomFreeSquare(this, zone),
          (String)arrayList0.get(Rand.Next(arrayList0.size())));
    }

    int int7 = Rand.Next(3, 8);

    for (int int8 = 0; int8 < int7; int8++) {
      this.addZombiesOnSquare(1, "Tourist", nullptr,
                              this.getRandomFreeSquare(this, zone));
    }
  }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
