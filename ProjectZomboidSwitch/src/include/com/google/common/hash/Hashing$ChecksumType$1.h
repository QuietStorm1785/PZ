#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace hash {


enum class Hashing {
   Hashing$ChecksumType$1(int x0) {
   }

    Checksum get() {
      return std::make_unique<CRC32>();
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
