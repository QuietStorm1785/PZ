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
    int lower = foundIndex;
    int upper = list.size() - 1;

      while (lower < upper) {
    int middle = lower + upper + 1 >>> 1;
    int c = comparator.compare((E)list.get(middle), key);
         if (c > 0) {
            upper = middle - 1;
         } else {
            lower = middle;
         }
      }

    return lower;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
