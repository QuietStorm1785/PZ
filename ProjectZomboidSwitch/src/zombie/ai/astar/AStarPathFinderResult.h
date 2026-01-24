#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/astar/AStarPathFinder/PathFindProgress.h"

namespace zombie {
namespace ai {
namespace astar {


class AStarPathFinderResult {
public:
    PathFindProgress progress = PathFindProgress::notrunning;
    int maxSearchDistance = 120;
}
} // namespace astar
} // namespace ai
} // namespace zombie
