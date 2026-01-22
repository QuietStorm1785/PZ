#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

enum class CollideWithObstacles {
   OnEdge,
   Inside,
   Outside;
}
} // namespace vehicles
} // namespace zombie
