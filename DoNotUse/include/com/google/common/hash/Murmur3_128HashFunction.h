#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/Murmur3_128HashFunction/Murmur3_128Hasher.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Murmur3_128HashFunction : public AbstractStreamingHashFunction {
public:
    const int seed;
    static const long serialVersionUID = 0L;

   Murmur3_128HashFunction(int seed) {
      this.seed = seed;
   }

    int bits() {
    return 128;
   }

    Hasher newHasher() {
      return std::make_shared<Murmur3_128Hasher>(this.seed);
   }

    std::string toString() {
      return "Hashing.murmur3_128(" + this.seed + ")";
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Murmur3_128HashFunction*>(object) != nullptr) {
    Murmur3_128HashFunction other = (Murmur3_128HashFunction)object;
         return this.seed == other.seed;
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.getClass().hashCode() ^ this.seed;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
