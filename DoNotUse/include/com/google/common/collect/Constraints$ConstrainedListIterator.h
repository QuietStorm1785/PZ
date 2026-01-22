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


class Constraints {
public:
   private const ListIterator<E> delegate;
   private const Constraint<? super E> constraint;

   public Constraints$ConstrainedListIterator(ListIterator<E> delegate, Constraint<? super E> constraint) {
      this.delegate = delegate;
      this.constraint = constraint;
   }

   protected ListIterator<E> delegate() {
      return this.delegate;
   }

    void add(E element) {
      this.constraint.checkElement(element);
      this.delegate.push_back(element);
   }

    void set(E element) {
      this.constraint.checkElement(element);
      this.delegate.set(element);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
