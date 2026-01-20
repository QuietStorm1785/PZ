#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multisets/ElementSet.h"
#include "com/google/j2objc/annotations/Weak.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedMultisets {
public:
   private const SortedMultiset<E> multiset;

   SortedMultisets$ElementSet(SortedMultiset<E> multiset) {
      this.multiset = multiset;
   }

   const SortedMultiset<E> multiset() {
      return this.multiset;
   }

   public Comparator<? super E> comparator() {
      return this.multiset().comparator();
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return this.multiset().subMultiset(fromElement, BoundType.CLOSED, toElement, BoundType.OPEN).elementSet();
   }

   public SortedSet<E> headSet(E toElement) {
      return this.multiset().headMultiset(toElement, BoundType.OPEN).elementSet();
   }

   public SortedSet<E> tailSet(E fromElement) {
      return this.multiset().tailMultiset(fromElement, BoundType.CLOSED).elementSet();
   }

    E first() {
      return (E)SortedMultisets.access$000(this.multiset().firstEntry());
   }

    E last() {
      return (E)SortedMultisets.access$000(this.multiset().lastEntry());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
