#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingIterator {
public:
    protected ForwardingIterator() {
   }

   protected abstract Iterator<T> delegate();

    bool hasNext() {
      return this.delegate().hasNext();
   }

    T next() {
      return this.delegate().next();
   }

    void remove() {
      this.delegate().remove();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
