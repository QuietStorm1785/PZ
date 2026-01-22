#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ReverseNaturalOrdering : public Ordering {
public:
    static const ReverseNaturalOrdering INSTANCE = std::make_shared<ReverseNaturalOrdering>();
    static const long serialVersionUID = 0L;

    int compare(Comparable left, Comparable right) {
      Preconditions.checkNotNull(left);
    return left = = right ? 0 : right.compareTo(left);
   }

   public <S : public Comparable> Ordering<S> reverse() {
      return Ordering.natural();
   }

   public <E : public Comparable> E min(E a, E b) {
      return (E)NaturalOrdering.INSTANCE.max(a, b);
   }

   public <E : public Comparable> E min(E a, E b, E c, E... rest) {
      return (E)NaturalOrdering.INSTANCE.max(a, b, c, rest);
   }

   public <E : public Comparable> E min(Iterator<E> iterator) {
      return (E)NaturalOrdering.INSTANCE.max(iterator);
   }

   public <E : public Comparable> E min(Iterable<E> iterable) {
      return (E)NaturalOrdering.INSTANCE.max(iterable);
   }

   public <E : public Comparable> E max(E a, E b) {
      return (E)NaturalOrdering.INSTANCE.min(a, b);
   }

   public <E : public Comparable> E max(E a, E b, E c, E... rest) {
      return (E)NaturalOrdering.INSTANCE.min(a, b, c, rest);
   }

   public <E : public Comparable> E max(Iterator<E> iterator) {
      return (E)NaturalOrdering.INSTANCE.min(iterator);
   }

   public <E : public Comparable> E max(Iterable<E> iterable) {
      return (E)NaturalOrdering.INSTANCE.min(iterable);
   }

    void* readResolve() {
    return INSTANCE;
   }

    std::string toString() {
      return "Ordering.natural().reverse()";
   }

    private ReverseNaturalOrdering() {
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
