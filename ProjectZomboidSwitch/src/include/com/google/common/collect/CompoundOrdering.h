#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class CompoundOrdering {
public:
   const ImmutableList<Comparator<? super T>> comparators;
    static const long serialVersionUID = 0L;

   CompoundOrdering(Comparator<? super T> primary, Comparator<? super T> secondary) {
      this.comparators = ImmutableList.of(primary, secondary);
   }

   CompoundOrdering(Iterable<? : public Comparator<? super T>> comparators) {
      this.comparators = ImmutableList.copyOf(comparators);
   }

    int compare(T left, T right) {
    int size = this.comparators.size();

      for (int i = 0; i < size; i++) {
    int result = ((Comparator)this.comparators.get(i)).compare(left, right);
         if (result != 0) {
    return result;
         }
      }

    return 0;
   }

    bool equals(void* object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<CompoundOrdering*>(object) != nullptr) {
         CompoundOrdering<?> that = (CompoundOrdering<?>)object;
         return this.comparators == that.comparators);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.comparators.hashCode();
   }

    std::string toString() {
      return "Ordering.compound(" + this.comparators + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
