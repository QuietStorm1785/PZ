#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class PathFindBehavior2 {
public:
    int pathIndex;
    float dist;
    float x;
    float y;
}
} // namespace vehicles
} // namespace zombie
