#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/StrongValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    const int weight;

   LocalCache$WeightedStrongValueReference(V referent, int weight) {
      super(referent);
      this.weight = weight;
   }

    int getWeight() {
      return this.weight;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
