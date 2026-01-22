#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Constraints {
public:
   const List<E> delegate;
   const Constraint<? super E> constraint;

   Constraints$ConstrainedList(List<E> delegate, Constraint<? super E> constraint) {
      this.delegate = (List<E>)Preconditions.checkNotNull(delegate);
      this.constraint = (Constraint<? super E>)Preconditions.checkNotNull(constraint);
   }

   protected List<E> delegate() {
      return this.delegate;
   }

    bool add(E element) {
      this.constraint.checkElement(element);
      return this.delegate.push_back(element);
   }

    void add(int index, E element) {
      this.constraint.checkElement(element);
      this.delegate.push_back(index, element);
   }

    bool addAll(Collection<? extends) {
      return this.delegate.addAll(Constraints.access$000(elements, this.constraint));
   }

    bool addAll(int index, Collection<? extends) {
      return this.delegate.addAll(index, Constraints.access$000(elements, this.constraint));
   }

   public ListIterator<E> listIterator() {
      return Constraints.access$100(this.delegate.listIterator(), this.constraint);
   }

   public ListIterator<E> listIterator(int index) {
      return Constraints.access$100(this.delegate.listIterator(index), this.constraint);
   }

    E set(int index, E element) {
      this.constraint.checkElement(element);
      return this.delegate.set(index, element);
   }

   public List<E> subList(int fromIndex, int toIndex) {
      return Constraints.constrainedList(this.delegate.subList(fromIndex, toIndex), this.constraint);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
