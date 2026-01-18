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

class RZSForestCamp : public RandomizedZoneStoryBase {
public:
public
  RZSForestCamp() {
    this.name = "Basic Forest Camp";
    this.chance = 10;
    this.minZoneHeight = 6;
    this.minZoneWidth = 6;
    this.zoneType.add(RandomizedZoneStoryBase.ZoneType.Forest.toString());
  }

public
  static ArrayList<String> getForestClutter() {
    std::vector arrayList = new ArrayList();
    arrayList.add("Base.Crisps");
    arrayList.add("Base.Crisps2");
    arrayList.add("Base.Crisps3");
    arrayList.add("Base.Crisps4");
    arrayList.add("Base.Pop");
    arrayList.add("Base.Pop2");
    arrayList.add("Base.WaterBottleFull");
    arrayList.add("Base.CannedSardines");
    arrayList.add("Base.CannedChili");
    arrayList.add("Base.CannedBolognese");
    arrayList.add("Base.CannedCornedBeef");
    arrayList.add("Base.TinnedSoup");
    arrayList.add("Base.TinnedBeans");
    arrayList.add("Base.TunaTin");
    arrayList.add("Base.WhiskeyFull");
    arrayList.add("Base.BeerBottle");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    return arrayList;
  }

public
  static ArrayList<String> getCoolerClutter() {
    std::vector arrayList = new ArrayList();
    arrayList.add("Base.Pop");
    arrayList.add("Base.Pop2");
    arrayList.add("Base.BeefJerky");
    arrayList.add("Base.Ham");
    arrayList.add("Base.WaterBottleFull");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    arrayList.add("Base.BeerCan");
    return arrayList;
  }

public
  static ArrayList<String> getFireClutter() {
    std::vector arrayList = new ArrayList();
    arrayList.add("Base.WaterPotRice");
    arrayList.add("Base.WaterPot");
    arrayList.add("Base.Pot");
    arrayList.add("Base.WaterSaucepanRice");
    arrayList.add("Base.WaterSaucepanPasta");
    arrayList.add("Base.PotOfStew");
    return arrayList;
  }

  void randomizeZoneStory(IsoMetaGrid.Zone zone) {
    int int0 = zone.pickedXForZoneStory;
    int int1 = zone.pickedYForZoneStory;
    std::vector arrayList0 = getForestClutter();
    std::vector arrayList1 = getCoolerClutter();
    std::vector arrayList2 = getFireClutter();
    this.cleanAreaForStory(this, zone);
    this.addTileObject(int0, int1, zone.z, "camping_01_6");
    this.addItemOnGround(this.getSq(int0, int1, zone.z),
                         (String)arrayList2.get(Rand.Next(arrayList2.size())));
    int int2 = Rand.Next(-1, 2);
    int int3 = Rand.Next(-1, 2);
    this.addTentWestEast(int0 + int2 - 2, int1 + int3, zone.z);
    if (Rand.Next(100) < 70) {
      this.addTentNorthSouth(int0 + int2, int1 + int3 - 2, zone.z);
    }

    if (Rand.Next(100) < 30) {
      this.addTentNorthSouth(int0 + int2 + 1, int1 + int3 - 2, zone.z);
    }

    this.addTileObject(int0 + 2, int1, zone.z,
                       "furniture_seating_outdoor_01_19");
    InventoryContainer inventoryContainer =
        (InventoryContainer)InventoryItemFactory.CreateItem("Base.Cooler");
    int int4 = Rand.Next(2, 5);

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

    this.addZombiesOnSquare(Rand.Next(1, 3), "Camper", nullptr,
                            this.getRandomFreeSquare(this, zone));
  }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
