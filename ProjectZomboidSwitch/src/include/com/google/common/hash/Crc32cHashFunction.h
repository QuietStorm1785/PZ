#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/Crc32cHashFunction/Crc32cHasher.h"

namespace com {
namespace google {
namespace common {
namespace hash {


class Crc32cHashFunction : public AbstractStreamingHashFunction {
public:
    int bits() {
    return 32;
   }

    Hasher newHasher() {
      return std::make_unique<Crc32cHasher>();
   }

    std::string toString() {
      return "Hashing.crc32c()";
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
