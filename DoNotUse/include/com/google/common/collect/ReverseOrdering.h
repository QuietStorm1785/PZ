#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ReverseOrdering {
public:
   const Ordering<? super T> forwardOrder;
    static const long serialVersionUID = 0L;

   ReverseOrdering(Ordering<? super T> forwardOrder) {
      this.forwardOrder = (Ordering<? super T>)Preconditions.checkNotNull(forwardOrder);
   }

    int compare(T a, T b) {
      return this.forwardOrder.compare(b, a);
   }

   public <S : public T> Ordering<S> reverse() {
      return this.forwardOrder;
   }

   public <E : public T> E min(E a, E b) {
      return (E)this.forwardOrder.max(a, b);
   }

   public <E : public T> E min(E a, E b, E c, E... rest) {
      return (E)this.forwardOrder.max(a, b, c, rest);
   }

   public <E : public T> E min(Iterator<E> iterator) {
      return (E)this.forwardOrder.max(iterator);
   }

   public <E : public T> E min(Iterable<E> iterable) {
      return (E)this.forwardOrder.max(iterable);
   }

   public <E : public T> E max(E a, E b) {
      return (E)this.forwardOrder.min(a, b);
   }

   public <E : public T> E max(E a, E b, E c, E... rest) {
      return (E)this.forwardOrder.min(a, b, c, rest);
   }

   public <E : public T> E max(Iterator<E> iterator) {
      return (E)this.forwardOrder.min(iterator);
   }

   public <E : public T> E max(Iterable<E> iterable) {
      return (E)this.forwardOrder.min(iterable);
   }

    int hashCode() {
      return -this.forwardOrder.hashCode();
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<ReverseOrdering*>(object) != nullptr) {
         ReverseOrdering<?> that = (ReverseOrdering<?>)object;
         return this.forwardOrder == that.forwardOrder);
      } else {
    return false;
      }
   }

    std::string toString() {
      return this.forwardOrder + ".reverse()";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
