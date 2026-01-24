#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ai {
namespace astar {

enum class PathFindProgress {
   notrunning,
   failed,
   found,
   notyetfound
};
} // namespace astar
} // namespace ai
} // namespace zombie
