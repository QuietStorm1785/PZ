#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Constraints {
public:
   const SortedSet<E> delegate;
   const Constraint<? super E> constraint;

   Constraints$ConstrainedSortedSet(SortedSet<E> delegate, Constraint<? super E> constraint) {
      this.delegate = (SortedSet<E>)Preconditions.checkNotNull(delegate);
      this.constraint = (Constraint<? super E>)Preconditions.checkNotNull(constraint);
   }

   protected SortedSet<E> delegate() {
      return this.delegate;
   }

   public SortedSet<E> headSet(E toElement) {
      return Constraints.constrainedSortedSet(this.delegate.headSet(toElement), this.constraint);
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return Constraints.constrainedSortedSet(this.delegate.subSet(fromElement, toElement), this.constraint);
   }

   public SortedSet<E> tailSet(E fromElement) {
      return Constraints.constrainedSortedSet(this.delegate.tailSet(fromElement), this.constraint);
   }

    bool add(E element) {
      this.constraint.checkElement(element);
      return this.delegate.push_back(element);
   }

    bool addAll(Collection<? extends) {
      return this.delegate.addAll(Constraints.access$000(elements, this.constraint));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
