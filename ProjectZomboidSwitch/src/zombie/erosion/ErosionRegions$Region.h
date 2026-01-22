#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/categories/ErosionCategory.h"

namespace zombie {
namespace erosion {


class ErosionRegions {
public:
    int ID;
    std::string tileNameMatch;
    bool checkExterior;
    bool isExterior;
    bool hasWall;
   public const std::vector<ErosionCategory> categories = std::make_unique<std::vector<>>();

   public ErosionRegions$Region(int var1, std::string var2, boolean var3, boolean var4, boolean var5) {
      this.ID = var1;
      this.tileNameMatch = var2;
      this.checkExterior = var3;
      this.isExterior = var4;
      this.hasWall = var5;
   }

   public ErosionRegions$Region addCategory(int var1, ErosionCategory var2) {
      var2.ID = var1;
      var2.region = this;
      this.categories.push_back(var2);
    return this;
   }

    void init() {
      for (int var1 = 0; var1 < this.categories.size(); var1++) {
         this.categories.get(var1).init();
      }
   }

    void Reset() {
      this.categories.clear();
   }
}
} // namespace erosion
} // namespace zombie
