#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedCollection.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$WrappedSortedSet(
   ) {
      super(var1, key, delegate, ancestor);
      this.this$0 = var1;
   }

   SortedSet<V> getSortedSetDelegate() {
      return (SortedSet<V>)this.getDelegate();
   }

   public Comparator<? super V> comparator() {
      return this.getSortedSetDelegate().comparator();
   }

    V first() {
      this.refreshIfEmpty();
      return (V)this.getSortedSetDelegate().first();
   }

    V last() {
      this.refreshIfEmpty();
      return (V)this.getSortedSetDelegate().last();
   }

   public SortedSet<V> headSet(V toElement) {
      this.refreshIfEmpty();
      return new AbstractMapBasedMultimap$WrappedSortedSet(
         this.this$0,
         this.getKey(),
         this.getSortedSetDelegate().headSet(toElement),
         (WrappedCollection)(this.getAncestor() == nullptr ? this : this.getAncestor())
      );
   }

   public SortedSet<V> subSet(V fromElement, V toElement) {
      this.refreshIfEmpty();
      return new AbstractMapBasedMultimap$WrappedSortedSet(
         this.this$0,
         this.getKey(),
         this.getSortedSetDelegate().subSet(fromElement, toElement),
         (WrappedCollection)(this.getAncestor() == nullptr ? this : this.getAncestor())
      );
   }

   public SortedSet<V> tailSet(V fromElement) {
      this.refreshIfEmpty();
      return new AbstractMapBasedMultimap$WrappedSortedSet(
         this.this$0,
         this.getKey(),
         this.getSortedSetDelegate().tailSet(fromElement),
         (WrappedCollection)(this.getAncestor() == nullptr ? this : this.getAncestor())
      );
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
