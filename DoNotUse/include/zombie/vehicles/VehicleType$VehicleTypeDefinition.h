#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class VehicleType {
public:
    std::string vehicleType;
    int index = -1;
    float spawnChance = 0.0F;

   public VehicleType$VehicleTypeDefinition(std::string var1, int var2, float var3) {
      this.vehicleType = var1;
      this.index = var2;
      this.spawnChance = var3;
   }
}
} // namespace vehicles
} // namespace zombie
