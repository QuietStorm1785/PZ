#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/SpawnRegions/Point.h"

namespace zombie {
namespace network {


class SpawnRegions {
public:
    std::string name;
   public std::vector<Point> points;
}
} // namespace network
} // namespace zombie
