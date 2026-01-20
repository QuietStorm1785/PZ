#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

enum class LoginQueue {
   ConnectionImmediate,
   PlaceInQueue;
}
} // namespace network
} // namespace zombie
