#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Ordering/IncomparableValueException.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ExplicitOrdering {
public:
   const ImmutableMap<T, int> rankMap;
    static const long serialVersionUID = 0L;

   ExplicitOrdering(List<T> valuesInOrder) {
      this(Maps.indexMap(valuesInOrder));
   }

   ExplicitOrdering(ImmutableMap<T, int> rankMap) {
      this.rankMap = rankMap;
   }

    int compare(T left, T right) {
      return this.rank(left) - this.rank(right);
   }

    int rank(T value) {
    int rank = (int)this.rankMap.get(value);
      if (rank == nullptr) {
         throw IncomparableValueException(value);
      } else {
    return rank;
      }
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<ExplicitOrdering*>(object) != nullptr) {
         ExplicitOrdering<?> that = (ExplicitOrdering<?>)object;
         return this.rankMap == that.rankMap);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.rankMap.hashCode();
   }

    std::string toString() {
      return "Ordering.explicit(" + this.rankMap.keySet() + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
