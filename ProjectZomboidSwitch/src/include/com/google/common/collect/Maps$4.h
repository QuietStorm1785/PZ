#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$4(NavigableSet var1) {
      this.val$set = var1;
   }

   protected NavigableSet<E> delegate() {
      return this.val$set;
   }

    bool add(E element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public SortedSet<E> headSet(E toElement) {
      return Maps.access$300(super.headSet(toElement));
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return Maps.access$300(super.subSet(fromElement, toElement));
   }

   public SortedSet<E> tailSet(E fromElement) {
      return Maps.access$300(super.tailSet(fromElement));
   }

   public NavigableSet<E> headSet(E toElement, boolean inclusive) {
      return Maps.access$400(super.headSet(toElement, inclusive));
   }

   public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
      return Maps.access$400(super.tailSet(fromElement, inclusive));
   }

   public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return Maps.access$400(super.subSet(fromElement, fromInclusive, toElement, toInclusive));
   }

   public NavigableSet<E> descendingSet() {
      return Maps.access$400(super.descendingSet());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
