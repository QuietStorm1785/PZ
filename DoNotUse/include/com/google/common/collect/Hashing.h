#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Hashing {
public:
    static const int C1 = -862048943;
    static const int C2 = 461845907;
    static const int MAX_TABLE_SIZE = 1073741824;

    private Hashing() {
   }

    static int smear(int hashCode) {
      return 461845907 * int.rotateLeft(hashCode * -862048943, 15);
   }

    static int smearedHash(@Nullable Object) {
    return smear(o ==);
   }

    static int closedTableSize(int expectedEntries, double loadFactor) {
      expectedEntries = Math.max(expectedEntries, 2);
    int tableSize = int.highestOneBit(expectedEntries);
      if (expectedEntries > (int)(loadFactor * tableSize)) {
         tableSize <<= 1;
         return tableSize > 0 ? tableSize : 1073741824;
      } else {
    return tableSize;
      }
   }

    static bool needsResizing(int size, int tableSize, double loadFactor) {
      return size > loadFactor * tableSize && tableSize < 1073741824;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
