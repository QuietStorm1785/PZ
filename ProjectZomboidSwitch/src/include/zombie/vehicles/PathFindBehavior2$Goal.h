#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

enum class PathFindBehavior2 {
   None,
   char,
   Location,
   Sound,
   VehicleAdjacent,
   VehicleArea,
   VehicleSeat;
}
} // namespace vehicles
} // namespace zombie
