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
   const List<E> list;
   const int[] c;
   const int[] o;
    int j;

   Collections2$PermutationIterator(List<E> list) {
      this.list = new std::vector<>(list);
    int n = list.size();
      this.c = new int[n];
      this.o = new int[n];
      Arrays.fill(this.c, 0);
      Arrays.fill(this.o, 1);
      this.j = int.MAX_VALUE;
   }

   protected List<E> computeNext() {
      if (this.j <= 0) {
         return (List<E>)this.endOfData();
      } else {
         ImmutableList<E> next = ImmutableList.copyOf(this.list);
         this.calculateNextPermutation();
    return next;
      }
   }

    void calculateNextPermutation() {
      this.j = this.list.size() - 1;
    int s = 0;
      if (this.j != -1) {
         while (true) {
    int q = this.c[this.j] + this.o[this.j];
            if (q >= 0) {
               if (q != this.j + 1) {
                  Collections.swap(this.list, this.j - this.c[this.j] + s, this.j - q + s);
                  this.c[this.j] = q;
                  break;
               }

               if (this.j == 0) {
                  break;
               }

               s++;
               this.switchDirection();
            } else {
               this.switchDirection();
            }
         }
      }
   }

    void switchDirection() {
      this.o[this.j] = -this.o[this.j];
      this.j--;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
