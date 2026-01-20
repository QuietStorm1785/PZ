#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace stash {

class StashBuilding {
public:
    int buildingX;
    int buildingY;
    std::string stashName;

    public StashBuilding(const std::string& var1, int var2, int var3) {
      this.stashName = var1;
      this.buildingX = var2;
      this.buildingY = var3;
   }

    std::string getName() {
      return this.stashName;
   }
}
} // namespace stash
} // namespace core
} // namespace zombie
