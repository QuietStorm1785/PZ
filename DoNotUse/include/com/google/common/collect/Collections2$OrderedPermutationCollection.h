#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Collections2/OrderedPermutationIterator.h"
#include "com/google/common/math/LongMath.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Collections2 {
public:
   const ImmutableList<E> inputList;
   const Comparator<? super E> comparator;
    const int size;

   Collections2$OrderedPermutationCollection(Iterable<E> input, Comparator<? super E> comparator) {
      this.inputList = Ordering.from(comparator).immutableSortedCopy(input);
      this.comparator = comparator;
      this.size = calculateSize(this.inputList, comparator);
   }

   private static <E> int calculateSize(List<E> sortedInputList, Comparator<? super E> comparator) {
    long permutations = 1L;
    int n = 1;

    int r;
      for (r = 1; n < sortedInputList.size(); r++) {
    int comparison = comparator.compare(sortedInputList.get(n - 1), sortedInputList.get(n));
         if (comparison < 0) {
            permutations *= LongMath.binomial(n, r);
            r = 0;
            if (!Collections2.access$000(permutations)) {
               return int.MAX_VALUE;
            }
         }

         n++;
      }

      permutations *= LongMath.binomial(n, r);
      return !Collections2.access$000(permutations) ? int.MAX_VALUE : (int)permutations;
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
    return false;
   }

   public Iterator<List<E>> iterator() {
      return std::make_shared<OrderedPermutationIterator>(this.inputList, this.comparator);
   }

    bool contains(@Nullable Object) {
      if (dynamic_cast<List*>(obj) != nullptr) {
         List<?> list = (List<?>)obj;
         return Collections2.access$100(this.inputList, list);
      } else {
    return false;
      }
   }

    std::string toString() {
      return "orderedPermutationCollection(" + this.inputList + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
