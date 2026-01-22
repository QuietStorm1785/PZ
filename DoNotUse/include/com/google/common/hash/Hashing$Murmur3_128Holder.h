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
    static const HashFunction MURMUR3_128 = std::make_shared<Murmur3_128HashFunction>(0);
    static const HashFunction GOOD_FAST_HASH_FUNCTION_128 = Hashing.murmur3_128(Hashing.access$100());

   private Hashing$Murmur3_128Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
