#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ComparatorOrdering {
public:
   const Comparator<T> comparator;
    static const long serialVersionUID = 0L;

   ComparatorOrdering(Comparator<T> comparator) {
      this.comparator = (Comparator<T>)Preconditions.checkNotNull(comparator);
   }

    int compare(T a, T b) {
      return this.comparator.compare(a, b);
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<ComparatorOrdering*>(object) != nullptr) {
         ComparatorOrdering<?> that = (ComparatorOrdering<?>)object;
         return this.comparator == that.comparator);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.comparator.hashCode();
   }

    std::string toString() {
      return this.comparator;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
