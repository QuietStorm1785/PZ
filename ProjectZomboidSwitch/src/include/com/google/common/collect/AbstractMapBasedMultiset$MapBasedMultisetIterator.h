#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultiset {
public:
   const Iterator<Entry<E, Count>> entryIterator;
   Entry<E, Count> currentEntry;
    int occurrencesLeft;
    bool canRemove;

   AbstractMapBasedMultiset$MapBasedMultisetIterator(AbstractMapBasedMultiset var1) {
      this.this$0 = var1;
      this.entryIterator = AbstractMapBasedMultiset.access$000(var1).entrySet().iterator();
   }

    bool hasNext() {
      return this.occurrencesLeft > 0 || this.entryIterator.hasNext();
   }

    E next() {
      if (this.occurrencesLeft == 0) {
         this.currentEntry = (Entry<E, Count>)this.entryIterator.next();
         this.occurrencesLeft = this.currentEntry.getValue().get();
      }

      this.occurrencesLeft--;
      this.canRemove = true;
      return (E)this.currentEntry.getKey();
   }

    void remove() {
      CollectPreconditions.checkRemove(this.canRemove);
    int frequency = this.currentEntry.getValue().get();
      if (frequency <= 0) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         if (this.currentEntry.getValue().addAndGet(-1) == 0) {
            this.entryIterator.remove();
         }

         AbstractMapBasedMultiset.access$110(this.this$0);
         this.canRemove = false;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
