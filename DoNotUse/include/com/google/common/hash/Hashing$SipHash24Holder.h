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
    static const HashFunction SIP_HASH_24 = std::make_shared<SipHashFunction>(2, 4, 506097522914230528L, 1084818905618843912L);

   private Hashing$SipHash24Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
