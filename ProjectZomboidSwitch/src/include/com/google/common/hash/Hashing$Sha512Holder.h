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
    static const HashFunction SHA_512 = std::make_shared<MessageDigestHashFunction>("SHA-512", "Hashing.sha512()");

   private Hashing$Sha512Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
