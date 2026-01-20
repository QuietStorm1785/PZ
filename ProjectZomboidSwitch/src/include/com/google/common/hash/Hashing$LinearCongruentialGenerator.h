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
    long state;

   public Hashing$LinearCongruentialGenerator(long seed) {
      this.state = seed;
   }

    double nextDouble() {
      this.state = 2862933555777941757L * this.state + 1L;
      return ((int)(this.state >>> 33) + 1) / 2.1474836E9F;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
