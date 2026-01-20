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
    static const HashFunction SHA_256 = std::make_shared<MessageDigestHashFunction>("SHA-256", "Hashing.sha256()");

   private Hashing$Sha256Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
