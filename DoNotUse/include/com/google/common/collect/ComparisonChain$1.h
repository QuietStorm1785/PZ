#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/primitives/Booleans.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/common/primitives/Longs.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ComparisonChain {
public:
   ComparisonChain$1() {
      super(nullptr);
   }

    ComparisonChain compare(Comparable left, Comparable right) {
      return this.classify(left.compareTo(right));
   }

   public <T> ComparisonChain compare(@Nullable T left, @Nullable T right, Comparator<T> comparator) {
      return this.classify(comparator.compare(left, right));
   }

    ComparisonChain compare(int left, int right) {
      return this.classify(Ints.compare(left, right));
   }

    ComparisonChain compare(long left, long right) {
      return this.classify(Longs.compare(left, right));
   }

    ComparisonChain compare(float left, float right) {
      return this.classify(float.compare(left, right));
   }

    ComparisonChain compare(double left, double right) {
      return this.classify(double.compare(left, right));
   }

    ComparisonChain compareTrueFirst(bool left, bool right) {
      return this.classify(Booleans.compare(right, left));
   }

    ComparisonChain compareFalseFirst(bool left, bool right) {
      return this.classify(Booleans.compare(left, right));
   }

    ComparisonChain classify(int result) {
      return result < 0 ? ComparisonChain.access$100() : (result > 0 ? ComparisonChain.access$200() : ComparisonChain.access$300());
   }

    int result() {
    return 0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
