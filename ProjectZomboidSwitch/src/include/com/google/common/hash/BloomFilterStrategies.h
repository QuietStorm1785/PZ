#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/BloomFilter/Strategy.h"

namespace com {
namespace google {
namespace common {
namespace hash {


enum class BloomFilterStrategies {
   MURMUR128_MITZ_32,
   MURMUR128_MITZ_64;

    private BloomFilterStrategies() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
