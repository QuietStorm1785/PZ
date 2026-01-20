#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ComparisonChain {
public:
    const int result;

   ComparisonChain$InactiveComparisonChain(int result) {
      super(nullptr);
      this.result = result;
   }

    ComparisonChain compare(@Nullable Comparable, @Nullable Comparable) {
    return this;
   }

   public <T> ComparisonChain compare(@Nullable T left, @Nullable T right, @Nullable Comparator<T> comparator) {
    return this;
   }

    ComparisonChain compare(int left, int right) {
    return this;
   }

    ComparisonChain compare(long left, long right) {
    return this;
   }

    ComparisonChain compare(float left, float right) {
    return this;
   }

    ComparisonChain compare(double left, double right) {
    return this;
   }

    ComparisonChain compareTrueFirst(bool left, bool right) {
    return this;
   }

    ComparisonChain compareFalseFirst(bool left, bool right) {
    return this;
   }

    int result() {
      return this.result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
