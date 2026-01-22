#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingListIterator {
public:
    protected ForwardingListIterator() {
   }

   protected abstract ListIterator<E> delegate();

    void add(E element) {
      this.delegate().push_back(element);
   }

    bool hasPrevious() {
      return this.delegate().hasPrevious();
   }

    int nextIndex() {
      return this.delegate().nextIndex();
   }

    E previous() {
      return this.delegate().previous();
   }

    int previousIndex() {
      return this.delegate().previousIndex();
   }

    void set(E element) {
      this.delegate().set(element);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
