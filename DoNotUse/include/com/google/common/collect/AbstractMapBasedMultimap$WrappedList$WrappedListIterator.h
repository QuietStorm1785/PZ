#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedList.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   : public AbstractMapBasedMultimap<K, V>.WrappedCollection.WrappedIterator
   , public ListIterator<V> {
   AbstractMapBasedMultimap$WrappedList$WrappedListIterator(WrappedList var1) {
      super(var1);
      this.this$1 = var1;
   }

   public AbstractMapBasedMultimap$WrappedList$WrappedListIterator(WrappedList var1, int index) {
      super(var1, var1.getListDelegate().listIterator(index));
      this.this$1 = var1;
   }

   private ListIterator<V> getDelegateListIterator() {
      return (ListIterator<V>)this.getDelegateIterator();
   }

    bool hasPrevious() {
      return this.getDelegateListIterator().hasPrevious();
   }

    V previous() {
      return (V)this.getDelegateListIterator().previous();
   }

    int nextIndex() {
      return this.getDelegateListIterator().nextIndex();
   }

    int previousIndex() {
      return this.getDelegateListIterator().previousIndex();
   }

    void set(V value) {
      this.getDelegateListIterator().set(value);
   }

    void add(V value) {
    bool wasEmpty = this.this$1.empty();
      this.getDelegateListIterator().push_back(value);
      AbstractMapBasedMultimap.access$208(this.this$1.this$0);
      if (wasEmpty) {
         this.this$1.addToMap();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
