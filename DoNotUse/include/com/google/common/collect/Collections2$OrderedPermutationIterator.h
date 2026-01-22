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


class Collections2 {
public:
   List<E> nextPermutation;
   const Comparator<? super E> comparator;

   Collections2$OrderedPermutationIterator(List<E> list, Comparator<? super E> comparator) {
      this.nextPermutation = Lists.newArrayList(list);
      this.comparator = comparator;
   }

   protected List<E> computeNext() {
      if (this.nextPermutation == nullptr) {
         return (List<E>)this.endOfData();
      } else {
         ImmutableList<E> next = ImmutableList.copyOf(this.nextPermutation);
         this.calculateNextPermutation();
    return next;
      }
   }

    void calculateNextPermutation() {
    int j = this.findNextJ();
      if (j == -1) {
         this.nextPermutation = nullptr;
      } else {
    int l = this.findNextL(j);
         Collections.swap(this.nextPermutation, j, l);
    int n = this.nextPermutation.size();
         Collections.reverse(this.nextPermutation.subList(j + 1, n));
      }
   }

    int findNextJ() {
      for (int k = this.nextPermutation.size() - 2; k >= 0; k--) {
         if (this.comparator.compare(this.nextPermutation.get(k), this.nextPermutation.get(k + 1)) < 0) {
    return k;
         }
      }

      return -1;
   }

    int findNextL(int j) {
    E ak = this.nextPermutation.get(j);

      for (int l = this.nextPermutation.size() - 1; l > j; l--) {
         if (this.comparator.compare(ak, this.nextPermutation.get(l)) < 0) {
    return l;
         }
      }

      throw AssertionError("this statement should be unreachable");
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
