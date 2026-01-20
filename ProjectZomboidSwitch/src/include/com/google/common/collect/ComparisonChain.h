#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ComparisonChain/1.h"
#include "com/google/common/collect/ComparisonChain/InactiveComparisonChain.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ComparisonChain {
public:
    static const ComparisonChain ACTIVE = std::make_shared<1>();
    static const ComparisonChain LESS = std::make_shared<InactiveComparisonChain>(-1);
    static const ComparisonChain GREATER = std::make_shared<InactiveComparisonChain>(1);

    private ComparisonChain() {
   }

    static ComparisonChain start() {
    return ACTIVE;
   }

   public abstract ComparisonChain compare(Comparable<?> var1, Comparable<?> var2);

   public abstract <T> ComparisonChain compare(@Nullable T var1, @Nullable T var2, Comparator<T> var3);

   public abstract ComparisonChain compare(int var1, int var2);

   public abstract ComparisonChain compare(long var1, long var3);

   public abstract ComparisonChain compare(float var1, float var2);

   public abstract ComparisonChain compare(double var1, double var3);

    ComparisonChain compare(bool left, bool right) {
      return this.compareFalseFirst(left, right);
   }

   public abstract ComparisonChain compareTrueFirst(boolean var1, boolean var2);

   public abstract ComparisonChain compareFalseFirst(boolean var1, boolean var2);

   public abstract int result();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
