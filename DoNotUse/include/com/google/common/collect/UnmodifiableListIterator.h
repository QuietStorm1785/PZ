#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class UnmodifiableListIterator {
public:
    protected UnmodifiableListIterator() {
   }

    void add(E e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(E e) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
