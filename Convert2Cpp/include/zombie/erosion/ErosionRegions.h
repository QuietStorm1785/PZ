#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionRegions/Region.h"
#include "zombie/erosion/categories/ErosionCategory.h"
#include "zombie/erosion/categories/Flowerbed.h"
#include "zombie/erosion/categories/NatureBush.h"
#include "zombie/erosion/categories/NatureGeneric.h"
#include "zombie/erosion/categories/NaturePlants.h"
#include "zombie/erosion/categories/NatureTrees.h"
#include "zombie/erosion/categories/StreetCracks.h"
#include "zombie/erosion/categories/WallCracks.h"
#include "zombie/erosion/categories/WallVines.h"

namespace zombie {
namespace erosion {


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
   public static final ArrayList<Region> regions = std::make_unique<ArrayList<>>();

    static void addRegion(Region var0) {
      var0.ID = regions.size();
      regions.add(var0);
   }

    static ErosionCategory getCategory(int var0, int var1) {
      return (ErosionCategory)regions.get(var0).categories.get(var1);
   }

    static void init() {
      regions.clear();
      addRegion(
    new Region();
            .addCategory(0, std::make_unique<NatureTrees>())
            .addCategory(1, std::make_unique<NatureBush>())
            .addCategory(2, std::make_unique<NaturePlants>())
            .addCategory(3, std::make_unique<NatureGeneric>())
      );
      addRegion(new Region(1, "blends_street", true, true, false).addCategory(0, std::make_unique<StreetCracks>()));
      addRegion(new Region(2, nullptr, false, false, true).addCategory(0, std::make_unique<WallVines>()).addCategory(1, std::make_unique<WallCracks>()));
      addRegion(new Region(3, nullptr, true, true, false).addCategory(0, std::make_unique<Flowerbed>()));

      for (int var0 = 0; var0 < regions.size(); var0++) {
         regions.get(var0).init();
      }
   }

    static void Reset() {
      for (int var0 = 0; var0 < regions.size(); var0++) {
         regions.get(var0).Reset();
      }

      regions.clear();
   }
}
} // namespace erosion
} // namespace zombie
