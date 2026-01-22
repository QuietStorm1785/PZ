#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class BaseVehicle {
public:
    float minX;
    float maxX;
    float minY;
    float maxY;
}
} // namespace vehicles
} // namespace zombie
