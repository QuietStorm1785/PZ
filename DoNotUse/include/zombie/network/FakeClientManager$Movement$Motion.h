#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

enum class FakeClientManager {
   Aim,
   Sneak,
   Walk,
   SneakRun,
   Run,
   Sprint,
   Pedestrian,
   Vehicle;
}
} // namespace network
} // namespace zombie
