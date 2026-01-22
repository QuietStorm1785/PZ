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
    float steering;
    float rotation;
    float skidInfo;
    float suspensionLength;
}
} // namespace vehicles
} // namespace zombie
