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


class Sets {
public:
    bool removeAll(Collection<?> c) {
      return Sets.removeAllImpl(this, c);
   }

    bool retainAll(Collection<?> c) {
      return super.retainAll((Collection<?>)Preconditions.checkNotNull(c));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
