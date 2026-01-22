#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

enum class Helicopter {
   Arriving,
   Hovering,
   Searching,
   Leaving;
}
} // namespace iso
} // namespace zombie
