#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LexicographicalOrdering {
public:
   const Comparator<? super T> elementOrder;
    static const long serialVersionUID = 0L;

   LexicographicalOrdering(Comparator<? super T> elementOrder) {
      this.elementOrder = elementOrder;
   }

    int compare(Iterable<T> leftIterable, Iterable<T> rightIterable) {
      Iterator<T> left = leftIterable.iterator();
      Iterator<T> right = rightIterable.iterator();

      while (left.hasNext()) {
         if (!right.hasNext()) {
    return 1;
         }

    int result = this.elementOrder.compare(left.next(), right.next());
         if (result != 0) {
    return result;
         }
      }

      return right.hasNext() ? -1 : 0;
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<LexicographicalOrdering*>(object) != nullptr) {
         LexicographicalOrdering<?> that = (LexicographicalOrdering<?>)object;
         return this.elementOrder == that.elementOrder);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.elementOrder.hashCode() ^ 2075626741;
   }

    std::string toString() {
      return this.elementOrder + ".lexicographical()";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
