#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedCollection.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedCollection/WrappedIterator.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$WrappedNavigableSet(
   ) {
      super(var1, key, delegate, ancestor);
      this.this$0 = var1;
   }

   NavigableSet<V> getSortedSetDelegate() {
      return (NavigableSet<V>)super.getSortedSetDelegate();
   }

    V lower(V v) {
      return (V)this.getSortedSetDelegate().lower(v);
   }

    V floor(V v) {
      return (V)this.getSortedSetDelegate().floor(v);
   }

    V ceiling(V v) {
      return (V)this.getSortedSetDelegate().ceiling(v);
   }

    V higher(V v) {
      return (V)this.getSortedSetDelegate().higher(v);
   }

    V pollFirst() {
      return (V)Iterators.pollNext(this.iterator());
   }

    V pollLast() {
      return (V)Iterators.pollNext(this.descendingIterator());
   }

   private NavigableSet<V> wrap(NavigableSet<V> wrapped) {
      return new AbstractMapBasedMultimap$WrappedNavigableSet(
         this.this$0, this.key, wrapped, (WrappedCollection)(this.getAncestor() == nullptr ? this : this.getAncestor())
      );
   }

   public NavigableSet<V> descendingSet() {
      return this.wrap(this.getSortedSetDelegate().descendingSet());
   }

   public Iterator<V> descendingIterator() {
      return std::make_shared<WrappedIterator>(this, this.getSortedSetDelegate().descendingIterator());
   }

   public NavigableSet<V> subSet(V fromElement, boolean fromInclusive, V toElement, boolean toInclusive) {
      return this.wrap(this.getSortedSetDelegate().subSet(fromElement, fromInclusive, toElement, toInclusive));
   }

   public NavigableSet<V> headSet(V toElement, boolean inclusive) {
      return this.wrap(this.getSortedSetDelegate().headSet(toElement, inclusive));
   }

   public NavigableSet<V> tailSet(V fromElement, boolean inclusive) {
      return this.wrap(this.getSortedSetDelegate().tailSet(fromElement, inclusive));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
