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
    static const HashFunction SHA_384 = std::make_shared<MessageDigestHashFunction>("SHA-384", "Hashing.sha384()");

   private Hashing$Sha384Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
