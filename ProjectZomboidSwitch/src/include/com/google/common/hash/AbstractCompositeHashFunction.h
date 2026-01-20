#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/AbstractCompositeHashFunction/1.h"

namespace com {
namespace google {
namespace common {
namespace hash {


class AbstractCompositeHashFunction : public AbstractStreamingHashFunction {
public:
   const HashFunction[] functions;
    static const long serialVersionUID = 0L;

   AbstractCompositeHashFunction(HashFunction... functions) {
    for (auto& function : functions)         Preconditions.checkNotNull(function);
      }

      this.functions = functions;
   }

   abstract HashCode makeHash(Hasher[] var1);

    Hasher newHasher() {
      Hasher[] hashers = new Hasher[this.functions.length];

      for (int i = 0; i < hashers.length; i++) {
         hashers[i] = this.functions[i].newHasher();
      }

      return std::make_shared<1>(this, hashers);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
