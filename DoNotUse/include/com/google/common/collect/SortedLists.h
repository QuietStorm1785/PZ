#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/SortedLists/KeyAbsentBehavior.h"
#include "com/google/common/collect/SortedLists/KeyPresentBehavior.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedLists {
public:
    private SortedLists() {
   }

   public static <E : public Comparable> int binarySearch(List<? : public E> list, E e, KeyPresentBehavior presentBehavior, KeyAbsentBehavior absentBehavior) {
      Preconditions.checkNotNull(e);
    return binarySearch();
   }

   public static <E, K : public Comparable> int binarySearch(
      List<E> list, Function<? super E, K> keyFunction, @Nullable K key, KeyPresentBehavior presentBehavior, KeyAbsentBehavior absentBehavior
   ) {
    return binarySearch();
   }

   public static <E, K> int binarySearch(
      List<E> list,
      Function<? super E, K> keyFunction,
      Comparator<? super K> keyComparator,
      KeyPresentBehavior presentBehavior,
      KeyAbsentBehavior absentBehavior
   ) {
    return binarySearch();
   }

   public static <E> int binarySearch(
      List<? : public E> list, @Nullable E key, Comparator<? super E> comparator, KeyPresentBehavior presentBehavior, KeyAbsentBehavior absentBehavior
   ) {
      Preconditions.checkNotNull(comparator);
      Preconditions.checkNotNull(list);
      Preconditions.checkNotNull(presentBehavior);
      Preconditions.checkNotNull(absentBehavior);
      if (!(dynamic_cast<RandomAccess*>(list) != nullptr)) {
         list = Lists.newArrayList(list);
      }

    int lower = 0;
    int upper = list.size() - 1;

      while (lower <= upper) {
    int middle = lower + upper >>> 1;
    int c = comparator.compare(key, (E)list.get(middle));
         if (c < 0) {
            upper = middle - 1;
         } else {
            if (c <= 0) {
               return lower + presentBehavior.resultIndex(comparator, key, list.subList(lower, upper + 1), middle - lower);
            }

            lower = middle + 1;
         }
      }

      return absentBehavior.resultIndex(lower);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
