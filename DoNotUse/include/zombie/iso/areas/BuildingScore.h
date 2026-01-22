#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace areas {

class BuildingScore {
public:
    float weapons;
    float food;
    float wood;
    float defense;
    IsoBuilding building;
    int size;
    int safety;

    public BuildingScore(IsoBuilding var1) {
      this.building = var1;
   }
}
} // namespace areas
} // namespace iso
} // namespace zombie
