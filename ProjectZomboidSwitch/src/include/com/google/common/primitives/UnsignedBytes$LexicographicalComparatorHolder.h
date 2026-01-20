#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class UnsignedBytes {
public:
    static const std::string UNSAFE_COMPARATOR_NAME = UnsignedBytes$LexicographicalComparatorHolder.class.getName() + "$UnsafeComparator";
   static const Comparator<byte[]> BEST_COMPARATOR = getBestComparator();

   static Comparator<byte[]> getBestComparator() {
      try {
         Class<?> theClass = Class.forName(UNSAFE_COMPARATOR_NAME);
         return (Comparator<byte[]>)theClass.getEnumConstants()[0];
      } catch (Throwable var2) {
         return UnsignedBytes.lexicographicalComparatorJavaImpl();
      }
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
