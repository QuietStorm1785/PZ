#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace hash {

class Hashing {
public:
    static const HashFunction CRC_32_C = std::make_shared<Crc32cHashFunction>();

   private Hashing$Crc32cHolder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
