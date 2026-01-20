#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractIndexedListIterator {
public:
    const int size;
    int position;

   protected abstract E get(int var1);

    protected AbstractIndexedListIterator(int size) {
      this(size, 0);
   }

    protected AbstractIndexedListIterator(int size, int position) {
      Preconditions.checkPositionIndex(position, size);
      this.size = size;
      this.position = position;
   }

    bool hasNext() {
      return this.position < this.size;
   }

    E next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return this.get(this.position++);
      }
   }

    int nextIndex() {
      return this.position;
   }

    bool hasPrevious() {
      return this.position > 0;
   }

    E previous() {
      if (!this.hasPrevious()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return this.get(--this.position);
      }
   }

    int previousIndex() {
      return this.position - 1;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
