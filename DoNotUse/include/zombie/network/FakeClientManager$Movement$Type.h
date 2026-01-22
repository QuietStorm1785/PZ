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
   Stay,
   Line,
   Circle,
   AIAttackZombies,
   AIRunAwayFromZombies,
   AIRunToAnotherPlayers,
   AINormal;
}
} // namespace network
} // namespace zombie
