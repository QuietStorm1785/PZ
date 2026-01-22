#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace physics {

enum class CarController {
   NoControl,
   Braking,
   Forward,
   Reverse;
}
} // namespace physics
} // namespace core
} // namespace zombie
