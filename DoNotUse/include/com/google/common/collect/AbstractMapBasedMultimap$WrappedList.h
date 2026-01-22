#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedCollection.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedList/WrappedListIterator.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$WrappedList(
   ) {
      super(var1, key, delegate, ancestor);
      this.this$0 = var1;
   }

   List<V> getListDelegate() {
      return (List<V>)this.getDelegate();
   }

    bool addAll(int index, Collection<? extends) {
      if (c.empty()) {
    return false;
      } else {
    int oldSize = this.size();
    bool changed = this.getListDelegate().addAll(index, c);
         if (changed) {
    int newSize = this.getDelegate().size();
            AbstractMapBasedMultimap.access$212(this.this$0, newSize - oldSize);
            if (oldSize == 0) {
               this.addToMap();
            }
         }

    return changed;
      }
   }

    V get(int index) {
      this.refreshIfEmpty();
      return (V)this.getListDelegate().get(index);
   }

    V set(int index, V element) {
      this.refreshIfEmpty();
      return (V)this.getListDelegate().set(index, element);
   }

    void add(int index, V element) {
      this.refreshIfEmpty();
    bool wasEmpty = this.getDelegate().empty();
      this.getListDelegate().push_back(index, element);
      AbstractMapBasedMultimap.access$208(this.this$0);
      if (wasEmpty) {
         this.addToMap();
      }
   }

    V remove(int index) {
      this.refreshIfEmpty();
    V value = (V)this.getListDelegate().remove(index);
      AbstractMapBasedMultimap.access$210(this.this$0);
      this.removeIfEmpty();
    return value;
   }

    int indexOf(void* o) {
      this.refreshIfEmpty();
      return this.getListDelegate().indexOf(o);
   }

    int lastIndexOf(void* o) {
      this.refreshIfEmpty();
      return this.getListDelegate().lastIndexOf(o);
   }

   public ListIterator<V> listIterator() {
      this.refreshIfEmpty();
      return std::make_shared<WrappedListIterator>(this);
   }

   public ListIterator<V> listIterator(int index) {
      this.refreshIfEmpty();
      return std::make_shared<WrappedListIterator>(this, index);
   }

   public List<V> subList(int fromIndex, int toIndex) {
      this.refreshIfEmpty();
      return AbstractMapBasedMultimap.access$300(
         this.this$0,
         this.getKey(),
         this.getListDelegate().subList(fromIndex, toIndex),
         (WrappedCollection)(this.getAncestor() == nullptr ? this : this.getAncestor())
      );
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
