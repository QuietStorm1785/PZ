#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

enum class NetworkTeleport {
   none,
   disappearing,
   teleportation,
   materialization;
}
} // namespace characters
} // namespace zombie
