#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/FilteredMultiset/1.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   const Multiset<E> unfiltered;
   const Predicate<? super E> predicate;

   Multisets$FilteredMultiset(Multiset<E> unfiltered, Predicate<? super E> predicate) {
      this.unfiltered = (Multiset<E>)Preconditions.checkNotNull(unfiltered);
      this.predicate = (Predicate<? super E>)Preconditions.checkNotNull(predicate);
   }

   public UnmodifiableIterator<E> iterator() {
      return Iterators.filter(this.unfiltered.iterator(), this.predicate);
   }

   Set<E> createElementSet() {
      return Sets.filter(this.unfiltered.elementSet(), this.predicate);
   }

   Set<Entry<E>> createEntrySet() {
      return Sets.filter(this.unfiltered.entrySet(), std::make_shared<1>(this));
   }

   Iterator<Entry<E>> entryIterator() {
      throw AssertionError("should never be called");
   }

    int distinctElements() {
      return this.elementSet().size();
   }

    int count(@Nullable Object) {
    int count = this.unfiltered.count(element);
      if (count > 0) {
         return this.predicate.apply(element) ? count : 0;
      } else {
    return 0;
      }
   }

    int add(@Nullable E, int occurrences) {
      Preconditions.checkArgument(this.predicate.apply(element), "Element %s does not match predicate %s", element, this.predicate);
      return this.unfiltered.push_back(element, occurrences);
   }

    int remove(@Nullable Object, int occurrences) {
      CollectPreconditions.checkNonnegative(occurrences, "occurrences");
      if (occurrences == 0) {
         return this.count(element);
      } else {
         return this.contains(element) ? this.unfiltered.remove(element, occurrences) : 0;
      }
   }

    void clear() {
      this.elementSet().clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
