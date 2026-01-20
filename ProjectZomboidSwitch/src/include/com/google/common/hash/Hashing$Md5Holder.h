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
    static const HashFunction MD5 = std::make_shared<MessageDigestHashFunction>("MD5", "Hashing.md5()");

   private Hashing$Md5Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
