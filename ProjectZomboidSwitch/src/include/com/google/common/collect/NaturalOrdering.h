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

namespace com {
namespace google {
namespace common {
namespace collect {


class NaturalOrdering : public Ordering {
public:
    static const NaturalOrdering INSTANCE = std::make_shared<NaturalOrdering>();
   private transient Ordering<Comparable> nullsFirst;
   private transient Ordering<Comparable> nullsLast;
    static const long serialVersionUID = 0L;

    int compare(Comparable left, Comparable right) {
      Preconditions.checkNotNull(left);
      Preconditions.checkNotNull(right);
      return left.compareTo(right);
   }

   public <S : public Comparable> Ordering<S> nullsFirst() {
      Ordering<Comparable> result = this.nullsFirst;
      if (result == nullptr) {
         result = this.nullsFirst = super.nullsFirst();
      }

      return (Ordering<S>)result;
   }

   public <S : public Comparable> Ordering<S> nullsLast() {
      Ordering<Comparable> result = this.nullsLast;
      if (result == nullptr) {
         result = this.nullsLast = super.nullsLast();
      }

      return (Ordering<S>)result;
   }

   public <S : public Comparable> Ordering<S> reverse() {
      return ReverseNaturalOrdering.INSTANCE;
   }

    void* readResolve() {
    return INSTANCE;
   }

    std::string toString() {
      return "Ordering.natural()";
   }

    private NaturalOrdering() {
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
