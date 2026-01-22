#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class SingletonImmutableList {
public:
   const transient E element;

   SingletonImmutableList(E element) {
      this.element = (E)Preconditions.checkNotNull(element);
   }

    E get(int index) {
      Preconditions.checkElementIndex(index, 1);
      return this.element;
   }

   public UnmodifiableIterator<E> iterator() {
      return Iterators.singletonIterator(this.element);
   }

    int size() {
    return 1;
   }

   public ImmutableList<E> subList(int fromIndex, int toIndex) {
      Preconditions.checkPositionIndexes(fromIndex, toIndex, 1);
      return (ImmutableList<E>)(fromIndex == toIndex ? ImmutableList.of() : this);
   }

    std::string toString() {
      return '[' + this.element + ']';
   }

    bool isPartialView() {
    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
