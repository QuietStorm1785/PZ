#pragma once
#include "zombie/erosion/categories/ErosionCategory.h"
#include "zombie/erosion/categories/Flowerbed.h"
#include "zombie/erosion/categories/NatureBush.h"
#include "zombie/erosion/categories/NatureGeneric.h"
#include "zombie/erosion/categories/NaturePlants.h"
#include "zombie/erosion/categories/NatureTrees.h"
#include "zombie/erosion/categories/StreetCracks.h"
#include "zombie/erosion/categories/WallCracks.h"
#include "zombie/erosion/categories/WallVines.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace erosion {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ErosionRegions {
public:
 static const int REGION_NATURE = 0;
 static const int CATEGORY_TREES = 0;
 static const int CATEGORY_BUSH = 1;
 static const int CATEGORY_PLANTS = 2;
 static const int CATEGORY_GENERIC = 3;
 static const int REGION_STREET = 1;
 static const int CATEGORY_STREET_CRACKS = 0;
 static const int REGION_WALL = 2;
 static const int CATEGORY_WALL_VINES = 0;
 static const int CATEGORY_WALL_CRACKS = 1;
 static const int REGION_FLOWERBED = 3;
 static const int CATEGORY_FLOWERBED = 0;
public
 static ArrayList<ErosionRegions.Region> regions =
 std::make_unique<ArrayList<>>();

 static void addRegion(ErosionRegions.Region region) {
 region.ID = regions.size();
 regions.add(region);
 }

 static ErosionCategory getCategory(int int1, int int0) {
 return regions.get(int1).categories.get(int0);
 }

 static void init() {
 regions.clear();
 addRegion(
 new ErosionRegions.Region(0, "blends_natural_01", true, true, false)
 .addCategory(0, std::make_unique<NatureTrees>())
 .addCategory(1, std::make_unique<NatureBush>())
 .addCategory(2, std::make_unique<NaturePlants>())
 .addCategory(3, std::make_unique<NatureGeneric>()));
 addRegion(new ErosionRegions.Region(1, "blends_street", true, true, false)
 .addCategory(0, std::make_unique<StreetCracks>()));
 addRegion(new ErosionRegions.Region(2, nullptr, false, false, true)
 .addCategory(0, std::make_unique<WallVines>())
 .addCategory(1, std::make_unique<WallCracks>()));
 addRegion(new ErosionRegions.Region(3, nullptr, true, true, false)
 .addCategory(0, std::make_unique<Flowerbed>()));

 for (int int0 = 0; int0 < regions.size(); int0++) {
 regions.get(int0).init();
 }
 }

 static void Reset() {
 for (int int0 = 0; int0 < regions.size(); int0++) {
 regions.get(int0).Reset();
 }

 regions.clear();
 }

public
 static class Region {
 int ID;
 std::string tileNameMatch;
 bool checkExterior;
 bool isExterior;
 bool hasWall;
 public
 ArrayList<ErosionCategory> categories =
 std::make_unique<ArrayList<>>();

 public
 Region(int int0, const std::string &string, bool boolean0, bool boolean1,
 bool boolean2) {
 this->ID = int0;
 this->tileNameMatch = string;
 this->checkExterior = boolean0;
 this->isExterior = boolean1;
 this->hasWall = boolean2;
 }

 public
 ErosionRegions.Region addCategory(int int0,
 ErosionCategory erosionCategory) {
 erosionCategory.ID = int0;
 erosionCategory.region = this;
 this->categories.add(erosionCategory);
 return this;
 }

 void init() {
 for (int int0 = 0; int0 < this->categories.size(); int0++) {
 this->categories.get(int0).init();
 }
 }

 void Reset() { this->categories.clear(); }
 }
}
} // namespace erosion
} // namespace zombie
