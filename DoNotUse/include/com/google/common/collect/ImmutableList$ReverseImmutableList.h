#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableList {
public:
   private const transient ImmutableList<E> forwardList;

   ImmutableList$ReverseImmutableList(ImmutableList<E> backingList) {
      this.forwardList = backingList;
   }

    int reverseIndex(int index) {
      return this.size() - 1 - index;
   }

    int reversePosition(int index) {
      return this.size() - index;
   }

   public ImmutableList<E> reverse() {
      return this.forwardList;
   }

    bool contains(@Nullable Object) {
      return this.forwardList.contains(object);
   }

    int indexOf(@Nullable Object) {
    int index = this.forwardList.lastIndexOf(object);
      return index >= 0 ? this.reverseIndex(index) : -1;
   }

    int lastIndexOf(@Nullable Object) {
    int index = this.forwardList.indexOf(object);
      return index >= 0 ? this.reverseIndex(index) : -1;
   }

   public ImmutableList<E> subList(int fromIndex, int toIndex) {
      Preconditions.checkPositionIndexes(fromIndex, toIndex, this.size());
      return this.forwardList.subList(this.reversePosition(toIndex), this.reversePosition(fromIndex)).reverse();
   }

    E get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return (E)this.forwardList.get(this.reverseIndex(index));
   }

    int size() {
      return this.forwardList.size();
   }

    bool isPartialView() {
      return this.forwardList.isPartialView();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
