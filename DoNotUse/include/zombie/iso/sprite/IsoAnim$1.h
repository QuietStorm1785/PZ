#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace sprite {

class IsoAnim {
public:
    std::stringstream initialValue() {
      return std::make_unique<std::stringstream>();
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
