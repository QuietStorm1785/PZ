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
   Normal,
   Attack;
}
} // namespace network
} // namespace zombie
