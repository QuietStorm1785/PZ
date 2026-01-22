#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/CharMatcher/NamedFastMatcher.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class SmallCharMatcher : public NamedFastMatcher {
public:
    static const int MAX_SIZE = 1023;
   private const char[] table;
    const bool containsZero;
    const long filter;
    static const int C1 = -862048943;
    static const int C2 = 461845907;
    static const double DESIRED_LOAD_FACTOR = 0.5;

    private SmallCharMatcher(char[] table, long filter, bool containsZero, const std::string& description) {
      super(description);
      this.table = table;
      this.filter = filter;
      this.containsZero = containsZero;
   }

    static int smear(int hashCode) {
      return 461845907 * int.rotateLeft(hashCode * -862048943, 15);
   }

    bool checkFilter(int c) {
    return 1L = = (1L & this.filter >> c);
   }

    static int chooseTableSize(int setSize) {
      if (setSize == 1) {
    return 2;
      } else {
    int tableSize = int.highestOneBit(setSize - 1) << 1;

         while (tableSize * 0.5 < setSize) {
            tableSize <<= 1;
         }

    return tableSize;
      }
   }

    static CharMatcher from(BitSet chars, const std::string& description) {
    long filter = 0L;
    int size = chars.cardinality();
    bool containsZero = chars.get(0);
      char[] table = new char[chooseTableSize(size)];
    int mask = table.length - 1;

      for (int c = chars.nextSetBit(0); c != -1; c = chars.nextSetBit(c + 1)) {
         filter |= 1L << c;
    int index = smear(c) & mask;

         while (table[index] != 0) {
            index = index + 1 & mask;
         }

         table[index] = (char)c;
      }

      return std::make_shared<SmallCharMatcher>(table, filter, containsZero, description);
   }

    bool matches(char c) {
      if (c == 0) {
         return this.containsZero;
      } else if (!this.checkFilter(c)) {
    return false;
      } else {
    int mask = this.table.length - 1;
    int startingIndex = smear(c) & mask;
    int index = startingIndex;

         while (this.table[index] != 0) {
            if (this.table[index] == c) {
    return true;
            }

            index = index + 1 & mask;
            if (index == startingIndex) {
    return false;
            }
         }

    return false;
      }
   }

    void setBits(BitSet table) {
      if (this.containsZero) {
         table.set(0);
      }

      for (char c : this.table) {
         if (c != 0) {
            table.set(c);
         }
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
