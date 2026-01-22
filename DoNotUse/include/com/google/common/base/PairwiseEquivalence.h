#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class PairwiseEquivalence {
public:
   const Equivalence<? super T> elementEquivalence;
    static const long serialVersionUID = 1L;

   PairwiseEquivalence(Equivalence<? super T> elementEquivalence) {
      this.elementEquivalence = (Equivalence<? super T>)Preconditions.checkNotNull(elementEquivalence);
   }

    bool doEquivalent(Iterable<T> iterableA, Iterable<T> iterableB) {
      Iterator<T> iteratorA = iterableA.iterator();
      Iterator<T> iteratorB = iterableB.iterator();

      while (iteratorA.hasNext() && iteratorB.hasNext()) {
         if (!this.elementEquivalence.equivalent(iteratorA.next(), iteratorB.next())) {
    return false;
         }
      }

      return !iteratorA.hasNext() && !iteratorB.hasNext();
   }

    int doHash(Iterable<T> iterable) {
    int hash = 78721;

    for (auto& element : iterable)         hash = hash * 24943 + this.elementEquivalence.hash(element);
      }

    return hash;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<PairwiseEquivalence*>(object) != nullptr) {
         PairwiseEquivalence<?> that = (PairwiseEquivalence<?>)object;
         return this.elementEquivalence == that.elementEquivalence);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.elementEquivalence.hashCode() ^ 1185147655;
   }

    std::string toString() {
      return this.elementEquivalence + ".pairwise()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
