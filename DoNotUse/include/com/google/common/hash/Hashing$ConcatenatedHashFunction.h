#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace hash {


class Hashing {
public:
    const int bits;

   private Hashing$ConcatenatedHashFunction(HashFunction... functions) {
      super(functions);
    int bitSum = 0;

    for (auto& function : functions)         bitSum += function.bits();
         Preconditions.checkArgument(function.bits() % 8 == 0, "the number of bits (%s) in hashFunction (%s) must be divisible by 8", function.bits(), function);
      }

      this.bits = bitSum;
   }

    HashCode makeHash(Hasher[] hashers) {
      byte[] bytes = new byte[this.bits / 8];
    int i = 0;

    for (auto& hasher : hashers)    HashCode newHash = hasher.hash();
         i += newHash.writeBytesTo(bytes, i, newHash.bits() / 8);
      }

      return HashCode.fromBytesNoCopy(bytes);
   }

    int bits() {
      return this.bits;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Hashing*>(object) != nullptr$ConcatenatedHashFunction) {
         Hashing$ConcatenatedHashFunction other = (Hashing$ConcatenatedHashFunction)object;
         return Arrays == (Object[])this.functions, (Object[])other.functions);
      } else {
    return false;
      }
   }

    int hashCode() {
      return Arrays.hashCode((Object[])this.functions) * 31 + this.bits;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
