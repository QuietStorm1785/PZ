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
    static const HashFunction FARMHASH_FINGERPRINT_64 = std::make_shared<FarmHashFingerprint64>();

   private Hashing$FarmHashFingerprint64Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
