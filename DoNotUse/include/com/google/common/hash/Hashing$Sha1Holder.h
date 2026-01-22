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
    static const HashFunction SHA_1 = std::make_shared<MessageDigestHashFunction>("SHA-1", "Hashing.sha1()");

   private Hashing$Sha1Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
