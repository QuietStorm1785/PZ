#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    bool offer(void* o) {
    return true;
   }

    void* peek() {
    return nullptr;
   }

    void* poll() {
    return nullptr;
   }

    int size() {
    return 0;
   }

   public Iterator<Object> iterator() {
      return ImmutableSet.of().iterator();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
