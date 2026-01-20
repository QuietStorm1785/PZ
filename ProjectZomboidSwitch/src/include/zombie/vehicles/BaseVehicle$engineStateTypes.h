#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

enum class BaseVehicle {
   Idle,
   Starting,
   RetryingStarting,
   StartingSuccess,
   StartingFailed,
   Running,
   Stalling,
   ShutingDown,
   StartingFailedNoPower;

   public static const BaseVehicle$engineStateTypes[] Values = values();
}
} // namespace vehicles
} // namespace zombie
