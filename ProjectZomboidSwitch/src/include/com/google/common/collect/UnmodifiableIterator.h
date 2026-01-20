#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class UnmodifiableIterator {
public:
    protected UnmodifiableIterator() {
   }

    void remove() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
