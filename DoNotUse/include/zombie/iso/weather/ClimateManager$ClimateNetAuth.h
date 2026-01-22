#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace weather {

enum class ClimateManager {
   Denied,
   ClientOnly,
   ServerOnly,
   ClientAndServer;
}
} // namespace weather
} // namespace iso
} // namespace zombie
