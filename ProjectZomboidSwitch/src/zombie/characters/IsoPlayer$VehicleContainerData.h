#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer/VehicleContainer.h"
#include <algorithm>

namespace zombie {
namespace characters {


class IsoPlayer {
public:
   std::vector<VehicleContainer> tempContainers = std::make_unique<std::vector<>>();
   std::vector<VehicleContainer> containers = std::make_unique<std::vector<>>();
   std::stack<VehicleContainer> freeContainers = std::make_unique<std::stack<>>();

   private IsoPlayer$VehicleContainerData() {
   }
}
} // namespace characters
} // namespace zombie
