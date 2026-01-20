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


enum class SortedLists {
   <E> int resultIndex(Comparator<? super E> comparator, E key, List<? : public E> list, int foundIndex) {
    int lower = 0;
    int upper = foundIndex;

      while (lower < upper) {
    int middle = lower + upper >>> 1;
    int c = comparator.compare((E)list.get(middle), key);
         if (c < 0) {
            lower = middle + 1;
         } else {
            upper = middle;
         }
      }

    return lower;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
