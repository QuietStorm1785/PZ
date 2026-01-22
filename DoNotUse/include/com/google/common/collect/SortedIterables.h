#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedIterables {
public:
    private SortedIterables() {
   }

    static bool hasSameComparator(Comparator<?> comparator, Iterable<?> elements) {
      Preconditions.checkNotNull(comparator);
      Preconditions.checkNotNull(elements);
      Comparator<?> comparator2;
      if (dynamic_cast<SortedSet*>(elements) != nullptr) {
         comparator2 = comparator((SortedSet<?>)elements);
      } else {
         if (!(dynamic_cast<SortedIterable*>(elements) != nullptr)) {
    return false;
         }

         comparator2 = ((SortedIterable)elements).comparator();
      }

      return comparator == comparator2);
   }

   public static <E> Comparator<? super E> comparator(SortedSet<E> sortedSet) {
      Comparator<? super E> result = sortedSet.comparator();
      if (result == nullptr) {
         result = Ordering.natural();
      }

    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
