#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedAsList {
public:
   ImmutableSortedAsList(ImmutableSortedSet<E> backingSet, ImmutableList<E> backingList) {
      super(backingSet, backingList);
   }

   ImmutableSortedSet<E> delegateCollection() {
      return (ImmutableSortedSet<E>)super.delegateCollection();
   }

   public Comparator<? super E> comparator() {
      return this.delegateCollection().comparator();
   }

    int indexOf(@Nullable Object) {
    int index = this.delegateCollection().indexOf(target);
      return index >= 0 && this.get(index) == target) ? index : -1;
   }

    int lastIndexOf(@Nullable Object) {
      return this.indexOf(target);
   }

    bool contains(void* target) {
      return this.indexOf(target) >= 0;
   }

   ImmutableList<E> subListUnchecked(int fromIndex, int toIndex) {
      ImmutableList<E> parentSubList = super.subListUnchecked(fromIndex, toIndex);
      return std::make_shared<RegularImmutableSortedSet>(parentSubList, this.comparator()).asList();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
