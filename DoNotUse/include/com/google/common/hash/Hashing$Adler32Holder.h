#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/Hashing/ChecksumType.h"

namespace com {
namespace google {
namespace common {
namespace hash {


class Hashing {
public:
    static const HashFunction ADLER_32 = Hashing.access$200(ChecksumType.ADLER_32, "Hashing.adler32()");

   private Hashing$Adler32Holder() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
