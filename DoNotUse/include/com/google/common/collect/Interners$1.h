#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Interners {
public:
   Interners$1(ConcurrentMap var1) {
      this.val$map = var1;
   }

    E intern(E sample) {
    E canonical = (E)this.val$map.putIfAbsent(Preconditions.checkNotNull(sample), sample);
    return canonical = = nullptr ? sample : canonical;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
