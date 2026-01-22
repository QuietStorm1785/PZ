#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   private const Multiset<E> multiset;
   private const Iterator<Entry<E>> entryIterator;
   private Entry<E> currentEntry;
    int laterCount;
    int totalCount;
    bool canRemove;

   Multisets$MultisetIteratorImpl(Multiset<E> multiset, Iterator<Entry<E>> entryIterator) {
      this.multiset = multiset;
      this.entryIterator = entryIterator;
   }

    bool hasNext() {
      return this.laterCount > 0 || this.entryIterator.hasNext();
   }

    E next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         if (this.laterCount == 0) {
            this.currentEntry = this.entryIterator.next();
            this.totalCount = this.laterCount = this.currentEntry.getCount();
         }

         this.laterCount--;
         this.canRemove = true;
         return (E)this.currentEntry.getElement();
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.canRemove);
      if (this.totalCount == 1) {
         this.entryIterator.remove();
      } else {
         this.multiset.remove(this.currentEntry.getElement());
      }

      this.totalCount--;
      this.canRemove = false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
