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
    static const HashFunction MURMUR3_32 = std::make_shared<Murmur3_32HashFunction>(0);
    static const HashFunction GOOD_FAST_HASH_FUNCTION_32 = Hashing.murmur3_32(Hashing.access$100());

   private Hashing$Murmur3_32Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
