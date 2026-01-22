#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace objects {

enum class IsoWindowFrame {
   INVALID,
   NORTH,
   WEST;

    bool isValid() {
      return this != INVALID;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
